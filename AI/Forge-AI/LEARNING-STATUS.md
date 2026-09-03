# Forge AI — learning status (continuity tracker)

Read this first every session; update it last every session. Keeps future sessions from re-asking
"where were we" or re-teaching what's already solid.

## How to read this file

- **Coverage** = has the material been taught/reviewed at all.
- **Confidence** = Vansh's demonstrated ability to explain it back unprompted, not just "has heard
  of it." Only raise this after he's actually explained it back correctly, not after you explained
  it to him.
- Update dates in ISO format (`YYYY-MM-DD`).

## Setup

- **2026-09-03** — Learning vault created (`AI/Forge-AI/`), grounded in the implementation repo
  at all-13-phases-complete state (plus one final whole-project audit). Content authored from a
  dedicated repo-inspection research pass (control files, `docs/internal/status.md`, all 13 phase
  reports, `docs/architecture/`, migrations, key source files under `apps/api/src/forge_api/`,
  security tests) but **not yet taught to Vansh in a session** — this is day-zero scaffolding, not
  a record of learning that happened.

## Coverage / confidence by phase

| Phase | Topic | Coverage | Confidence | Last touched | Notes |
|---|---|---|---|---|---|
| 1 | Foundation, auth, tenancy, RBAC | Not started | — | — | |
| 2 | Deterministic workflow domain | Not started | — | — | |
| 3 | Durable queues, workers, recovery | Not started | — | — | |
| 4 | Typed tool runtime | Not started | — | — | |
| 5 | LLM provider + structured planning | Not started | — | — | |
| 6 | Human approval + AI security boundaries | Not started | — | — | |
| 7 | Bounded agentic workflow | Not started | — | — | |
| 8 | LangGraph implementation + comparison | Not started | — | — | |
| 9 | Evaluation, failure-injection, LangChain interop | Not started | — | — | |
| 10 | Execution history, debugger, safe replay | Not started | — | — | |
| 11 | MCP interoperability | Not started | — | — | |
| 12 | Measured multi-agent patterns | Not started | — | — | |
| 13 | Temporal decision, observability, budgets, cloud hardening | Not started | — | — | |
| audit | Final whole-project audit | Not started | — | — | |

## Coverage / confidence by concept cluster

| Cluster | Coverage | Confidence | Notes |
|---|---|---|---|
| Tenant isolation model (RLS + scoped services) | Not started | — | |
| Durable execution / transactional outbox | Not started | — | |
| Worker recovery / fencing / idempotency | Not started | — | |
| Typed tool runtime / run-scoped grants | Not started | — | |
| Model authority boundary (planner vs runtime) | Not started | — | |
| Exact-action approval binding | Not started | — | |
| Bounded agent loop / safe termination | Not started | — | |
| Budgets (reserve-before-work, race-safety) | Not started | — | |
| Prompt-injection / untrusted-content containment | Not started | — | |
| MCP interoperability + security | Not started | — | |
| Multi-agent (router/specialist/synthesizer) | Not started | — | |
| LangChain / LangGraph / LangSmith placement | Not started | — | |
| Observability (OTel) + zero-cost adapter pattern | Not started | — | |
| ADR reasoning (Q-005 Temporal, Q-006 multi-agent, Q-008 no vector DB, D-001 no microservices) | Not started | — | |

## Interview questions drilled

None yet. When a question from `04-interview-questions.md` has been drilled (asked cold, Vansh
answered, got feedback), list it here with date and outcome (solid / shaky / needs rework).

## Misconceptions caught

None yet.

## Weak areas (flagged, not yet resolved)

None yet — first session will surface these.

## Next queued

Suggested first session: `00-mental-model.md` end-to-end (especially the Atlas-vs-Forge distinction
— Forge is durable-execution/agent-security, not RAG), then Phase 6 (exact-action approvals) +
Phase 7 (bounded agent loop) — these two are the highest-leverage "defend this in an interview"
topics for an agent platform — before working through the rest of the phases in order. Save
Phase 8/9 (LangGraph/LangChain placement) and Phase 11/12 (MCP, multi-agent) for after the core
durable-execution + security story is solid, since those integrations are easy to overclaim without
that foundation.

## Revision cadence note

This is a finished project (not an active build), so "revision" here means periodic re-drilling to
fight forgetting, not tracking new work. Suggest a light pass every few weeks: pick 2-3 rows above
below "Confidence: solid," re-drill via `04-interview-questions.md`, update this file.
