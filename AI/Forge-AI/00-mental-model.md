# Forge AI — mental model

Grounded in the implementation repo (`codevoks/forge-ai`) at the all-phases-complete state
(Phase 1–13 + final whole-project audit). See [`01-phases.md`](01-phases.md) for phase detail and
[`02-concepts.md`](02-concepts.md) for concept-level pointers.

## What is Forge?

Forge is a **durable, tenant-isolated agent and workflow platform**. It is a runtime that can
persist, schedule, execute, and recover long-running units of work — deterministic workflow DAGs
*and* bounded AI-agent loops — where Postgres is the single authoritative source of truth for
what happened, and every side effect (a tool call, a model call, an external API call) is tracked
through its full lifecycle: proposed → authorized → possibly-approved → budgeted → executed →
recorded as evidence.

It ships as three deployables sharing one Postgres database:

- `apps/web` — Next.js UI. Presents state. Never decides authorization or transitions.
- `apps/api` — FastAPI command/query boundary. JWT verification, actor construction, policy,
  transactions. This is where almost all of the interesting logic lives.
- `apps/worker` — queue consumers, outbox dispatcher, abandoned-work recovery, task execution.

Redis is used only as **disposable coordination** (queue transport). If Redis is lost entirely,
Forge loses *scheduling latency*, never *acknowledged workflow state* — everything durable is
already in Postgres.

## What problem does it solve?

Two problems, in one platform:

1. **Durable workflow execution.** Ordinary backend systems execute multi-step processes
   in-memory or with ad-hoc retry logic; a crash mid-process loses state or double-executes a side
   effect. Forge instead models work as a DAG of tasks with persisted state machines, a
   transactional outbox, at-least-once delivery, and an idempotency contract on every handler —
   so a crash anywhere is a recoverable event, not data loss.
2. **Safe AI agent execution inside that same durable substrate.** An LLM can *propose* a plan or
   the next action in an agent loop, but Forge's application code is the only thing that can
   authorize a tool call, bind and enforce a human approval, reserve/settle a budget, validate a
   citation against real evidence, or terminate a runaway loop. The model is a planner, not a
   security boundary.

## Why isn't it just an LLM tool-calling loop?

A naive tool-calling loop trusts the model's output directly: whatever tool name and arguments the
model emits gets executed, with retries and errors handled ad hoc, no persisted history beyond the
chat transcript, and no notion of "this specific action needs a human to approve it first" versus
"this one doesn't." That's fine for a demo; it's not fine for anything that touches real systems,
money, or multiple tenants.

Forge inverts the trust relationship:

- The model can only choose from **run-scoped, code/admin-registered, immutable tool versions**
  that were explicitly granted to that run at creation time. A hallucinated, unlisted, or
  version-mismatched tool fails closed.
- Every tool call's arguments are **schema-validated, canonically normalized, and hashed** before
  anything executes — and confused-deputy fields (tenant/user/account) always come from actor
  context, never from model-supplied arguments.
- A tool call flagged as a "simulated effect" risk cannot execute until a **separate human
  approval**, bound by hash to that exact canonical action, is granted by someone other than the
  requester, and consumed exactly once.
- Every model call, tool call, and agent iteration counts against a **budget that is reserved
  before work starts and settled after** — a runaway loop stops deterministically when it runs out,
  not when someone notices.
- Tool output (including MCP output) is always **untrusted, provenance-labeled data** — it can
  never change system instructions, permissions, or allowed tools, no matter what text it contains.
- An agent's claimed "I'm done" completion must **cite real, persisted evidence**; unsupported
  citations fail closed rather than being taken on faith.

None of that is optional add-on security — it's the actual execution substrate. That's the
difference between "an LLM tool-calling loop" and "an agent platform."

## What does "application authoritative" mean?

At every point where a model could influence something consequential, Forge code — not the model,
not LangChain, not LangGraph, not an MCP server — makes the actual decision:

| Decision | Who decides | Model's role |
|---|---|---|
| Which tools exist / which version is callable | Code/admin registry (`tool_versions`) | Names one; can't invent one |
| Whether a tool call is authorized for this run | `run_tool_grants` snapshot + policy | None |
| Whether this exact action needs human approval | `ApprovalPolicy` (risk classification) | None |
| Whether budget remains to do the work | Atomic `UPDATE ... RETURNING` reservation | None |
| Whether an agent loop keeps going or stops | Step/iteration/cost/no-progress limits in code | Proposes next action only |
| Whether a completion claim is accepted | Citation validated against persisted evidence | Makes the claim; doesn't validate it |
| What actually happened (the record) | Postgres: events, invocations, evidence | Its output is one input, not the record |

