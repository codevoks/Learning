# Atlas AI — interview question bank

Grounded Q&A. Answers are compressed to the core defensible claim + why — expand out loud in an
actual interview, don't recite verbatim. Cross-reference `01-phases.md`/`02-concepts.md` for depth.
Track which of these have been drilled in `LEARNING-STATUS.md`.

## Data/storage decisions

**Q: Why Postgres for everything, including vectors — why not a dedicated vector DB?**
A: One authoritative store means one transaction boundary and one place tenant filters can't be
forgotten (D03, D09). At demo/early scale, exact-cosine over JSONB is fine. pgvector/ANN is an
explicit evidence gate — adopted only after corpus-size/recall/latency curves justify it, not
because "vector DBs are what everyone uses." The retrieval *interface* doesn't change when the
index does — only implementation and infra.

**Q: Isn't storing vectors as JSONB slow?**
A: Yes, O(n) per query — acceptable at the current scale, explicitly called out as a baseline, not
a final answer. The whole point of the adapter boundary (`SemanticRetriever.search`) is that
swapping in pgvector HNSW later is a config/migration change, not a rewrite.

**Q: Why not Redis for the job queue from day one?**
A: D07 — avoid premature queue infrastructure. Postgres `FOR UPDATE SKIP LOCKED` gives real
concurrent-safe job claiming without standing up a broker. A dedicated broker gets adopted only
once throughput, isolation, or delay/retry-semantics evidence demands it — and Redis specifically
must never be the *only* durable record even if introduced later (it stays non-authoritative).

## Retrieval

**Q: Why hybrid retrieval — why isn't semantic search enough?**
A: Semantic and lexical retrieval have complementary failure modes — semantic misses exact
keyword/vocabulary matches it wasn't trained to weight highly; lexical misses paraphrase/semantic
similarity. Fusing both, under the *same* authorization filters on each branch, covers more of the
query space than either alone.

**Q: Why RRF instead of weighted score fusion?**
A: Semantic cosine distance and lexical rank aren't on a comparable scale — you'd need calibration
to combine them meaningfully. RRF only needs *rank position*, not calibrated scores, so it's robust
with zero tuning. Weighted/learned fusion stays behind an evaluation-evidence gate (D10, D20).

**Q: How do you decide whether to add a new retrieval technique (e.g. query expansion, reranking)?**
A: Evidence-gated ablation against the Phase 7 evaluation harness — same production services, a
fixed offline dataset. Phase 8's query expansion shipped *because* an ablation showed a specific
vocabulary-mismatch slice go from zero recall to full recall. Anything without that kind of evidence
stays deferred (D20).

## Generation / citations

**Q: How do you stop the model from hallucinating a citation?**
A: Don't trust model output formatting at all. A *separate* deterministic validator, running after
generation, checks each citation marker's span and quoted text against the exact `AnswerEvidence`
snapshot that was frozen *before* generation ran. Status is `resolvable / span_matched / supported /
rejected` — not synonyms. An answer is citation-verified only if every claimed evidence identity was
actually supplied and authorized.

**Q: What happens if there's no supporting evidence for a question?**
A: A labeled refusal — a first-class outcome, not an error and not an unsupported-but-confident
answer. This is tested explicitly (`test_generation.py`).

**Q: Why is generation synchronous and non-streaming?**
A: D31 — streaming needs a separate design for safely validating *partial* output (you can't
citation-validate a half-generated sentence the same way). Deferred deliberately, not an oversight.

## Tenant isolation / security

**Q: How is tenant isolation actually enforced — walk me through a request.**
A: Authentication establishes a subject. Workspace access is *derived* from active membership
lookup, never from a client-supplied workspace ID. Application use cases authorize a named action
against a typed resource *before* any repository mutation — the check lives in `application`, not
only in routes. Every query starts workspace-scoped; composite `(workspace_id, id)` keys make a
child row structurally unable to reference another tenant's parent.

**Q: Why return 404 instead of 403 for cross-tenant access?**
A: 403 confirms the resource exists (just not for you) — that's an information leak about another
tenant's data. A non-disclosing 404 leaks nothing. Consistent across every retrieval branch and
mutation.

