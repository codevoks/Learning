# Forge AI implementation rules

Forge AI is an educational, production-grade durable agent/workflow platform. Success means the owner can design, implement, debug, and defend it—not merely run it.

## Before working

1. Read this file, `docs/architecture/README.md`, the architecture documents it routes to, and only the current `docs/phases/phase-NN-<scope>.md`.
2. Work on one phase only. Never advance without the user saying **Proceed to next phase**.
3. Do not redesign settled decisions silently. Record a proposed ADR change with evidence and migration impact.
4. Product implementation may advance after explicit phase authorization even when the hiring-readiness learning gate is `NOT TESTED` or `IN PROGRESS`. Never treat learning-gate status as a product blocker.

## Permanent architecture invariants

- Begin as a modular monolith: `apps/web`, `apps/api`, `apps/worker`; add packages only at genuine boundaries.
- PostgreSQL is authoritative. Redis/queues/caches are disposable coordination mechanisms.
- State changes use explicit transition functions and database transactions. Current-state projections and append-only execution events are written together.
- Cross-process work is published through a transactional outbox and consumed at least once. Every handler and side effect needs an idempotency strategy.
- The model proposes; application code authorizes, validates, budgets, approves, executes, and terminates.
- Tenant/workspace scope is explicit in identity, queries, records, events, jobs, traces, and cache keys. Deny by default.
- High-risk side effects require a code-enforced approval bound to the exact versioned action and arguments.
- Plans are validated, bounded DAG versions. Replanning creates a new version; history is not rewritten.
- Provider, queue, model, tool, MCP, and workflow-engine details stay behind narrow interfaces.
- No claim of exactly-once external effects. Record uncertain outcomes and reconcile.

## Engineering rules

- Prefer explicit, typed control flow; no god service, arbitrary `utils`, hidden mutable state, scattered transitions/SQL, or provider SDK leakage.
- Make changes narrow. Add schema migrations; never edit an applied migration. Use UTC timestamps and opaque UUIDv7 identifiers.
- Secrets are references, never prompt/context/event/log payloads. Treat model and external-tool output as untrusted data.
- Test in three named layers: deterministic software tests, offline behavioral evaluations, and opt-in live-model evaluations. Never fabricate metrics.
- Each phase needs unit, integration, security, failure, and concurrency coverage proportional to its scope. Deterministic fakes are mandatory at boundaries.
- Update architecture docs and ADRs when a contract changes. Refactor before the phase gate.
- Name every phase specification and report with both its two-digit phase number and scope, for example `phase-03-durable-queues-workers-recovery.md`.
- When a phase introduces important topology, ownership, state, sequence, trust, or failure relationships, add or update the smallest useful Mermaid visual in the relevant architecture document. Visuals must teach a decision and remain consistent with the written contract.

## LangChain, LangGraph, and LangSmith placement

- Final project completion requires genuine executed, tested, demonstrated, and documented coverage for LangChain, LangGraph, and LangSmith. Installing or importing a package does not count.
- Preserve historical truth: do not rewrite Git history, move `phase-1` through `phase-8` tags, retroactively rename completed phases, or claim a framework existed in a historical snapshot where it did not.
- LangChain belongs around provider/message/prompt/structured-output/tool interoperability and composition seams. It may enhance subsystems first implemented in Phase 5, but Forge application code remains authoritative for schemas, permissions, budgets, approvals, state, and effects.
- LangGraph belongs around stateful agent orchestration: graph state, nodes, conditional edges, reducers, checkpoints, interrupts/HITL, and state inspection. The Phase 8 local `StateGraph` path is the first genuine integration; later phases may evaluate and debug it further, but LangGraph checkpoint state is never a tenant/security authority source.
- LangSmith belongs around tracing, evaluation datasets, experiments, model/tool/agent observability, and regression comparison. It must be opt-in, redacted, tenant-scoped, and exporter-failure-isolated. The default zero-cost profile must run without a LangSmith account or external telemetry.
- Every framework integration must include functional tests, relevant adversarial/security boundary tests, a user-visible demo, documentation, and an offline/zero-cost fallback. Any live LangSmith/provider/cloud execution requires explicit user approval in the current task and must be separately labeled from local evidence.
- If final completion reaches a point where an approved LangSmith account or self-hosted endpoint is unavailable, report the live LangSmith execution evidence as a blocker rather than fabricating it; the local/offline fallback still remains mandatory and must not be weakened.

