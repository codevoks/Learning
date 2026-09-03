# Atlas AI — five-minute revision cheatsheet

For the morning-of-an-interview refresh. If any line doesn't fully make sense, go read its section
in `01-phases.md` / `02-concepts.md` before the interview, don't wing it.

## The one-liner

Multi-tenant RAG + bounded-research SaaS where tenant isolation, citation integrity, idempotent
async processing, and human-approval gates are enforced in code — and the whole golden path runs
at $0 on local Postgres + deterministic AI adapters.

## The five things to never get wrong

1. **Tenant isolation is server-derived from membership, never from a client-supplied ID.**
   Cross-tenant access → non-disclosing `404`.
2. **Citations are validated after generation**, against a frozen evidence snapshot the model
   never influenced. Status: resolvable / span_matched / supported / rejected — not synonyms.
3. **Nothing is searchable until a document version atomically publishes as READY** — chunks and
   embeddings become visible in the same transaction as the version flip.
4. **Research synthesis is blocked on a fresh, current human approval** — stale approval version
   fails as conflict; denial → CANCELLED, nothing generated.
5. **Postgres is the sole authoritative store**, including the current exact-cosine vector
   baseline — pgvector/OpenSearch/Redis-as-authority are all explicit, evidence-gated non-decisions,
   not gaps.

## Phase order (memorize the shape, not just the list)

0 design → 1 tenancy/auth → 2 upload/jobs → 3 parse/chunk → 4 embed/semantic search → 5 lexical +
hybrid (RRF) → 6 generate + verify citations → 7 evaluate → 8 evidence-gated query expansion → 9
bounded research + approval → 10 guardrails/security → 11 observability/ops hardening.

Pattern: **build the deterministic core end-to-end first (0–7), prove one advanced-RAG technique
with evidence (8), add the agentic layer only after that (9), consolidate security (10), prove
production-readiness without spending money (11).**

## Ingestion state machine (say it in one breath)

`PENDING → CLAIMED → VERIFYING → PARSING → NORMALIZING → CHUNKING → EMBEDDING → PUBLISHING →
SUCCEEDED`, with `RETRY_WAIT` and `CANCEL_REQUESTED/CANCELLED` branches, leased via `FOR UPDATE
SKIP LOCKED` with heartbeats and expected-version checks at publish time.

## Research state machine

`PENDING → RUNNING → WAITING_APPROVAL → SUCCEEDED`, `CANCELLED` from most states (incl. on denial),
terminal also includes `FAILED / BUDGET_EXHAUSTED / TIMED_OUT`.

## Retrieval in one sentence

Semantic (exact cosine over Postgres JSONB) + lexical (Postgres FTS) run under **identical**
tenant/status filters, deduped by `(chunk_id, document_version_id)`, fused with deterministic RRF
(`score = Σ 1/(k + rank_i)`) — no score calibration needed.

## The ADR numbers worth having on the tip of your tongue

- **D03/D09** — Postgres is sole authority incl. vectors; pgvector is an evidence gate.
- **D06** — ingestion is idempotent at-least-once, not exactly-once.
- **D07** — DB-backed job claiming before a broker; Redis never becomes authoritative.
- **D10** — RRF as the fixed fusion baseline; weighted fusion needs evaluation evidence.
- **D11** — evidence is typed/versioned; citations post-validated, never trusted from formatting.
- **D12** — provider-neutral ports, deterministic local fakes as default, paid providers opt-in.
- **D15/D16** — deterministic before agentic; no multi-agent without benchmark evidence.
- **D20** — evaluation gates advanced retrieval/agent complexity/OpenSearch/optimization changes.
- **D27** — zero-cost build/test/demo path is a fixed invariant across every phase.
- **D31** — deterministic generation + post-validation is the gate; streaming deferred.
- **D34** — deterministic `ResearchGraph` boundary before adopting LangGraph as a dependency.
- **D36** — local no-content telemetry + plan-only IaC as the final production-hardening baseline.

## Deferred / NOT implemented — say this list out loud, it's a strength

- pgvector/ANN indexing, OpenSearch, Redis-backed coordination — all evidence-gated, not built.
- PDF/Office/OCR/archive ingestion — text/Markdown only today.
- Hosted LLM/embedding/reranking/judge providers — deterministic local fakes are the default;
  hosted adapters exist as opt-in, unevaluated-in-this-repo code paths.
- Malware scanning, enterprise DLP/KMS/HSM, SSO/SCIM, external penetration testing.
- Multi-agent runtime — no benchmark evidence yet that it beats one bounded workflow.
- Live AWS provisioning — `infra/aws/` is plan-only Terraform, zero resource blocks.
- Redis/distributed rate limiting — Postgres fixed-window counters are authoritative today.
- Streaming generation — safe partial-output validation needs its own design.

## Real numbers (from the README, actually run in-repo)

`pnpm test → 54 tests passed (49 API · 4 worker · 1 web)` · `pnpm ops:validate →
phase11_artifact_validation=passed, billable_provisioning=disabled, terraform_resources=0` ·
offline eval: Recall@5 = `1.0`, MRR = `1.0`, citation-verified rate = `1.0` on the regression set.

## Layering (say this for any "walk me through the code" question)

`domain → application → infrastructure/retrieval/ai/api`. Imports point inward: domain has no
framework/provider dependency; application depends on ports (interfaces); infrastructure implements
ports; routes/job consumers adapt external input to the domain. This is ports-and-adapters /
hexagonal architecture, applied to both `apps/api` and `apps/worker`.

## Non-disclosing 404 — the answer that always lands

403 confirms a resource exists in a tenant you can't see (an information leak). 404 leaks nothing.
Used consistently across every retrieval branch and mutation in Atlas whenever cross-tenant access
is attempted.
