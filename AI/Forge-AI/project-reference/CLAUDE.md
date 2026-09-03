# Claude Code operating guide — Forge AI

This file is a **local-only** operating guide for Claude Code sessions in this repository. It is not committed (see "Privacy and Git handling" below) and is not a substitute for project rules.

## Authority

`AGENTS.md` (repository root) is the canonical, permanent source of project instructions. **Read `AGENTS.md` in full before doing any project work.** If anything in this file ever conflicts with `AGENTS.md`, `AGENTS.md` wins — unless the user explicitly overrides it in the current conversation. This file distills `AGENTS.md` into a Claude-Code-shaped operating manual; it does not add, loosen, or replace any of its rules.

## Project identity

Forge AI (`forge-ai` in `package.json`) is a durable, tenant-isolated **agent and workflow platform** built as a production-grade learning project — success is measured by whether the owner can design, implement, debug, and defend it, not merely run it. It is not a RAG/document product and has no vector store (see "Data & evidence invariants").

It starts as a **modular monolith**: three deployables (`apps/web`, `apps/api`, `apps/worker`) sharing PostgreSQL as the single authoritative store, with Redis as disposable coordination only. A deterministic runtime persists and schedules bounded tasks; models may propose structured plans and tool calls, but Forge application code always validates, authorizes, budgets, approves, executes, and terminates. The engineering bar is production-quality and interview-defensible: explicit typed control flow, narrow migrations, tenant scope everywhere, real security controls, and no fabricated evidence.

All 14 planned phases (Phase 00 system design through Phase 13) are marked complete in `docs/internal/status.md`. There is currently **no authorized next phase** — do not infer or start one; wait for the user to say "Proceed to next phase" and to point at (or approve creating) the relevant `docs/phases/phase-NN-<scope>.md`.

## Repository map

```
apps/web/       Next.js UI + same-origin browser facade — presents state, never decides authz/transitions
apps/api/       FastAPI command/query boundary — JWT verification, actor construction, policy, transactions
                  src/forge_api/{domain,application,policy,runtime,planner,tools,ports,infrastructure,api}
                  migrations/00N_<scope>.sql — one file per phase, forward-only
                  tests/ — pytest, `security` marker for adversarial suite
apps/worker/    Queue consumers, outbox dispatcher, abandoned-work recovery, task execution, graceful shutdown
packages/config/       Validated, non-secret shared configuration contracts
packages/shared-types/ OpenAPI-derived TS client/types (generated — do not hand-edit generated files)
docs/architecture/     Stable cross-phase contract — read before implementing anything (see read order below)
docs/phases/           Per-phase specifications (`phase-NN-<scope>.md`) and phase roadmap/gates
docs/internal/         Phase completion reports and `status.md` (phase history — internal only, never product UI)
scripts/        demo.mjs, backup-restore-drill.mjs, check-public-files.mjs, setup-python.mjs
infra/terraform/        Optional AWS topology — validate/plan only, never apply without explicit approval
```

Python backend code lives inside the owning app until two deployables genuinely need to share a stable concept; only then is it extracted to a package. Dependencies point inward: `domain/` imports nothing from web, database, queue, model, or provider SDKs.

## Before touching anything

1. Read `AGENTS.md` completely.
2. Read `docs/architecture/README.md` and follow its numbered read order for the architecture documents relevant to the work (requirements → system architecture → visual guide → domain/workflow model → data/API contracts → failure model → security threat model → scale/observability/cost → zero-cost demo → decisions → traceability → phase roadmap).
3. Check `docs/internal/status.md` to confirm which phase is actually current — do not trust memory or the roadmap summary.
4. If a phase is authorized, read **only** that exact `docs/phases/phase-NN-<scope>.md`. Do not read ahead into future phase specs to "prepare."
5. Inspect the actual current implementation (migrations, `src/forge_api/...`, tests) before assuming a doc still matches reality — architecture docs are the contract, but code is what runs.