## Zero-cost development and demonstration

- The complete local development, automated test, evaluation, and portfolio demonstration path must cost INR 0 and require no billing credentials, paid subscription, purchased domain, or temporary trial credit.
- The default path uses local/open-source infrastructure and deterministic fakes at external boundaries. PostgreSQL, Redis, workers, queues, state machines, checkpoints, approvals, retries, idempotency, recovery, replay, policy, and security controls must exercise the real Forge architecture.
- Paid model APIs are never required. Deterministic fake model providers must support every agentic, multi-agent, and evaluation demonstration. Large local model downloads are optional and never prerequisites.
- Tests and evaluations must be network-denied or otherwise fail closed against live/billable providers by default. Every live provider or cloud adapter is explicitly opt-in, separately labeled, budget-capped, and excluded from default commands and CI.
- Never provision AWS, Bedrock, Temporal Cloud, managed databases, paid observability, or any potentially billable resource without the user's explicit approval in the current task. Trial credits do not satisfy the zero-cost contract.
- Production-capable adapters may be designed and optionally implemented behind narrow ports, but their absence must not reduce the zero-cost demo's coverage of Forge-owned behavior.
- Maintain the reproducible zero-cost demo contract in `docs/architecture/zero-cost-demo.md`. Evolve a single `pnpm demo` entry point as phases add runnable capabilities; it must never require billing credentials.
- At every phase gate, prove the default demo/test path made no billable calls and identify any optional integration that was not exercised.

## Mandatory phase demonstration

- Every implementation phase must automatically end with a real demonstration before the phase can be called complete. Do not wait for the user to request it separately.
- A demonstration means showing the working result so the owner can personally see, inspect, and understand what was built. Tests, validation, file lists, test counts, API-response summaries, or statements that the browser was checked are required evidence where relevant, but they are not substitutes for demonstration.
- For UI functionality: start required local services, open the app in the available browser or preview, navigate to the new capability, create or seed useful demo data if needed, exercise the functionality, show the resulting UI/screens/states, explain concisely in natural Hinglish what is visible, provide exact reproduction steps, and leave the demo environment running where practical.
- For functionality without a meaningful UI: do not create unnecessary UI. Demonstrate through the appropriate API, CLI, database/state inspection, worker output, logs/traces, or deterministic simulation. Show the actual action/input and resulting output/state, not only a description.
- For reliability and security work, demonstrate representative scenarios where applicable: normal success, cross-tenant denial, duplicate/idempotent handling, invalid-input safe failure, worker crash recovery/retry, approval-required blocking, and malicious or prompt-injected input triggering the relevant control.
- Every phase closeout must include these sections: `BEFORE`, `AFTER`, `LIVE DEMO`, `TRY IT YOURSELF`, `UNDER THE HOOD`, `VALIDATION`, `LIMITATIONS`, and `NEXT PHASE`.
- If an environment or tool limitation prevents a user-visible demonstration, state the blocker explicitly and provide the closest reproducible demonstration possible. Never fabricate results or imply the owner saw something that was not actually shown.
- This is a local Codex operating rule. Do not copy Codex-specific orchestration instructions into public repository documentation or GitHub-facing material.

## AI security and adversarial validation

