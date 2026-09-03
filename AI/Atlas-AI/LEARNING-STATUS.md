# Atlas AI — learning status (continuity tracker)

Read this first every session; update it last every session. Keeps future sessions from re-asking
"where were we" or re-teaching what's already solid.

## How to read this file

- **Coverage** = has the material been taught/reviewed at all.
- **Confidence** = Vansh's demonstrated ability to explain it back unprompted, not just "has heard
  of it." Only raise this after he's actually explained it back correctly, not after you explained
  it to him.
- Update dates in ISO format (`YYYY-MM-DD`).

## Setup

- **2026-09-03** — Learning vault created (`AI/Atlas-AI/`), grounded in the implementation repo
  at all-11-phases-complete state. Content authored from repo inspection (README, architecture,
  data-model, threat-model, decisions, project-status docs) but **not yet taught to Vansh in a
  session** — this is day-zero scaffolding, not a record of learning that happened.

## Coverage / confidence by phase

| Phase | Topic | Coverage | Confidence | Last touched | Notes |
|---|---|---|---|---|---|
| 0 | System design/contracts | Not started | — | — | |
| 1 | Tenancy, auth, RBAC | Not started | — | — | |
| 2 | Uploads, durable jobs | Not started | — | — | |
| 3 | Parsing, chunking | Not started | — | — | |
| 4 | Embeddings, semantic search | Not started | — | — | |
| 5 | Lexical + hybrid retrieval (RRF) | Not started | — | — | |
| 6 | Generation + citation verification | Not started | — | — | |
| 7 | Evaluation harness | Not started | — | — | |
| 8 | Query expansion (evidence-gated) | Not started | — | — | |
| 9 | Bounded research + approval | Not started | — | — | |
| 10 | Security guardrails | Not started | — | — | |
| 11 | Observability/ops hardening | Not started | — | — | |

## Coverage / confidence by concept cluster

| Cluster | Coverage | Confidence | Notes |
|---|---|---|---|
| Tenant isolation model | Not started | — | |
| Idempotency & job state machine | Not started | — | |
| Hybrid retrieval / RRF | Not started | — | |
| Citation verification pipeline | Not started | — | |
| Bounded research / approval gates | Not started | — | |
| Prompt injection / guardrails | Not started | — | |
| Evaluation methodology | Not started | — | |
| Zero-cost adapter pattern | Not started | — | |
| Scaling trade-offs / ADR reasoning | Not started | — | |

## Interview questions drilled

None yet. When a question from `04-interview-questions.md` has been drilled (asked cold, Vansh
answered, got feedback), list it here with date and outcome (solid / shaky / needs rework).

## Misconceptions caught

None yet.

## Weak areas (flagged, not yet resolved)

None yet — first session will surface these.

## Next queued

Suggested first session: `00-mental-model.md` end-to-end, then Phase 1 + Phase 6 (tenancy and
citation verification are the two highest-leverage "defend this in an interview" topics) before
working through the rest of the phases in order.

## Revision cadence note

This is a finished project (not an active build), so "revision" here means periodic re-drilling to
fight forgetting, not tracking new work. Suggest a light pass every few weeks: pick 2-3 rows above
below "Confidence: solid," re-drill via `04-interview-questions.md`, update this file.
