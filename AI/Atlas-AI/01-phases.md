# Atlas AI — phase-by-phase breakdown

All 11 phases are `Complete` per `docs/internal/engineering-history/project-status.md` in the
implementation repo, tagged `phase-1` … `phase-11` in git (Phase 0 has no standalone tag — the repo
wasn't initialized yet at that point). Use this file to drill one phase at a time; don't re-read
the whole thing in one sitting — that defeats the "small chunks" teaching rule.

Format per phase: state before → problem → what shipped → data/control-flow change → key decisions
→ key algorithm/schema → security → failure scenarios → tests/gates → trade-offs → interview
framing → pointers.

---

## Phase 0 — System design and contracts

- **Before**: nothing; blank repo.
- **Problem**: define the system before writing product code — architecture, threat model, data
  model, phase contracts — so later phases build against a stable target instead of improvising.
- **Shipped**: `docs/architecture.md`, `docs/threat-model.md`, `docs/data-model.md`, ADR ledger
  (`docs/decisions.md`), system-design visuals, per-phase implementation contracts under
  `docs/internal/engineering-history/phases/`.
- **Key decisions**: the 36 ADRs in `docs/decisions.md` (D01–D36) were mostly locked here —
  monorepo boundary, Postgres-as-authority, provider-neutral ports, deterministic-before-agentic,
  no-multi-agent-without-evidence, zero-cost-by-default. These are the rules every later phase is
  graded against.
- **Trade-off framing**: heavy upfront design vs. "just start coding" — justified here because the
  hard parts (tenant isolation, citation integrity, idempotency) are exactly the parts that are
  expensive to retrofit.
- **Interview framing**: "I wrote the ADRs and threat model before any product code, and every
  later phase had to satisfy them — that's why isolation and citation integrity aren't bolted on."
- **Pointers**: `docs/decisions.md`, `docs/threat-model.md` §Security objectives, `docs/internal/engineering-history/phases/`.

---

## Phase 1 — Monorepo foundation, auth, workspaces, RBAC, audit

- **Before**: only design docs, no running code.
- **Problem**: stand up the deployable shape (web/api/worker) and the tenancy primitive everything
  else depends on — workspaces, membership, roles — plus auth that works with $0 spend.
- **Shipped**: pnpm/Turborepo monorepo; deterministic local dev auth + OIDC/JWKS production
  boundary; workspace/member APIs; RBAC; idempotency; audit events; Tailwind web UI.
- **Data/control flow**: browser → Next.js BFF → FastAPI (owns auth context + use cases) →
  Postgres. No direct DB/provider access from the web app, ever.
- **Key decisions**: D21 (dev auth is local-only; prod config *rejects* `AUTH_MODE=development` and
  requires real JWKS); D22 (workspace-creation idempotency via actor+operation+key-hash serialized
  with a Postgres advisory lock); D23 (audit events are transactional with the mutation, not an
  async afterthought); D24 (Tailwind is the fixed styling system).
- **Key schema/algorithm**: `users`, `workspaces`, `memberships (workspace_id, user_id) unique`,
  `audit_events`, `idempotency_records`. Permission names are stable actions checked in
  *application*, not routes — "RBAC lives in domain/application logic, not `if role == 'admin'`
  scattered in routes."
- **Security**: workspace access derived from active membership → non-disclosing `404` if absent
  (not `403` — don't reveal a resource exists); last-owner removal/downgrade transactionally
  rejected; CSP/frame-deny/nosniff headers on the web app.
- **Failure scenarios**: a retried workspace-creation request must not create two workspaces
  (idempotency key + advisory lock); a role downgrade that would leave zero owners must be rejected
  mid-transaction, not cleaned up after.
- **Tests/gates**: migration + lint + typecheck + build + tests + local foundation demo.
  `apps/api/tests/test_authentication.py`, `test_workspace_api.py`.
- **Trade-off**: no fine-grained ACLs yet — role-based only, deliberately, until a real requirement
  demands per-resource ACLs (see D05).
- **Interview framing**: "Why non-disclosing 404 instead of 403 for cross-tenant access?" → 403
  confirms the resource exists in another tenant; 404 leaks nothing. This single answer is a good
  tenant-isolation talking point.
- **Pointers**: `phase-1` tag / commit `47331fb`; `docs/decisions.md` D21–D24; `docs/threat-model.md`
  §Phase 1 implementation security review.

---

## Phase 2 — Source storage, signed uploads, durable ingestion metadata

- **Before**: workspaces/auth exist; no way to get a document into the system.
- **Problem**: accept file uploads safely and durably, without cloud credentials, and set up the
  job the worker will later claim.
- **Shipped**: source/document/version/upload metadata; HMAC-signed local uploads with digest
  verification; Postgres-backed ingestion jobs, leases, cancel/retry/delete, reconciliation.
- **Data/control flow**: API issues a scoped upload intent + signed URL → client uploads directly →
  API finalizes by re-verifying digest/size/media-type → one transaction creates document + version
  + job + job-event + audit-event + idempotency record.
- **Key decisions**: D25 (local filesystem object-store adapter behind the same interface a real S3
  adapter would implement — production swap is config, not rewrite); D26 (Postgres `FOR UPDATE SKIP
  LOCKED` leasing instead of standing up a broker this early).
- **Key schema/algorithm**: `sources`, `upload_intents` (tenant-prefixed key, digest, expiry),
  `documents`, `document_versions` (immutable), `ingestion_jobs` (lease owner/expiry, heartbeat,
  bounded attempts), `job_events` (append-only). Object keys are **server-generated**, never
  client-chosen — prevents key-guessing/path traversal.
- **Security**: signed upload URLs expire with the intent; finalize re-checks digest so a swapped
  file after signing is caught; worker publication requires a valid lease owner + expected job
  version (stale worker can't publish).
- **Failure scenarios**: worker dies after leasing but before publishing → lease expires → another
  worker reclaims; corrupt/missing object at finalize → job fails as an integrity failure, no
  version published.
- **Tests/gates**: `apps/api/tests/test_document_ingestion_api.py`, `apps/worker/tests/test_ingestion.py`.
- **Trade-off**: no malware scanning / magic-byte validation yet (deferred to Phase 3's parser
  boundary); no durable quota ledger yet, just size limits + permission checks.
- **Interview framing**: "Why database-backed leasing instead of SQS/Kafka on day one?" → D07 —
  avoid premature queue infra; adopt a broker only when throughput/isolation/delay-semantics
  evidence demands it. `FOR UPDATE SKIP LOCKED` gives real concurrent-safe claiming without one.
- **Pointers**: `phase-2` tag (impl `00c3a2b`, gate snapshot `413b918`); `docs/decisions.md` D25–D26;
  `docs/data-model.md` §Sources and documents.

---

## Phase 3 — Parsing, normalization, deterministic chunking

- **Before**: a document can be uploaded and has a durable job; nothing extracts or chunks it yet.
- **Problem**: turn raw bytes into deterministic, provenance-tracked chunks — safely, for a narrow
  allowlist of formats.
- **Shipped**: deterministic text/Markdown parser + canonical normalization; workspace-scoped
  normalized artifacts; immutable chunks; parser/chunker provenance; chunk preview UI.
- **Data/control flow**: worker: verify object → parse (text/Markdown only) → normalize → write
  normalized derived artifact (digest-verified) → deterministic chunk → (chunks not yet published
  — that waits for Phase 4's embedding step in the full state machine).
- **Key decisions**: D28 — narrow allowlist first (text/Markdown), richer converters (PDF/Office/OCR)
  deliberately deferred behind a parser-sandbox boundary that doesn't exist yet.
- **Key schema/algorithm**: `chunks` — immutable, one document version each, deterministic ordinal,
  content hash, chunker version. Binary magic bytes, PDFs, archives, OLE containers, invalid UTF-8,
  empty extracted text, oversized input all **fail safely** rather than silently mis-parsing.
- **Security**: parser input is allowlisted and bounded (size/time); extracted text is rendered as
  escaped React text in the UI — never treated as HTML or instructions, even though it's untrusted.
- **Failure scenarios**: unsupported file type → job fails with a safe error code, no bytes/content
  leaked into logs/errors.
- **Tests/gates**: parser fixtures for each unsafe-input class; chunk API cross-tenant `404` test.
- **Trade-off**: no PDF/Office/OCR — explicitly out of scope until sandboxing + fixture coverage +
  evidence exist; chunk size/overlap are deterministic defaults, not evaluation-tuned.
- **Interview framing**: "Why not just support every format on day one?" → each format is an attack
  surface (archive bombs, path traversal, parser exploits); the allowlist-first approach keeps the
  zero-cost/safe default while leaving the door open via the same parser-boundary interface.
- **Pointers**: `phase-3` tag; `docs/decisions.md` D28; `docs/threat-model.md` §Phase 3 review.

---

## Phase 4 — Embeddings and semantic retrieval

- **Before**: chunks exist but aren't searchable.
- **Problem**: make chunks semantically searchable, tenant-safe, without a paid embedding API.
- **Shipped**: deterministic local embedding provider + bounded batch planner; workspace-scoped
  embedding sets; atomic chunk+embedding publication; tenant-safe semantic evidence API; idempotent
  backfill repair command.
- **Data/control flow**: this is where the **full ingestion state machine** first completes end to
  end — `PENDING → CLAIMED → VERIFYING → PARSING → NORMALIZING → CHUNKING → EMBEDDING → PUBLISHING
  → SUCCEEDED`, and a version becomes `READY`/active **only after** embeddings for the active
  embedding set are complete. Nothing is searchable before that atomic publish.
- **Key decisions**: D29 — deterministic local hash embeddings + **exact cosine** retrieval as the
  default gate; D09 — Postgres is retrieval authority now, pgvector is an evidence-gated future
  index, not implemented (plain Postgres image today, no extension).
- **Key schema/algorithm**: `embedding_sets` (provider/model/version/dimension/normalization —
  provenance so nothing compares across incompatible vector spaces), `chunk_embeddings` — one
  vector per `(chunk_id, embedding_set_id)`, stored as **JSONB** (not a vector type) for the
  zero-cost baseline. Search: tenant + active-document + active-version + ready-version +
  embedding-set filters applied *before* ranking.
- **Security**: semantic search checks membership + `document:read` before any embedding/query;
  query length and `top_k` are bounded; raw vectors never returned in responses.
- **Failure scenarios**: idempotent backfill command can repair missing embeddings without
  duplicating work.
- **Tests/gates**: zero-cost search demo, cross-tenant denial, invalid-query failure, backfill
  no-op validation. `apps/api/tests/test_embeddings.py`.
- **Trade-off**: JSONB exact cosine is O(n) per query, not ANN — fine at demo scale, explicitly
  gated behind future pgvector/HNSW adoption once corpus-size/recall/latency evidence exists (D09).
- **Interview framing**: "Isn't JSONB cosine slow at scale?" → yes, deliberately deferred: the
  interface (`SemanticRetriever.search`) doesn't change when the index does; only implementation
  and infra swap, which is the point of the adapter boundary.
- **Pointers**: `phase-4` tag; `docs/decisions.md` D09, D29; `docs/data-model.md` §Chunks and embeddings.

---

## Phase 5 — Lexical and hybrid retrieval

- **Before**: semantic search only; misses exact-keyword-match cases semantic embeddings are weak at.
- **Problem**: add lexical search and fuse it with semantic, without a managed search service.
- **Shipped**: Postgres full-text lexical retrieval (GIN expression index); unified
  semantic/lexical/hybrid search API with deterministic RRF fusion + dedup; retrieval diagnostics;
  basic Recall@K/MRR utility.
- **Data/control flow**: hybrid search runs semantic and lexical branches under the **same**
  authorization/filter predicates, then fuses — fusion never runs *outside* the access-control
  boundary (this is the detail worth stating precisely in an interview).
- **Key decisions**: D30 — Postgres FTS + RRF as the zero-cost hybrid baseline; weighted/learned
  fusion, synonyms, multilingual analyzers, OpenSearch all deferred pending evaluation evidence.
- **Key schema/algorithm**: `ix_chunks_fts_english` GIN index on `to_tsvector('english', text)`.
  **Reciprocal Rank Fusion**: `score = Σ 1/(k + rank_i)` across each branch's ranked list — no
  score calibration needed between semantic distance and lexical rank, which is exactly why RRF is
  the safe first fusion choice (D10). Dedup by `(chunk_id, document_version_id)`.
- **Security**: lexical queries go through parameterized `websearch_to_tsquery` (no string-built
  SQL); special-character queries handled safely.
- **Failure scenarios**: invalid mode/bounds fail through typed request schema before touching
  retrieval.
- **Tests/gates**: cross-tenant denial, invalid-bound failure, special-character lexical query.
  `apps/api/tests/test_retrieval_fusion.py`.
- **Trade-off**: English-analyzer only; no query caching yet.
- **Interview framing**: "Why RRF over weighted score fusion?" → semantic cosine distance and
  lexical rank aren't on a comparable scale; RRF only needs *rank*, is robust without calibration,
  and weighted fusion is explicitly gated behind evaluation evidence (D10, D20).
- **Pointers**: `phase-5` tag; `docs/decisions.md` D10, D30.

---

## Phase 6 — Reranking, context, grounded generation, citation integrity

- **Before**: retrieval returns ranked evidence; no answer synthesis yet, and no citation checking
  mechanism exists anywhere in the system.
- **Problem**: generate an answer that's actually grounded, and *prove* it after the fact rather
  than trust the model.
- **Shipped**: deterministic local reranker, context builder, generator, output/citation validator,
  answer orchestrator; workspace-scoped answer runs, answer evidence, citations, full provenance.
- **Data/control flow**: retrieval evidence → context builder (dedup, bounded evidence count +
  character budget, labels untrusted excerpts) → generator (sees **only** supplied evidence, zero
  tools/secrets/network) → **separate** citation validator checks every marker+span+quote against
  the frozen evidence → persist `answer_runs` + immutable `answer_evidence` + `citations`.
- **Key decisions**: D31 — synchronous deterministic generation + post-generation validation as the
  gate; D11 (cross-cutting) — retrieval produces typed evidence, generation consumes only that,
  citations are post-validated, never trusted from formatting.
- **Key schema/algorithm**: `citations.status ∈ {resolvable, span_matched, supported, rejected}` —
  these are **not synonyms**; an answer is citation-verified only if every claimed evidence
  identity was actually supplied and authorized. Prompt-injection-like phrases in retrieved text are
  detected and avoided/warned rather than blindly included.
- **Security**: no-evidence questions get a **labeled refusal**, never an unsupported answer; answer
  creation re-authorizes before persisting.
- **Failure scenarios**: fabricated citation → validator rejects it, doesn't silently pass; refusal
  path is a first-class outcome, not an error.
- **Tests/gates**: no-evidence refusal, prompt-injection warning, fabricated-citation rejection.
  `apps/api/tests/test_generation.py`.
- **Trade-off**: deterministic generator is a correctness baseline, not production answer quality —
  explicitly labeled as such; streaming disabled because safe partial-output validation needs its
  own design.
- **Interview framing**: "How do you stop the model from hallucinating a citation?" → don't trust
  the model's formatting at all — a separate deterministic validator re-derives whether the quoted
  span actually resolves to supplied evidence, after generation completes. This is the single best
  answer in the whole project for "how do you make LLM output trustworthy."
- **Pointers**: `phase-6` tag; `docs/decisions.md` D11, D31; `docs/data-model.md` §Evidence, answers,
  citations.

---

## Phase 7 — Retrieval and RAG evaluation platform

- **Before**: retrieval and generation exist but quality is unmeasured — "it works" isn't evidence.
- **Problem**: build a real, reproducible offline evaluation harness over the *production* services.
- **Shipped**: versioned evaluation datasets, immutable labeled cases; deterministic offline runs
  over production retrieval/answer services; metric-versioned reports; append-only baseline
  approval.
- **Data/control flow**: a run pins dataset version, code revision, retrieval/prompt/model configs,
  metric versions. Hidden labels (expected answers, relevant chunks) are used **only by the metric
  layer after** the system-under-test produces output — never fed into retrieval or generation
  (leakage prevention).
- **Key decisions**: D32 — evaluate through the real services, not copied metric-only logic
  (otherwise regressions hide behind test-only code paths).
- **Key schema/algorithm**: `evaluation_datasets → evaluation_dataset_versions → evaluation_cases`
  (immutable after use) `→ evaluation_runs → evaluation_results`; `evaluation_baselines` is
  append-only audited approval. Metrics: Recall@K, MRR, citation-verified rate.
- **Security**: same membership/RBAC boundary as everything else; relevant-chunk labels only
  accepted if the chunk is ready/active/same-workspace.
- **Failure scenarios**: failed system execution, metric failure, and missing labels are **distinct
  statuses** — an aggregate score never silently absorbs an unsafe/incomplete case.
- **Tests/gates**: invalid-label failure, cross-tenant denial, baseline approval flow.
  `apps/api/tests/test_evaluations.py`.
- **Trade-off**: no hosted LLM-judge, no online experimentation yet — deterministic local metrics
  only, by design, to keep evaluation itself zero-cost and reproducible.
- **Interview framing**: "How do you know your RAG system actually works?" → not vibes — a
  versioned, leakage-safe offline harness scoring the same production code path, with
  Recall@5=1.0, MRR=1.0, citation-verified rate=1.0 on the regression set (see README's validation
  numbers) as a concrete, defensible number.
- **Pointers**: `phase-7` tag; `docs/decisions.md` D32.

---

## Phase 8 — Evidence-gated advanced RAG (query expansion)

- **Before**: baseline hybrid retrieval works but misses vocabulary-mismatch queries.
- **Problem**: prove *one* advanced RAG technique earns its complexity, using the Phase 7 harness,
  before adding more.
- **Shipped**: allowlisted baseline + `phase8-multi-query-expansion-v1` config; deterministic
  bounded query expansion; multi-query retrieval planning with branch provenance; UI plan
  visibility; zero-cost ablation proving the technique against baseline.
- **Data/control flow**: query → deterministic fixed synonym expansion (bounded variant count) →
  each variant retrieves under the *same* tenant/ACL filters → provenance records which variant
  contributed which evidence item.
- **Key decisions**: D33 — enable exactly one technique by default, and only because the Phase
  7-style ablation showed a named slice going from **zero recall** (baseline lexical) to **full
  recall** (expansion) with no paid providers involved. Anything else (contextual retrieval, learned
  fusion, LlamaIndex, personalization) stays deferred until its *own* ablation clears the same bar.
- **Key schema/algorithm**: fixed synonym mapping, not an LLM rewriter; fan-out bounded by
  max-variants + branch-query budget + per-branch candidate limit, all visible in debug output.
- **Security**: expansion cannot broaden tenant/source/document/ACL scope — existing predicates
  still apply inside every branch; prompt-injection-like query text suppresses expansion entirely.
- **Failure scenarios**: n/a beyond standard retrieval failure paths — expansion is additive, not a
  new failure surface by design.
- **Tests/gates**: baseline-vs-advanced ablation, invalid-config failure, cross-tenant denial.
  `apps/api/tests/test_phase8_advanced_rag.py`.
- **Trade-off**: narrow deterministic synonym expansion vs. a general semantic rewriter — the
  latter needs an LLM and isn't zero-cost; can introduce intent drift outside fixture coverage.
- **Interview framing**: this phase *is* the interview answer to "how do you decide whether to add
  RAG complexity?" — evidence-gated ablation against a fixed harness, not intuition. D20 generalizes
  this: evaluation gates advanced retrieval, agent complexity, and optimization changes.
- **Pointers**: `phase-8` tag; `docs/decisions.md` D20, D33.

---

## Phase 9 — Bounded agentic research workflow

- **Before**: single-shot grounded Q&A only; no multi-step reasoning or tool use.
- **Problem**: add bounded agentic research *without* an uncontrolled agent runtime — deterministic
  first, agentic only where genuinely needed, with a hard human checkpoint before anything
  synthesizes a final report.
- **Shipped**: workspace-scoped research runs/steps/tool-invocations/checkpoints/approvals/budgets/
  cited reports; deterministic local `ResearchGraph` (planner, Atlas-retrieval tool, local
  policy-catalog tool, approval gate, synthesis); research API/UI.
- **Data/control flow**: `PENDING → RUNNING → WAITING_APPROVAL → SUCCEEDED`, with `CANCELLED` from
  most states and specifically when an approval is **denied**. Synthesis is blocked until an
  authorized user submits a **current** approval version — stale approvals fail with conflict.
- **Key decisions**: D34 — deterministic local graph behind a `ResearchGraph` boundary *before*
  adopting the LangGraph package itself, so the runtime dependency is adopted only once
  checkpoint/retry/failure-mode evidence justifies it; D16 (cross-cutting) — no multi-agent runtime
  without benchmark evidence.
- **Key schema/algorithm**: allowlisted tools = exactly `atlas_retrieval` + `local_policy_catalog` —
  no shell, no arbitrary HTTP, no code execution, no paid provider tool. Tool invocations use
  **stable idempotency keys** so resuming a run never silently repeats a non-idempotent tool effect.
  Budget reservations: reserve → commit actual usage → release unused; concurrency-safe.
- **Security**: prompt-injection/SSRF-like input requesting forbidden tools/URLs/secrets is rejected
  **before run persistence**, not after; clients cannot submit arbitrary graph state, tool names,
  URLs, prompts, budgets, or provider config — the server picks all of that.
- **Failure scenarios**: worker/run interruption resumes from the last checkpoint without repeating
  completed tool calls (idempotency keys); denied approval terminates the run as `CANCELLED`, not
  silently retried.
- **Tests/gates**: idempotent replay, approval-gated synthesis, forbidden-tool rejection,
  stale-version conflict, cross-tenant denial. `apps/api/tests/test_phase9_research.py`.
- **Trade-off**: not a general autonomous agent runtime — deliberately bounded (2 tools, fixed
  budget, mandatory human gate). LangGraph itself isn't a dependency yet; the interface is fixed,
  the implementation isn't.
- **Interview framing**: "How do you keep an agent from doing something irreversible?" → allowlist
  the tools to the minimum needed, require a **fresh** authorization check plus explicit human
  approval before the consequential step (synthesis/report), and make every tool call idempotent so
  resuming never double-executes. This whole phase is a strong "responsible agentic system design"
  answer.
- **Pointers**: `phase-9` tag; `docs/decisions.md` D15, D16, D34; `docs/data-model.md` §Research and
  budgets.

---

## Phase 10 — Security guardrails and adversarial assurance

- **Before**: security is enforced per-phase (tenant checks, parser allowlists, tool allowlists)
  but there's no dedicated guardrail layer scanning content itself, and no auditable security-event
  trail.
- **Problem**: consolidate and add executable, deterministic guardrails (prompt injection,
  secret-leak, SSRF) plus quota/abuse controls and an admin-visible security posture.
- **Shipped**: deterministic input/output guardrails, redactor, egress policy, fail-closed scanner
  behavior; workspace-scoped `security_events`, policy config, quota counters, content-trust,
  retention-tombstone foundations; admin-only security posture/event APIs+UI.
- **Data/control flow**: input guardrails scan upload metadata/content samples, search/answer
  queries, and research purpose/question text *before* they do anything expensive. Output
  guardrails scan generated answers/research reports *before* persistence/return, so secret-like
  model output fails closed instead of being stored as a valid answer.
- **Key decisions**: D35 — deterministic local guardrails + persisted security events as the
  default assurance baseline; pattern-based scanners are simple and reproducible on purpose (not a
  substitute for classifier/human red-team review, but a real fail-closed floor).
- **Key schema/algorithm**: `quota_counters` keyed `(workspace_id, actor_user_id, operation,
  window_start)`, fixed-window, incremented atomically **before** expensive work. Egress policy
  fails closed for non-HTTPS, localhost/loopback/private/link-local/reserved/multicast, and
  metadata-service targets (SSRF defense). Redactor masks API-key-like values, labeled secrets,
  passwords, emails before they reach an error or security-event row.
- **Security**: `security_events` are admin-readable only — members/viewers can't see security
  telemetry; event metadata is redacted by construction, never raw secrets/prompts/document bodies.
- **Failure scenarios**: quota exhaustion → stable resource-exhausted error + a separate blocked
  security event, even though the user's request itself fails; guardrail-scan failure fails closed
  (block), not open.
- **Tests/gates**: prompt-injection/secret blocking, redaction canary, admin-only visibility, quota
  exhaustion, SSRF-safe egress, zero-cost posture. `apps/api/tests/test_phase10_security.py`.
- **Trade-off**: pattern-based scanners catch known classes, not everything — explicitly not a
  replacement for model-assisted classifiers or human red-teaming; Redis/distributed rate limiting
  deferred, Postgres fixed-window counters are authoritative for now.
- **Interview framing**: "How do you defend against prompt injection from retrieved/tool content?"
  → treat all crossing-boundary content as data, never instructions (system/developer policy always
  outranks it); scan both directions (input *and* output); fail closed on scanner ambiguity; keep
  guardrail evidence in an auditable, redacted event trail.
- **Pointers**: `phase-10` tag; `docs/decisions.md` D35; `docs/threat-model.md` §AI-specific policy,
  §Phase 10 review.

---

## Phase 11 — Scale evidence, observability, deployment hardening

- **Before**: the product is functionally complete through Phase 10; no visibility into its own
  operational posture, no CI/container/IaC artifacts, no capacity/SLO documentation.
- **Problem**: prove production-readiness *without* provisioning anything billable — observability,
  operations posture, deployment artifacts, all zero-cost.
- **Shipped**: local no-content telemetry (request/trace IDs, route metrics, SLO summary);
  admin-only operations posture API/UI (dependency, capacity, cost, runbook summaries); Dockerfiles
  for all 3 services; GitHub Actions CI; plan-only AWS/Terraform baseline; zero-cost artifact
  validator (`tools/ops/validate_phase11_artifacts.py`).
- **Data/control flow**: API middleware stamps `X-Request-ID`/`X-Trace-ID` and records bounded
  in-memory metrics by route template/method/status/latency. Telemetry **excludes** request/response
  bodies, prompts, chunks, document text, provider payloads, credentials — content-off by default.
- **Key decisions**: D36 — local no-content telemetry + protected posture + plan-only IaC as the
  final baseline; hosted observability/AWS provisioning/OpenSearch/managed queues remain explicit
  opt-in requiring approval + evidence, not something this phase claims to already run.
- **Key schema/algorithm**: internal metrics require `X-Atlas-Internal-Token`; production config
  fails closed if that token is missing/too short. Readiness checks the DB dependency and returns a
  typed dependency-unavailable error if unreachable; liveness stays lightweight (doesn't check DB).
- **Security**: operations posture visible only to owners/admins via existing `security:read`
  permission; artifact validator asserts CI never applies Terraform / requests AWS credentials, the
  Terraform baseline has zero `resource` blocks, and local Postgres remains the default demo
  dependency.
- **Failure scenarios**: DB unreachable → readiness fails typed and explicit, not a generic 500;
  missing internal token → internal metrics endpoint fails closed, not silently permissive.
- **Tests/gates**: contracts, migration no-op, artifact validation, lint/typecheck/tests/build,
  internal-token protection, production-config guard, cross-tenant operations denial.
  `apps/api/tests/test_phase11_operations.py`; `pnpm ops:validate`.
- **Trade-off**: in-memory telemetry is not a production metrics backend (no persistence, no
  dashboards, no alert routing) — explicitly named as deployment work, not pretended to be solved.
- **Interview framing**: "How do you demonstrate production-readiness without a cloud bill?" → a
  validator script that asserts the negative space (no billable resources declared, no Terraform
  applied in CI) is just as real a piece of engineering as the positive-space features — it's proof
  the zero-cost invariant can't silently regress.
- **Pointers**: `phase-11` tag; `docs/decisions.md` D36; `tools/ops/validate_phase11_artifacts.py`;
  `docs/operations-hardening.md`.

---

## Cross-phase note: no Phase 12

There is no numbered Phase 12 contract in the implementation repo. If a future session is tempted
to "continue the phases," that's out of scope for this learning vault and out of scope for the
implementation repo unless the user explicitly authorizes new phase work there — see the
implementation repo's own `CLAUDE.md` phase-discipline section (preserved in `project-reference/`).