## Architecture invariants

These must never be casually violated. A genuine need to change one requires a proposed ADR in `docs/architecture/decisions.md` (context, alternatives, security/failure/scaling impact, migration/rollback, evidence) — not a silent redesign.

- **PostgreSQL is authoritative; Redis is disposable.** Redis loss delays work but never loses acknowledged workflow state.
- **Current-state tables + append-only execution events, written together in one transaction.** Not full event sourcing; event folding is verification (see `debugger_projection_verifications`), not the only recovery path.
- **Transactional outbox, at-least-once consumers.** Every handler/side effect needs an explicit idempotency strategy; duplicates are expected, not exceptional.
- **DAGs for user/template/planner work; loops live inside bounded state machines, never as graph cycles.** Agent iteration is a state machine inside one task.
- **Immutable versioned snapshots** for workflow templates, plans, tool versions, policy, and model configuration. Replanning/changes append a new version; history is never rewritten. Emergency policy may only tighten, never loosen, a pinned run.
- **Code owns authorization, risk, approval, budgets, validation, termination.** Models propose; they are never a security boundary. LangChain/LangGraph/MCP output is untrusted data, always.
- **Approval binds the exact canonical action** (tenant, run, tool version, canonical args, action hash, risk, expiry, eligible approver) and is distinct from authorization — approval satisfies a gate, it grants nothing the caller didn't already have.
- **No exactly-once claim for external effects.** Use intent ledger + idempotency key + reconciliation; unresolvable outcomes are `outcome_unknown`, never silently retried or assumed successful.
- **UUIDv7 opaque IDs, UTC `timestamptz`, integer `version` for optimistic concurrency.**
- **Narrow ports** for model/queue/tool/workflow-engine/secrets/telemetry (`ports/`). No provider SDK leakage into domain/application code.
- **LangChain / LangGraph / LangSmith placement is fixed** (see `AGENTS.md` §"LangChain, LangGraph, and LangSmith placement" and `decisions.md` Q-011/Q-012/Q-004 for full detail):
  - LangChain: provider/message/prompt/structured-output/tool interop seam only, around the Phase 5 planner boundary.
  - LangGraph: an alternate `engine_kind=langgraph` orchestration strategy for the same bounded agent task; `workflow_engine_checkpoints` are sanitized comparison evidence, never an authority source.
  - LangSmith: opt-in, redacted, tenant-scoped, exporter-failure-isolated observability only; zero-cost profile runs without it.
  - Package install/import is not coverage — only genuine executed, tested, demonstrated, documented use counts, and never for a phase where it wasn't actually built.
- **No microservices split without measured contention, team ownership, or security isolation evidence** — see `decisions.md` D-001 and "Why not microservices now" in `system-architecture.md`.

## Security invariants

Application security policy outranks model output, always — see `docs/architecture/security-threat-model.md` for the full threat register and current per-area classification (protected/needs-validation/gap/not-applicable).

