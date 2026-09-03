# Atlas AI — core concepts

Format: **concept → Atlas mechanism → code/doc pointer → why → trade-off**. Grounded in the
implementation repo; verify pointers if it's been months since last checked (renames happen).

Only concepts actually implemented in Atlas are listed as "implemented" — this file is the primary
place the implemented-vs-hypothetical line matters, since a quick skim tempts overclaiming.

## Tenancy and access

**Workspace tenancy** → every tenant-owned row carries `workspace_id`; composite `(workspace_id,
id)` keys where practical so a child row can't accidentally reference another workspace → `docs/data-model.md`
§Conventions, `memberships` table → why: defense in depth, not just an app-layer filter → trade-off:
no row-level-security (RLS) yet — considered *after* repository-level policy tests are proven (D04).

**Authentication/authorization** → dev: deterministic local identities (Alice Owner/Bob Member),
prod: OIDC/JWKS verifier boundary (issuer/audience/expiry/subject/email validated) → `docs/decisions.md`
D21, `apps/api/tests/test_authentication.py` → why: tests/demos must never depend on a live IdP →
trade-off: production auth is a real boundary that's never been exercised against a live IdP in
this repo — it's a code path, not a deployed proof.

**Tenant isolation** → authorization derived server-side from active membership; a client-supplied
workspace ID never grants authority; cross-tenant reads return non-disclosing `404` → checked in
`application`, before any repository mutation, not only in routes → why: correctness property, not
a filter bolted on later → trade-off: coarse role-based model (owner/admin/member/viewer), no
per-resource ACL yet (D05).

**RBAC** → permission names are stable actions ("document:read"), role membership is data, policy
evaluation is application logic → `docs/threat-model.md` §Authorization and tenant isolation model
→ why: keeps authorization centralized and testable, not scattered `if role ==` checks.

## Ingestion

**Async/durable job processing** → explicit state machine `PENDING → CLAIMED → VERIFYING → PARSING
→ NORMALIZING → CHUNKING → EMBEDDING → PUBLISHING → SUCCEEDED`, leases with `FOR UPDATE SKIP LOCKED`,
heartbeats, bounded attempts, `RETRY_WAIT`/`CANCEL_REQUESTED`/`FAILED` branches → `docs/data-model.md`
§Jobs → why: providers and workers fail; D06 — "exactly-once is unrealistic; uniqueness + checkpoints
+ atomic publish create effective-once outcomes" → trade-off: Postgres-backed, not a dedicated
broker — deliberate (D07), revisit only with throughput/isolation evidence.

**Idempotency** → stable idempotency keys on upload finalization, workspace creation, tool
invocations; request/response hash stored so a retry returns the *same* result, not a duplicate
side effect → `idempotency_records` table, D22 → why: retries are inevitable in a distributed
system; idempotency is what makes retry safe instead of dangerous.

**Parsing/normalization** → allowlisted deterministic text/Markdown parser; unsafe inputs (binary
magic bytes, archives, invalid UTF-8, oversized input) fail safely, no publish → D28 → why: format
support is an attack-surface decision, not just a feature checkbox → trade-off: PDF/Office/OCR
explicitly deferred behind a not-yet-built parser-sandbox boundary.

**Chunking** → deterministic, immutable, one document-version each, ordinal + content hash +
chunker version → `chunks` table → why: content hash + version let you detect/dedupe identical
reprocessing and keep citations stable across re-ingestion.

**Provenance** → every chunk/embedding/answer/evaluation row records the parser/chunker/embedding
provider-model-version/prompt-version that produced it → D13 (cross-cutting ADR) → why:
reproducibility and safe migration — never silently compare data produced by incompatible configs.

## Retrieval

**Embeddings** → deterministic local hash-embedding provider by default; `embedding_sets` record
provider/model/version/dimension/normalization; `chunk_embeddings` are one row per `(chunk_id,
embedding_set_id)` → D29 → why: zero-cost default, adapter-compatible with a real hosted provider
later → trade-off: not semantically rich like a real transformer embedding — a *correctness*
baseline, not a *quality* baseline.

**Vector retrieval** → exact cosine similarity over vectors stored as **Postgres JSONB** (not
pgvector) → D09 → why: one authority/transaction boundary, no extra infra, matches the plain
Postgres compose image today → trade-off: O(n) scan, not ANN — pgvector adoption is an explicit
evidence gate (corpus size + recall/latency curves), not implemented.

**Lexical retrieval** → Postgres full-text search (`websearch_to_tsquery`, English config) over a
GIN expression index on `to_tsvector('english', chunks.text)` → D30 → why: keeps lexical search
inside the same tenant-filtered authority boundary, no managed search service needed.

**Hybrid retrieval / RRF** → semantic + lexical candidates generated under **identical** policy
filters, deduped by `(chunk_id, document_version_id)`, fused with deterministic **Reciprocal Rank
Fusion**: `score = Σ 1/(k + rank_i)` per branch → D10 → why: RRF needs only rank, not calibrated
scores — semantic distance and lexical rank aren't comparable scales → trade-off: weighted/learned
fusion is evaluation-gated (D20), not implemented.

**Ranking / advanced RAG (query expansion)** → `phase8-multi-query-expansion-v1`: deterministic
fixed synonym mapping, bounded fan-out, branch provenance recorded → D33 → why: the *only* advanced
RAG technique enabled by default, and only because a Phase-7-harness ablation proved it moved a
named slice from zero recall to full recall → trade-off: not a general semantic rewriter; an LLM
query rewriter would need paid/hosted inference and isn't the zero-cost default.

