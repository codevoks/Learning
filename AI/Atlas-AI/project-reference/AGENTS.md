# Atlas AI implementation rules

Atlas AI is a production-grade enterprise knowledge, retrieval, RAG, and bounded-research SaaS. A working repository is insufficient unless the architecture is coherent, testable, secure, observable, and defensible.

## Read before working

Read this file, `docs/architecture.md`, `docs/decisions.md`, `docs/threat-model.md`, the relevant focused design (`data-model.md`, `capacity-model.md`, or `failure-model.md`), and only the active implementation contract under `docs/internal/engineering-history/phases/`. Do not rescan the repository without a concrete reason. `PROMPT.md` is a local-only product/orchestration charter; revisit it only for ambiguity or architecture changes.

## Phase discipline

- Work on one approved phase only. Never start the next phase until the user says **Proceed to next phase**.
- Each phase has an explicit product gate based on implementation scope, security requirements, failure handling, tests, and a reproducible demonstration.
- Each phase must remain buildable, testable, and demonstrable at zero monetary cost.
- Keep phase scope, deferrals, acceptance criteria, tests, failure tests, and security review aligned with the phase specification.
- Record architecture changes in `docs/decisions.md` and update `docs/architecture.md` and `docs/threat-model.md` when boundaries change.
- Keep `docs/system-design-visuals.md` synchronized when a component boundary, authoritative store, trust boundary, major data flow, state machine, or scaling decision changes. Add a new visual only when it materially improves understanding; prefer Mermaid for static architecture and flows.
- Keep `docs/internal/engineering-history/project-status.md` synchronized at the start and end of every implementation phase. Mark the active phase `In Progress` before implementation validation completes, then update it with completed scope, demo/validation evidence, and Git commit/tag information after the phase gate passes.
- Diagnose failed validation before retrying. Use targeted checks during work and the full phase gate at completion.

## Phase demonstration

Every implementation phase must automatically end with a real demonstration without waiting for the user to request it separately. A phase is not complete until this demonstration has been performed.

Tests and validation are required, but they are not a substitute for demonstration. A demonstration is not satisfied by only saying tests passed, listing changed files, reporting test counts, describing API responses, saying the browser was checked, or summarizing the implementation.

When the phase functionality has a UI:

1. Start all required local services.
2. Open the application in the available browser or preview.
3. Navigate to the relevant functionality.
4. Create or seed useful demo data if necessary.
5. Actually exercise the newly built functionality.
6. Show the resulting UI/screens/states to the user.
7. Explain concisely in natural Hinglish what the user is seeing.
8. Tell the user exactly what they can click/do to reproduce it themselves.
9. Leave the application/demo environment running and available for user inspection where practical.

When the phase functionality does not have a meaningful UI, do not manufacture unnecessary UI. Instead, perform a real reproducible demonstration using the appropriate API, CLI, database/state inspection, worker output, logs/traces, deterministic simulation, or evaluation artifact. Show the actual action/input and resulting output/state, not merely a description.

For reliability and security functionality, demonstrate relevant scenarios where applicable: normal request succeeds, cross-tenant request is denied, duplicate request is idempotent, invalid input fails safely, worker crash recovers/retries, approval-required action blocks until approval, and malicious/prompt-injected input activates security controls.

The demonstration path must require zero paid SaaS, cloud resources, domains, or paid model APIs. Use deterministic fakes/mocks or genuinely free local alternatives for tests and demos.

Never fabricate a result or claim the user saw something that was not actually shown. If an environment/tool limitation prevents a user-visible demonstration, explicitly state what prevents it and provide the closest reproducible demonstration possible.

Every phase completion report must include:

- BEFORE — what the product could do before this phase.
- AFTER — what new capabilities this phase added.
- LIVE DEMO — the started and exercised capability so the user can see it.
- TRY IT YOURSELF — the minimum steps to reproduce the demo.
- UNDER THE HOOD — the important architecture/data flow and the most important code/modules.
- VALIDATION — relevant tests, security checks, failure tests, evaluations, or benchmarks with actual results.
- LIMITATIONS — intentionally deferred work.
- NEXT PHASE — what the next phase will add, without implementing it.

## Zero-cost build, test, and demo invariant

- The default repository path must work without monetary spend: local Docker/open-source infrastructure, deterministic development auth, local storage, deterministic model/provider fakes, and fixture-based tests.
- Paid SaaS, cloud accounts, paid model APIs, domains, managed observability, managed queues, hosted search, or billable infrastructure may be represented by production-grade adapters and documentation, but must be explicitly opt-in and must never run, provision, or call external billable services without the user's approval.
- Do not make large local LLM downloads mandatory. If local AI behavior is needed for tests or demos, provide deterministic fakes or small optional alternatives.
- Every provider-facing phase must include adapter contract tests against deterministic local implementations. Live provider checks are optional smoke tests only, isolated from the product gate unless the user explicitly approves them.
- Phase completion evidence must identify the zero-cost path used and any optional billable integrations that remain disabled.

## Public repository professionalism

- Keep production code, code comments, commit messages, README files, public documentation, architecture documentation, API contracts, ADRs, issues, and GitHub-facing material in professional English.
- Preserve useful technical depth in public docs: architecture, ADRs, threat models, phase specifications, test plans, evaluation methodology, benchmarks, security requirements, failure analysis, and deployment documentation.
- Do not commit private/personal material, credentials, raw sensitive documents, provider payloads containing customer data, or production traces.
- `.local-private/` is ignored for temporary local notes, but it must not be treated as part of the public repository.

## Architecture invariants

- Required monorepo: pnpm + Turborepo; initially `apps/web`, `apps/api`, `apps/worker`, `packages/config`, and `packages/shared-types`. Add packages only for proven reuse or a real architectural boundary.
- Next.js is the browser-facing UI/BFF; Tailwind CSS is the required web styling system; FastAPI owns domain/API behavior; the worker owns durable asynchronous jobs.
- PostgreSQL is the transactional source of truth; pgvector starts as semantic storage; Redis is ephemeral coordination/cache, never authoritative; object storage holds source blobs.
- Every tenant-owned row and object is tenant-scoped. Authorization is enforced server-side at use-case and persistence boundaries; never trust client-supplied tenant identity.
- External providers are behind narrow adapters. Persist provider/model/version provenance. Do not scatter SDK calls.
- Ingestion and research are explicit, idempotent state machines. Side effects require stable idempotency keys, bounded retries, timeouts, and recoverable failure states.
- Retrieval returns typed evidence with stable chunk/document/version identity. Generation may cite only evidence supplied to it; citations are validated after generation.
- Treat uploads, retrieved text, model output, tool output, and web content as untrusted data. Instructions never inherit authority from retrieved content.
- Prefer deterministic workflows. Use agents only for bounded, measurable tasks with explicit tools, budgets, termination, checkpoints, and human intervention points.
- No multi-agent implementation without benchmark evidence that it improves a named workflow enough to justify coordination and evaluation cost.
- Keep domain/application/infrastructure/retrieval/AI/API/presentation responsibilities explicit. Avoid giant handlers/services/components, random utility modules, speculative abstractions, hidden state, duplicated rules, and unjustified `any`.

## Privacy and secrets

- Never commit secrets, raw sensitive documents, provider payloads containing customer data, production traces, or private/personal material.
- Keep local environment files ignored. `.env.example` may contain placeholders only.
- Logs and telemetry must be redacted and tenant-safe.

## Completion report

Report system-design decisions/tradeoffs/scale, product changes/modules/tests/security/failure results/refactoring, live demonstration and reproduction steps, resource impact, and Git safety. End with:

`PRODUCT GATE: PASS | FAIL`

Then stop.