- **Tenant isolation is structural, not incidental.** Every tenant-owned record carries `tenant_id` (workspace-owned records also `workspace_id`); identity, queries, records, events, jobs, traces, and cache keys all carry explicit scope. Deny by default. RLS is defense in depth, not a replacement for scoped services.
- **Trust boundaries are explicit**: user/browser | web | API/policy | database/queue | worker/runtime | model provider | local tool/integration | MCP server | third-party content. Every crossing authenticates, validates typed/size-bounded data, propagates tenant/correlation identity, labels trust/provenance, and emits sanitized audit evidence. Queue possession alone grants no authority — workers reload durable scope and policy on every claim.
- **Tools are code/admin-registered immutable versions.** A hallucinated/unlisted/version-mismatched tool fails closed. Canonical arguments are schema-validated, normalized, policy-checked, and hashed; confused-deputy fields (tenant/user/account) come from actor context, never model arguments.
- **Tool output is data with provenance, never instruction.** It cannot change system instructions, permissions, budgets, or allowed tools. MCP tool output is always `untrusted_tool_output`, independent of local-vs-remote trust level.
- **Secrets are references only** (`secretref://...`), resolved just-in-time under a scoped workload identity. Never in prompts, context, events, logs, checkpoints, traces, or exceptions.
- **Budgets are reserve-before-work, settle-after**, enforced by a single conditional `UPDATE ... RETURNING` to close reservation races; exhaustion is a deterministic, fail-closed stop.
- **SSRF/egress controls**: deny private/loopback/link-local/metadata ranges; remote hosts are re-resolved and re-validated on every call (not only at config time), closing DNS-rebinding TOCTOU gaps.
- **Prompt-injection controls**: keep policy/capability outside natural-language prompts and enforce after every model decision; separate trusted instructions from quoted untrusted content; minimize context/privilege; require citations for consequential claims; validate structured output against strict schemas/enums/graph bounds; treat injection-indicator flags as advisory triage signals, never the security boundary itself.
- **No genuine security blocker may ship.** A phase does not pass with known cross-tenant access, model-controlled authorization, unbound approval, a logged secret, an unbounded loop/cost, a default-replayed effect, or an external-fetch tool without network destination controls.
- When a phase introduces a new AI/agent/tool/workflow/MCP/retrieval/external-content attack surface, classify it as `protected and verified`, `implemented but needing deeper validation`, `genuine gap/blocker`, or `not applicable yet` in the phase report, and add representative cases to the reusable adversarial suite (`apps/api/tests/adversarial_cases.py` and the phase's `test_*_security.py`) — not disposable one-off checks.

## Data & evidence invariants

Forge has **no RAG pipeline and no vector database** by explicit ADR (`decisions.md` Q-008: "No vector database in the base architecture... add retrieval only when a concrete use case and evaluation dataset demonstrate benefit"). Do not introduce embeddings, chunking, or a vector store without that evidence-gated decision being revisited first. What exists instead, and what the invariants actually govern:

- **`model_calls`**: provider-neutral request/response/usage ledger. Request hash and summaries only — raw provider output is never stored.
- **`tool_invocations` / `evidence_items`**: exact requested action, policy decision, idempotency identity, outcome, and provenance/trust-labeled evidence derived from tool output (source, trust label, content hash, bounded summary). Raw secrets/provider payloads are never logged.
- **`plan_versions` / `plan_nodes` / `plan_edges`**: immutable, run-scoped, monotonically versioned planner DAGs. Only validated plans get nodes/edges persisted; superseding a plan appends a new version rather than mutating the old one.
- **Context/memory taxonomy is closed and explicit**: runtime state, conversational context, workspace knowledge, user preferences, and (off-by-default) episodic records. There is no generic "memory" table or ambient write access — don't add one implicitly.
- **Every payload category needs an explicit owner, purpose, read/write principals, retention, and redaction rule.** Raw model/tool bodies get shorter retention than normalized evidence/events.
- **`agent_iterations`**: durable per-iteration checkpoint ledger for bounded agent loops — decision type/status, model-call linkage, counters snapshot, context hash. This is the evidence trail an agent's completion citations must resolve against; unsupported citations fail closed.

## Development workflow

1. Inspect before editing — read the relevant architecture doc(s), the current implementation, and existing tests before writing code.
2. Prefer root-cause fixes over patches; don't paper over a failing invariant.
3. Make changes narrow and scoped to the authorized phase. Add a new migration; never edit an applied one.
4. Preserve prior architecture — no silent redesign, rename, or restructuring of completed modules/contracts/decisions.
5. Preserve the established Forge visual/UI direction already in `apps/web`; extend it, don't drift to a new look ad hoc.
6. Write/extend tests alongside the change: unit, integration, security/adversarial, failure, concurrency — proportional to scope, with deterministic fakes at boundaries.
7. Update the relevant architecture doc/ADR and phase/status docs when a contract changes, in the same change.
8. Run the applicable commands (below) before considering work done.

## Commands

Verified against `package.json`, `turbo.json`, `apps/*/package.json`, and `.github/workflows/ci.yml` — do not invent variants.

```bash
pnpm install                # install workspace deps
pnpm demo                   # zero-cost local demo: db up, migrate, seed, start web/api/worker
pnpm dev                    # turbo dev, all apps, parallel

pnpm db:up / db:down        # local Postgres + Redis via docker-compose
pnpm db:migrate             # apps/api migrations
pnpm db:seed                # deterministic seed data

pnpm lint                   # turbo lint (ruff + mypy for Python apps, eslint for web)
pnpm typecheck              # turbo typecheck (mypy strict / tsc --noEmit)
pnpm build                  # turbo build
pnpm test                   # turbo test — pytest (excl. `security` marker) + vitest
pnpm test:security          # turbo test:security — pytest -m security + vitest security.test.ts
pnpm generate:types          # export OpenAPI from API, regenerate shared TS types

pnpm demo:tools / demo:planning / demo:approvals / demo:agentic / demo:langgraph
pnpm demo:evaluations / demo:debugger / demo:mcp / demo:multi-agent / demo:recovery
pnpm capacity-report         # real local load/soak drill, measured evidence + labeled extrapolation
pnpm backup-restore-drill    # real pg_dump/pg_restore cycle into a throwaway DB
```

Per-app equivalents (when iterating inside one app) are in that app's `package.json`, e.g. `apps/api`: `pytest tests -m 'not security'`, `ruff check src tests && mypy src`, `uvicorn forge_api.main:create_app --factory --reload`. Terraform in `infra/terraform` is `fmt`/`validate`/`plan` only — `apply` requires explicit user approval and is never part of any default command.

## Testing & validation

Three named, non-interchangeable lanes (`decisions.md` D-017): deterministic software tests, offline behavioral evaluations, and opt-in live-model evaluations. Never fabricate metrics or results in any of them.

- Every phase needs unit, integration, security/adversarial, failure, and concurrency coverage proportional to its scope, with deterministic fakes at boundaries — not just happy-path tests.
- Security tests live under the `security` pytest marker / `tests/security.test.ts` and run via `pnpm test:security`; they are part of the normal gate, not optional extras.
- CI (`.github/workflows/ci.yml`) is the ground truth for "passing": install → migrate/seed → generate:types → lint → typecheck → build → test → test:security → `pip-audit` → `pnpm audit --audit-level=high`, plus a separate `gitleaks` secret-scan job over full history. All GitHub Actions are pinned to commit SHAs.
- Never weaken a test to make it pass, and never replace real functionality with mocks except where mocks/fakes are the intentional zero-cost/deterministic boundary substitution (fake model provider, fake external effects, local MCP server) that the architecture already calls for.

## Zero-cost requirement

The complete local development, test, evaluation, and demo path must cost **INR 0** and never require billing credentials, a paid API, cloud infrastructure, or a purchased domain — this is a permanent architecture profile (`decisions.md` D-019/D-020), not a bootstrap shortcut.

- Default config selects deterministic fake model/tool/notification/remote-service adapters. Discovering a credential in the environment must never activate a potentially-billable adapter — that decision is enforced at the composition root via `FORGE_EXTERNAL_INTEGRATIONS` (`disabled` by default), not by convention inside adapters.
- `pnpm demo` and the default lint/typecheck/build/test/test:security/CI commands must never make a live or billable call. Any live provider, cloud adapter, or paid integration is a separately labeled, budget-capped, explicit opt-in excluded from all default commands and CI.
- Never provision AWS/Bedrock/Temporal Cloud/managed DBs/paid observability/a domain without the user's explicit approval in the current task. Trial credits do not satisfy this contract.
- If a phase report claims "zero-cost," it must name which profile ran and which external adapters were disabled — not just assert it.

## Phase discipline

- **One phase at a time.** Implement exactly the scope of the current, explicitly authorized phase specification. Never begin, scaffold, or partially implement the next phase without the user explicitly saying **"Proceed to next phase."** Being helpful is not authorization.
- Since Phase 00–13 are all complete per `docs/internal/status.md`, there is currently no phase to implement — flag this rather than guessing at a "Phase 14" scope.
- Read the exact phase spec every time, even for a phase that looks similar to a completed one; never implement from memory or the roadmap table alone.
- Universal phase exit procedure (from `docs/phases/README.md`): refactor + doc/ADR update → focused deterministic/integration/security/failure/concurrency tests (+ labeled behavioral/live evals where relevant) → verify no secrets/private material tracked and no live/billable calls were made → private learning artifacts (owner's Learning Vault, out of repo scope for Claude) → reproducible demonstration → phase report → separate `PRODUCT GATE` / `HIRING-READINESS LEARNING GATE` → stop and wait for explicit next-phase authorization.
- Hiring-readiness learning-gate status (`NOT TESTED`/`IN PROGRESS`) never blocks or delays authorized product implementation; report the two gates independently.

## User-visible demonstration

A phase (or any user-visible change) is not complete because tests pass. Every phase closeout automatically ends with a real, shown demonstration — never test counts, file lists, or "checked in browser" claims as a substitute.

- UI functionality: start required local services, open the app, navigate to the capability, seed demo data if needed, exercise it, show the resulting states, explain what's visible, give exact reproduction steps.
- Non-UI functionality: demonstrate through the appropriate API/CLI/database-state/worker-output/logs/deterministic simulation — don't build unnecessary UI just to have something to show.
- Reliability/security work: demonstrate representative scenarios (normal success, cross-tenant denial, idempotent duplicate handling, invalid-input safe failure, worker crash recovery, approval-required blocking, prompt-injected input triggering the relevant control) where applicable.
- If an environment/tool limitation prevents showing something, say so explicitly and give the closest reproducible alternative — never fabricate or imply a demo that didn't happen.
- Every phase closeout uses these sections in order: `BEFORE`, `AFTER`, `LIVE DEMO`, `TRY IT YOURSELF`, `UNDER THE HOOD`, `VALIDATION`, `LIMITATIONS`, `NEXT PHASE`, followed by separate `PRODUCT GATE: PASS|FAIL` and `HIRING-READINESS LEARNING GATE: NOT TESTED|IN PROGRESS|PASS` lines. Report content itself is natural Roman-script Hinglish with standard technical terms kept in English; the underlying artifacts (code, docs, commit messages) stay professional English.

## Git discipline

- Only create commits, tags, or pushes when the user's current instructions (or the phase-completion procedure the user has authorized) explicitly call for it.
- Phase-completion commit → tag `phase-N` on that exact commit → push commit and tag to the configured remote → verify both exist on the remote, only after implementation + all applicable tests + demo + doc updates are genuinely done and the working tree is clean.
- **Never touch an existing `phase-N` tag** — never move, rewrite, or re-target one, never tag an incomplete/failing phase, never rewrite history or force-push to make history look cleaner.
- If Git/GitHub isn't available or a remote push can't be verified, report that plainly instead of claiming it happened.
- Never destroy unrelated user changes; never use destructive Git operations merely to make the working tree clean (see the global Git Safety Protocol in this session's system instructions — it takes precedence over any of the above).

## Documentation discipline

- Keep `docs/architecture/*`, `docs/internal/status.md`, and the relevant phase report synchronized with what was actually implemented — a contract change without a doc/ADR update is incomplete work.
- Phase numbers, phase names, and phase history stay in `docs/internal/` and `docs/phases/` only — never in product UI or the primary `README.md`.
- Production code, code comments, README files, public architecture/phase docs, commit messages, and all GitHub-facing material stay professional English, always.
- Private owner learning/teaching material (Hinglish quizzes/explanations, the Learning Vault at `~/AI-Learning-Vault/forge-ai/`) never gets committed, linked from public docs, uploaded, or made runtime-dependent.

## Dependency policy

Prefer existing dependencies and already-adopted platform capabilities (PostgreSQL, Redis, the existing typed ports) over adding new ones. Any new dependency needs a concrete engineering justification tied to the current phase's scope — check `decisions.md` first; several additions (vector DB, Temporal, multi-agent-by-default, SSE) were already evaluated and explicitly rejected or deferred with stated evidence thresholds. Don't reopen an evidence-gated decision without new evidence.

## Definition of done

Before calling any task or phase complete, confirm all that apply:

- [ ] Implementation matches the exact authorized scope — nothing from a future phase silently included.
- [ ] Relevant architecture doc(s)/ADR updated if a contract changed; no doc left contradicting the code.
- [ ] Unit, integration, security/adversarial, failure, and concurrency tests added/updated and passing, proportional to scope.
- [ ] `pnpm lint`, `pnpm typecheck`, `pnpm test`, `pnpm test:security` (and `pnpm build` where relevant) actually run and pass.
- [ ] No secret, credential, or private Learning Vault content is tracked or committed; `AGENTS.md`/`PROMPT.md`/`CLAUDE.md` remain untracked.
- [ ] Zero-cost path verified: no live/billable call made by any default command.
- [ ] A real, shown demonstration exists (not just tests) — with an explicit note if environment limits prevented showing part of it.
- [ ] Phase closeout sections and both gates completed, if this is a phase closeout.
- [ ] Working tree is clean before any phase-completion commit/tag/push, and remote commit+tag existence is actually verified before claiming it.

## Behavior rules for Claude

1. Inspect before editing — read the doc, the code, and existing tests first.
2. Prefer root-cause fixes over patches or workarounds.
3. Never weaken a test just to make it pass.
4. Never bypass a security control to simplify an implementation.
5. Never replace real functionality with mocks, except where mocks/fakes are intentionally part of the test suite or the zero-cost/deterministic architecture itself.
6. Never claim something was tested, demonstrated, committed, tagged, or pushed unless it actually happened.
7. Never silently expand scope beyond the authorized phase or task.
8. Preserve backward compatibility unless the task explicitly requires breaking it.
9. Keep changes production-quality and interview-defensible.
10. Prefer simple architecture over unnecessary abstraction — no god services, arbitrary `utils`, or hidden mutable state.
11. Treat security, tenant isolation, provenance, and deterministic testing as first-class requirements, not afterthoughts.
12. Stop and report genuine blockers (missing Git remote, environment limitation, unresolved ADR conflict) rather than fabricating success.

## Privacy and Git handling

- This repository keeps agent-instruction and private-context files **out of Git using `.git/info/exclude`** (a local, per-clone exclude file that is itself never tracked) rather than `.gitignore`. `AGENTS.md` and `PROMPT.md` are already excluded this way. `CLAUDE.md` follows the same policy — it must stay untracked and must never be committed.
- Separately, `.gitignore` also ignores `.local-learning/`, `.env`, `.env.*`, and local credential/runtime directories (`local/`, `apps/api/local/`). Private learning material belongs only under `~/AI-Learning-Vault/forge-ai/` (outside this repo) — never commit it, link to it from public docs, upload it, or make product runtime depend on it.
- Do not paste, summarize, or otherwise surface private Learning Vault content into public docs, commit messages, PRs, or product UI.
- Before finishing any task that touches the repo root or `.gitignore`/`.git/info/exclude`, sanity-check that `AGENTS.md`, `PROMPT.md`, and `CLAUDE.md` remain untracked (`git status`, `git ls-files` should not list them).