## Generation and evidence

**Grounded generation** → deterministic local generator receives *only* the supplied evidence
context (no tools, no secrets, no network) → D31 → why: correctness baseline that proves the
data/instruction separation and context-budgeting contract before a hosted model is ever wired in.

**Evidence handling** → `AnswerEvidence` freezes the *exact* authorized context/ranks/scores
supplied to generation, immutably, before the model runs → `docs/data-model.md` §Evidence, answers,
citations → why: makes "what did the model actually see" independently checkable after the fact,
not reconstructed from the prompt.

**Citation verification** → a *separate* validator checks every citation marker's span+quote
against the frozen `AnswerEvidence`, **after** generation → status ∈ `resolvable | span_matched |
supported | rejected` (not synonyms) → D11 → why: never trust citations because they're
well-formatted; verify structurally against ground truth the model didn't get to fabricate.

## Idempotency, retries, recovery (cross-cutting)

**Idempotency** → see Ingestion above; also applies to tool invocations in research (Phase 9) and
answer/workspace creation.

**Retries and recovery** → bounded attempts, `next_attempt_at` backoff, lease expiry/reclaim;
**permanent** validation/auth/policy failures never auto-retry — only transient/classified failures
do → `docs/threat-model.md` §Incident-safe failure rules → why: retrying a permanent failure just
wastes budget and can amplify abuse; the failure taxonomy (validation / authorization / conflict /
transient dependency / permanent dependency / resource exhausted / cancelled / internal) exists
specifically so retry logic can make that distinction.

## Bounded research (agentic layer)

**Bounded research** → deterministic local `ResearchGraph`: plan → retrieve evidence → checkpoint →
wait for approval → synthesize → terminal state; states `PENDING/RUNNING/WAITING_APPROVAL/PAUSED` →
terminal `SUCCEEDED|FAILED|CANCELLED|BUDGET_EXHAUSTED|TIMED_OUT` → D15, D34 → why: "deterministic
before agentic" — most product flows need reliability, not autonomy; the agentic layer sits *on
top of* the proven deterministic RAG core, not instead of it.

**Human approval gates** → synthesis is blocked until an authorized user submits a **current**
approval version; stale approvals fail with conflict; denial → `CANCELLED`, nothing generated
without sign-off → `approvals` table, optimistic-versioned → why: sensitive/externally-consequential
actions require a *fresh* authorization check, not a permission checked once at run start.

**Prompt-injection defenses** → retrieved/tool content is data, never instructions; system/developer
policy always outranks it; input guardrails reject forbidden-tool/URL/secret requests *before* run
persistence → `docs/threat-model.md` §AI-specific policy → why: the confused-deputy risk in
agentic systems is exactly "untrusted content directs a privileged action" — cut it off at the
data/instruction boundary, not by trying to detect every bad output downstream.

**Secret-leak/security guardrails** → deterministic pattern-based scanners (API-key-like values,
labeled secrets, passwords, emails) on both input and output, fail-closed; redactor masks matches
before they reach an error or a `security_events` row → D35 → why: known-class coverage that's
reproducible and auditable, explicitly not a substitute for model-assisted classifiers.

## Evaluation

**Evaluations / Recall@K / MRR / citation integrity** → versioned datasets, immutable labeled cases,
deterministic offline runs over the *production* retrieval/answer services; hidden labels used only
by the metric layer *after* system output exists (no leakage into retrieval/generation) → D32 →
why: metrics computed against copied/mocked logic can hide the exact regressions that matter;
real README numbers: Recall@5 `1.0`, MRR `1.0`, citation-verified rate `1.0` on the regression set.

## Observability and cost

**Observability/telemetry** → route-level metrics + request/trace IDs, in-memory, no content
capture by default (no bodies, prompts, chunks, document text, credentials) → D17, D36 → why:
telemetry must correlate requests without becoming a second copy of sensitive tenant data →
trade-off: not a production metrics backend — no persistence/dashboards/alerting; hosted export
(e.g. OpenTelemetry collector, Langfuse) stays opt-in.

**Deterministic zero-cost adapters** → every external-facing capability (embedding, generation,
reranking, evaluation judge) is a typed port with a deterministic local fake as the *default*
implementation → D12 → why: default tests/demos/CI never require a paid key; swapping in a hosted
provider is a configuration change behind the same interface, not a rewrite.

## Runtime/deployment boundaries

**Zero-cost, by construction** → the entire golden path runs on local Docker Postgres, local
filesystem object storage, deterministic dev auth, deterministic AI adapters — $0. Hosted providers
exist as adapter-compatible code paths but are opt-in and disabled by default everywhere (tests,
CI, local dev, demo) → D27 → why: a demoable, testable system that never accidentally racks up a
bill is itself a security/operability property, not just a cost-saving nicety.

**Plan-only infrastructure** → `infra/aws/main.tf` declares zero `resource` blocks,
`enable_billable_resources = false`; CI never applies Terraform or requests AWS credentials
(validated by `tools/ops/validate_phase11_artifacts.py`) → D36 → why: documents an intended
production shape without ever provisioning it — the "proof" is a validator asserting the *absence*
of billable resources, not just a claim.