**Q: How do workers know which tenant a job belongs to — can a malicious job payload claim a
different workspace?**
A: Workers derive tenant scope from the authorized, immutable job record in Postgres, never from
message payload alone. There's no transport payload that could smuggle a different `workspace_id`
in and have it trusted.

**Q: How do you defend against prompt injection from retrieved or tool content?**
A: Treat everything crossing a trust boundary as data, never instructions — system/developer policy
always outranks it. Concretely: deterministic input guardrails scan for indirect-injection and
secret-exfiltration patterns before expensive work runs; output guardrails scan generated
answers/reports before persistence; both fail closed on ambiguity. In the research workflow,
forbidden-tool/URL/secret requests in the input are rejected *before* the run is even persisted.

**Q: What's your SSRF defense for the research agent's tools?**
A: The tool set is allowlisted to exactly two: `atlas_retrieval` and `local_policy_catalog` —
neither makes arbitrary outbound HTTP. The egress-policy primitive itself fails closed for
non-HTTPS, localhost/loopback/private/link-local/reserved/multicast, and metadata-service targets,
as a defense-in-depth layer even though the default tool set doesn't currently exercise it.

## Idempotency / failure handling

**Q: Where is idempotency actually required, and how do you implement it?**
A: Upload finalization, workspace creation, and research tool invocations. Pattern: a stable
idempotency key (actor + operation + request-hash or explicit key), stored with the
request/response, checked before re-executing a side effect — a retry returns the *same* result
instead of duplicating it. Workspace creation additionally serializes with a Postgres advisory lock
to close a race between concurrent identical requests (D22).