- Security is a continuous engineering requirement for Forge AI, not work deferred only to the final project audit.
- For every current and future implementation phase, inspect the functionality introduced or modified by that phase and identify relevant security boundaries, abuse cases, trust assumptions, and adversarial failure modes.
- Implement appropriate security controls as part of the functionality itself. Do not postpone obvious security work when the phase introduces the relevant attack surface.
- Add and run relevant adversarial/security tests whenever the phase introduces an applicable attack surface. Security tests are part of the normal phase gate and run alongside functional, reliability, failure, and regression tests.
- Explicitly consider and test only areas relevant to functionality that exists in that phase. Do not create meaningless tests for features that do not exist yet.
- Depending on the phase scope, consider: authentication and tenant/workspace isolation; authorization boundaries; tool-call authorization; agent privilege boundaries and least privilege; confused-deputy attacks; direct prompt injection; indirect prompt injection through tool results, retrieved content, external/web content, MCP resources, or other untrusted data; attempts by untrusted content to override system/developer/security instructions; data exfiltration; secret leakage; SSRF and malicious URL/tool inputs; unsafe tool arguments; unauthorized tool chaining; approval bypass; human-in-the-loop enforcement for dangerous actions; agent runaway or excessive execution; resource and token-budget abuse; retry/replay abuse; idempotency/security interactions; forged or manipulated agent/workflow state; checkpoint/state tampering; cross-tenant state or memory leakage; malicious MCP/tool responses; unsafe error leakage; audit-log integrity; and security-event visibility.
- For each phase, classify relevant security areas as `protected and verified`, `implemented but needing deeper final validation`, `genuine gap/blocker`, or `not applicable yet`.
- A genuine security blocker must be fixed before that phase can be declared complete. Never claim a security guarantee that has not been demonstrated by implementation and evidence.
- Build the adversarial evaluation corpus incrementally as Forge evolves. When a phase introduces a new AI, agent, tool, workflow, MCP, retrieval, or external-content attack surface, add representative cases to the reusable security/evaluation suite rather than disposable one-off checks.
- Phase-level security validation does not replace the final integrated security/red-team audit. After all implementation phases are complete, perform a dedicated end-to-end adversarial audit across the fully integrated system, including attack chains that cross multiple components.
- The final audit must distinguish between `verified protection`, `residual limitation`, `intentionally out-of-scope risk`, and `release-blocking vulnerability`.

## Phase Git history and tagging

- For every implementation phase, Git history must preserve an accurate and auditable phase-completion snapshot.
- After a phase has been fully implemented; all required functional tests passed; all applicable security/adversarial tests passed; reliability/failure validation passed; the required user-visible demonstration performed; and relevant internal documentation/status updated, automatically create a dedicated phase-completion commit if appropriate.
- Ensure the repository working tree is clean before tagging a completed phase.
- Create the Git tag `phase-N` on the exact verified completion commit for Phase N, push the completion commit to the configured GitHub remote, push the corresponding `phase-N` tag, and verify that both the commit and tag exist on the remote.
- Never tag an incomplete or failing phase; place a phase tag blindly on an unrelated later commit; move an existing correct phase tag; rewrite Git history or force-push merely to make phase history look cleaner; or fabricate a historical phase tag when no honest historical completion commit exists.
- If Git/GitHub is not initialized or a remote is unavailable, clearly report that instead of pretending the commit or tag was pushed.
- Maintain internal phase completion/status documentation so `Phase -> completion report -> completion commit -> Git tag` remain consistent and auditable.
- Phase numbering and phase history are internal engineering information. Do not expose them in the product UI or primary README.

## Learning and phase gates

- Use natural Roman-script Hinglish for all interactive teaching, quizzes, interview practice, assessments, system-design/security explanations, debugging and reconstruction discussions, and private Learning Vault material written for the owner. Keep standard technical terminology in English; never force awkward Hindi translations of terms such as `idempotency`, `eventual consistency`, `state machine`, `DAG`, `outbox`, `retries`, `checkpointing`, `prompt injection`, `MCP`, `LangGraph`, or `multi-agent`.
- Keep every public repository artifact in professional English, including production code, code comments, README files, public/architecture/phase documentation, commit messages, and GitHub-facing material. The language split is content-based: private owner education is Hinglish; repository and public engineering communication is English.
- Important primitives must include owner-written exercises or reconstruction work before the hiring-readiness gate can pass.
- Treat `~/AI-Learning-Vault/forge-ai/current-state.md` as the private learning handoff source of truth. Read it before any learning interaction and update it after every learning session and every phase with the current phase, concepts mastered, weak concepts, exercises completed, assessment status, product status, and one exact next action. It must contain enough verified context for a fresh Codex chat to resume without prior conversation history; never infer mastery or completed work without evidence.
- End every phase with separate `PRODUCT GATE` and `HIRING-READINESS LEARNING GATE`; product success never implies learning success.
- Every completed phase requires a reproducible demonstration using runnable commands, APIs, browser interaction, state inspection, automated tests, or deterministic simulations. Reliability and security claims require evidence; never fabricate model behavior, benchmarks, test results, latency, cost, or security results.
- Report in concise natural Hinglish: what was built, exact demo evidence, reproduction steps, architecture fit, important files, reliability, security, actual test results, limitations, and the next phase; then stop.
- Private educational material belongs only in `~/AI-Learning-Vault/forge-ai/`. Never commit, link from public docs, upload, or make runtime-dependent on it. Keep `.local-learning/` ignored and verify private material is untracked at every gate.