This is why Forge's own docs describe the model as something that "proposes structured plans and
tool calls," while "Forge application code always validates, authorizes, budgets, approves,
executes, and terminates."

## Major components (name → role)

- **Domain** (`apps/api/src/forge_api/domain/`) — pure business rules: workflow/run/task state
  machines, tool contracts, approval policy/binding-hash, budgets, multi-agent roles. No I/O.
- **Application** (`application/`) — orchestration services: `run_service`, `tool_runtime`,
  `approval_service`, `agent_runtime` (+ `LangGraphAgentRuntime`), `budget_service`,
  `multi_agent_router`, `evaluation_service`, `debugging_service`.
- **Policy** (`policy/`) — authorization checks (RBAC, tenant/workspace scope).
- **Runtime / Planner** — bounded agent iteration loop; LLM provider abstraction and structured
  plan validation.
- **Tools** (`tools/`) — typed tool definitions and adapters (deterministic/code, MCP-backed).
- **Ports** (`ports/`) — narrow interfaces to everything external: `ModelProvider`, `QueuePort`,
  `MCPClientPort`, workflow-engine, secrets, `TelemetryPort`. No provider SDK leaks past a port.
- **Infrastructure** (`infrastructure/`) — concrete adapters: Postgres repositories, Redis Streams
  queue, OTel telemetry exporter, LangChain-composed model provider, LangGraph checkpointer.
- **`apps/worker`** — the process that actually claims queued tasks and calls into
  `application/` to run them; re-validates grant/scope/policy on every claim (queue possession
  alone grants no authority).

## The lifecycle of a durable run

1. **Create** — API validates and persists an immutable versioned workflow snapshot (or agent
   task spec), opens a run, computes/persists the initial DAG of tasks, snapshots `run_tool_grants`
   and budget policy for that run. A root telemetry span/trace is opened here.
2. **Schedule** — ready tasks are written to Postgres and mirrored into the transactional outbox
   in the *same* transaction as the state change. The outbox dispatcher publishes due messages
   onto the (disposable) Redis Streams queue.
3. **Claim** — a worker consumer claims a task message (at-least-once — duplicates are expected),
   reloads durable scope/grants/policy fresh from Postgres (never trusts anything cached in the
   queue message beyond routing), and takes an attempt lease with a fencing token.
4. **Execute** — depending on task kind:
   - deterministic/tool task → `tool_runtime`: grant check → schema validation → canonical-hash →
     invocation ledger insert → (maybe pause for approval) → budget reservation → adapter dispatch
     → evidence record with trust label → completion event.
   - agent task → `agent_runtime` (custom engine or `LangGraphAgentRuntime`): iterate
     perceive→decide→act→observe, each iteration checkpointed, budgeted, and validated against
     snapshotted `allowed_tools`, until it completes (citation-validated), fails, or hits a bound.
5. **Recover** — if a worker dies mid-attempt, its lease expires; a periodic recovery scan
   reclaims the abandoned attempt, resets the task to `ready`, and republishes it (and, since the
   final audit, releases any budget reservation that attempt had orphaned) — all inside a
   transaction, all derivable purely from Postgres state.
6. **Complete / fail** — task and run state transitions are written together with an append-only
   execution event in one transaction. The event log is the audit trail; current-state tables are
   for fast queries, not the only source of truth (event folding is used to *verify* projections,
   not as the sole recovery path — see Phase 10's debugger).

## How this differs from Atlas AI (so you don't cross-wire mental models)

Atlas AI (`../Atlas-AI/`) is a multi-tenant **RAG** system: ingestion → chunking → embeddings →
hybrid retrieval → citation-checked generation, with a bounded-research agent layered on top.
Forge has **no RAG pipeline and no vector database at all** (explicit ADR, Q-008: add retrieval
only when a concrete use case and evaluation dataset demonstrate benefit). Forge's center of
gravity is the opposite half of an AI-infra system: durable execution, tool/approval/budget
security, and multi-agent orchestration — the part that runs *after* a plan exists, not the part
that finds documents to ground a plan in. Where Atlas teaches "how do you retrieve and cite
correctly," Forge teaches "how do you let a model drive real actions safely, durably, at scale."