**Q: What can be processed twice in Atlas, and what can't?**
A: Ingestion is explicitly *at-least-once*, made safe by idempotency + atomic publish, not
exactly-once (D06 — "exactly-once side effects are unrealistic for a system with real providers and
workers that fail"). What can't happen twice: a document version publishing twice, a workspace
being created twice for the same idempotency key, a research tool invocation re-executing a
non-idempotent effect on resume (guarded by stable tool idempotency keys).

**Q: What happens if a worker crashes mid-ingestion?**
A: Its lease expires (no heartbeat); another worker claims the same durable job row via `FOR UPDATE
SKIP LOCKED` with an expected-version check. Publication requires a valid lease owner and expected
job version, so a worker that lost its lease can't corrupt state even if it's still technically
running. Recovery is "another worker claims the same row," not a bespoke crash-recovery path.

**Q: What are Atlas's consistency guarantees?**
A: Strong: membership/role changes, upload finalization metadata, active document-version
publication, budget reservation, idempotency registration, approvals. Eventual: upload-to-search
visibility (bounded by the job state machine), cache invalidation (n/a today, no cache layer yet),
derived search projections, observability export. Read-your-writes for metadata; search visibility
begins only after atomic publish.

## Agentic / research workflow

**Q: Why not a general autonomous agent for research?**
A: D15/D16 — deterministic workflows first; agents only for bounded, measurable tasks with explicit
tools/budgets/termination/checkpoints. No multi-agent runtime without benchmark evidence it beats a
single bounded workflow enough to justify coordination/evaluation cost. Phase 9 is deliberately
narrow: 2 allowlisted tools, fixed budget, mandatory human approval before the one consequential
step (synthesis).

**Q: How do you stop an agent from doing something irreversible?**
A: Allowlist tools to the minimum needed (no shell/arbitrary HTTP/code exec); require a *fresh*
authorization check plus explicit human approval before the consequential step, checked against a
*current* approval version (stale approvals fail as conflicts, not silent passes); make every tool
call idempotent so resuming a run never double-executes a side effect.

**Q: Why build the deterministic `ResearchGraph` boundary instead of just using LangGraph directly?**
A: D34 — proves the workflow/data/security contract (durable state, checkpoints, idempotent tool
records, budgets, approval gates) without adding a runtime dependency until checkpoint/retry/
failure-mode evidence justifies the swap. The adapter boundary means adopting LangGraph later is a
implementation swap behind a fixed interface, not a redesign.

## Evaluation

**Q: How do you know your RAG system actually works, beyond "it looks right in the demo"?**
A: A versioned offline evaluation harness (Phase 7) running over the *production* retrieval/answer
services — not copied metric-only logic, so regressions can't hide behind test-only code paths.
Hidden labels (expected answers, relevant chunks) are used only by the metric layer *after* the
system-under-test produces output, preventing leakage into retrieval/generation. Concrete numbers:
Recall@5 = 1.0, MRR = 1.0, citation-verified rate = 1.0 on the regression case set.

**Q: What's the difference between a metric failure and a system failure in your evaluation runs?**
A: They're distinct statuses, deliberately not collapsed — failed system execution, metric-compute
failure, and missing labels are each tracked separately so an aggregate score can never silently
absorb an unsafe or incomplete case.

## Scale / trade-offs

**Q: What would change at 100x scale?**
A: First: separate worker pools and quotas by workload/tenant, add DB replicas/partitioning and
connection controls, batch embeddings. Move derived search to something like OpenSearch *only* if
measured Postgres limits or search-feature needs justify the operational cost — not preemptively.
Likely first real bottlenecks: external-model quota/latency (once a hosted provider is enabled),
parsing CPU/memory, vector-index recall/latency, Postgres I/O, unbounded context — not the web tier.

**Q: At 10M documents, what changes?**
A: Evaluate sharding/partitioning by tenant, dedicated placement for large tenants, asynchronous
index projections, and reindex backfills. Explicitly: no single topology is promised for every
tenant-size distribution — that's a stated architecture-doc position, not a gap.

**Q: Why not microservices from the start?**
A: D02 — modular monolith control/query plane plus a separate worker process, fixed *initially*.
Maximizes learnability and transactional clarity while the system is young; service decomposition
is deferred until ownership, scaling, or failure-isolation evidence exists — not assumed as a
default "real systems use microservices" move.

**Q: Why deterministic local adapters instead of just calling a real LLM/embedding API?**
A: Zero-cost default path (tests/CI/demo never require a paid key or network egress) plus
reproducibility (deterministic output makes tests and evaluation runs stable). Every provider sits
behind a typed port (`EmbeddingProvider`, `Generator`, `Reranker`) with the deterministic fake as
default implementation — swapping in a hosted provider is a config change behind the same
interface, gated by its own quality/latency/cost evaluation pass before being enabled anywhere.

**Q: This all sounds deterministic and "toy" — how do you defend it as production-grade engineering?**
A: The *architecture* is production-shaped even though the default *providers* are deterministic —
tenant isolation, idempotent job state machines, post-validated citations, human-approval gates,
fail-closed guardrails, and an evaluation harness are all real, tested, enforced-in-code properties,
independent of which model is plugged in behind the adapter boundary. The honest, explicit
"Known limitations" list in the README (text/Markdown only, no malware scanning, no pgvector yet,
not deployed to live cloud) is itself evidence of engineering discipline, not a weakness to hide.

## Fast-fire (one-liners for warm-up drilling)

- Why S3-compatible object storage for blobs and not Postgres? → Large blobs don't belong in the
  transactional store; a DB row keeps tenant-scoped key/digest/size/lifecycle metadata instead.
- What's the difference between a `Document` and a `DocumentVersion`? → Document = stable logical
  identity; DocumentVersion = immutable content snapshot; only one version is active/published.
- Why can citations be `span_matched` but not `supported`? → Different validation stages — the
  quote text can resolve to the right character span in evidence without necessarily being judged
  as semantically supporting the specific claim; they're deliberately not conflated.
- Why does egress policy fail closed on scheme/host ambiguity? → Because ambiguity in a
  security-relevant decision defaults to deny, per the incident-safe failure rules.
- What's the one sentence for "why doesn't Atlas have a full autonomous multi-agent system"? → No
  benchmark evidence yet that coordination overhead pays off over one bounded workflow (D16).
