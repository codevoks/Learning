# Forge AI — revision cheatsheet

Compact quick-review only. Full detail lives in
[`00-mental-model.md`](00-mental-model.md)/[`01-phases.md`](01-phases.md)/
[`02-concepts.md`](02-concepts.md)/[`03-architecture-flows.md`](03-architecture-flows.md)/
[`04-interview-questions.md`](04-interview-questions.md) — don't duplicate the full documentation
here, just the fast-recall layer.

## One-line mental model

Durable, tenant-isolated agent/workflow platform. Postgres-authoritative, Redis-disposable. Model
proposes; application code authorizes/approves/budgets/executes/terminates. No RAG, no vector DB.

## Invariants (recite these cold)

- Postgres authoritative; Redis disposable — losing Redis delays work, never loses acknowledged state.
- Current-state tables + append-only events, written together, one transaction.
- Transactional outbox, at-least-once delivery, idempotency everywhere.
- DAGs for structure; loops only inside bounded state machines (never graph cycles).
- Immutable versioned snapshots (workflows, plans, tools, policy, model config) — replan = new version.
- Application code owns authorization, risk, approval, budgets, validation, termination — always.
- Approval binds the exact canonical action (hash) — distinct from authorization.
- No exactly-once claim for external effects — intent ledger + idempotency key + reconciliation; `outcome_unknown` when ambiguous.
- UUIDv7, UTC timestamptz, integer `version` for optimistic concurrency.
- Narrow ports for model/queue/tool/engine/secrets/telemetry — no provider SDK leakage into domain/application.
- No microservices split without measured contention/ownership/security evidence.
- Zero-cost path is permanent: `FORGE_EXTERNAL_INTEGRATIONS=disabled` by default; a credential in env never auto-activates billing.

## Execution flows (one line each — full diagrams in `03-architecture-flows.md`)

- **Run create**: API validates → 1 txn writes run+tasks+outbox → dispatcher polls → publishes → worker claims.
- **Tool call**: grant check → schema validate → canonicalize+hash → invocation ledger → (approval if `simulated_effect`) → budget reserve (`try_reserve`) → adapter → evidence (trust label) → event.
- **Approval**: bound by SHA-256(sorted-key JSON of tenant/workspace/run/task/invocation/tool-version/action-hash/canonical-args) → self-approval forbidden → decision commits before response → consumed exactly once.
- **Agent loop**: perceive → decide (strict schema) → validate against `allowed_tools` snapshot/budget → act (same tool path) → observe → checkpoint (`agent_iterations`) → repeat until complete (citation-checked)/fail/limit.
- **Recovery**: lease expires → `SELECT...FOR UPDATE SKIP LOCKED` → task → `ready` → republish → (post-audit) release orphaned budget reservation, all one txn.
- **MCP**: discover → quarantined snapshot → admin enable → ordinary `origin=mcp` tool_versions row → identical pipeline → result always `untrusted_tool_output`.
- **Multi-agent**: deterministic router filters graph pre-persistence → same DAG scheduler → isolated specialists (task-scoped evidence) → deterministic synthesizer reads `task_dependencies` → never calls a model.

## Phase → one artifact each (fast recall table)

| Phase | Signature artifact |
|---|---|
| 1 | RLS + JWT/OIDC + RBAC |
| 2 | Immutable workflow DAG + state machines |
| 3 | Transactional outbox + recovery scan |
| 4 | `run_tool_grants` + `outcome_unknown` |
| 5 | `ModelProvider` port + validated `plan_versions` |
| 6 | `approval_binding_hash` (exact-action approval) |
| 7 | `AgentRuntime` + `agent_iterations` |
| 8 | `LangGraphAgentRuntime` + `ForgeLangGraphCheckpointer` |
| 9 | `LangChainDeterministicModelProvider` (real `Runnable` chain) |
| 10 | Debugger: cursor feed + projection verify + blocked effect replay |
| 11 | `MCPClientPort` + quarantine-until-admin-enabled |
| 12 | `Router` + `SpecialistAgentRuntime`/`SynthesizerRuntime` |
| 13 | `try_reserve` atomic budget UPDATE + real OTel + Temporal rejected (Q-005) |
| audit | Budget-orphan-on-crash bug found+fixed; README rewritten |

## Terminology quick-defs

- **Outbox pattern**: write state change + outgoing message in one transaction; a separate
  dispatcher publishes — eliminates "wrote but didn't notify" gap.
- **Fencing token**: a monotonically increasing value tied to a lease, so a late/zombie worker
  can't clobber work claimed by a newer attempt.
- **Confused deputy**: an authorized actor tricked into misusing its authority on someone else's
  behalf — Forge's defense is that tenant/user/account fields always come from actor context, never
  model-supplied arguments.
- **Reserve-before-work**: allocate budget atomically before doing the work, settle after — avoids
  check-then-act races.
- **`outcome_unknown`**: explicit third state (besides success/failure) for effects whose result
  can't be confirmed.
- **Trust label**: provenance tag (`trusted_local_fixture` / `untrusted_tool_output`) that travels
  with content and prevents it from ever being promoted to instruction.

## Trade-offs to have ready

- Temporal rejected: evidence-backed (`capacity-report` numbers), not "Temporal is bad."
- No vector DB: evidence-gated ADR (Q-008), not "RAG is bad" — just not built without a concrete
  use case + eval dataset.
- Multi-agent opt-in only (Q-006): proven overhead via `MultiAgentComparisonService`, not assumed benefit.
- No microservices split (D-001): needs measured contention/ownership/security evidence first.
- Package install ≠ coverage: LangChain/LangGraph are genuinely wired and tested; LangSmith live
  export and cloud deployment are honestly flagged as never exercised.

## Weak-spot placeholder

Fill this in per revision session from `LEARNING-STATUS.md`'s "Weak areas" — don't let this file
go stale; it's meant to be edited, not just read.
