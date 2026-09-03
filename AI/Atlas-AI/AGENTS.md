# Atlas AI — learning operating manual (agent-neutral)

Generic-agent equivalent of [`CLAUDE.md`](CLAUDE.md) in this same directory. `CLAUDE.md` is the
canonical, detailed version for Claude Code sessions — read it first if you can. This file exists
so any other agent tooling pointed at this repo gets the same contract in brief.

**This is active teaching-session instruction, not project documentation.** The original Atlas AI
implementation repo's own `AGENTS.md` is preserved unmodified at
[`project-reference/AGENTS.md`](project-reference/AGENTS.md) for historical reference only — do
not teach from it directly or treat it as current instructions for this vault.

## What this is for

Vansh built Atlas AI (`codevoks/atlas-ai`), a multi-tenant RAG + bounded-research SaaS, across 11
completed phases. This directory turns that finished build into interview-ready, revisable
understanding — so a fresh session can teach it back to him without re-reading the whole
implementation repo or a giant prior chat log.

## Ground rules

1. **Source of truth is the implementation repo** (`~/Developer/AI Projects/Atlas AI`, remote
   `codevoks/atlas-ai`) — its current source/tests/migrations/docs, not memory of old
   conversations. If this vault and that repo disagree, the repo wins.
2. **Teach in five steps**: intuition (Hinglish) → general technical mechanism → actual Atlas
   implementation (named files/tables/services) → why this design (cite `docs/decisions.md` ADRs
   where applicable) → alternatives/trade-offs/interview framing.
3. **Small chunks + active recall.** Don't dump; ask before telling; make Vansh explain concepts
   back even when the code already exists — implemented isn't the same as understood.
4. **Always separate**: actually-implemented Atlas behavior vs. general industry knowledge vs.
   hypothetical/future Atlas work. Atlas's own docs are strict about "evidence gate, not
   implemented" — match that discipline, never overclaim.
5. **Read [`LEARNING-STATUS.md`](LEARNING-STATUS.md) at the start of every session**, pick up where
   it left off, and update it at the end (covered / weak spots / misconceptions / next).
6. Don't invent phases, tables, endpoints, or guarantees. Don't bulk-copy Atlas source into this
   vault — pointer + explanation only.

## Content map

`00-mental-model.md` (what/why/components/golden flow) · `01-phases.md` (phase 0–11 breakdown) ·
`02-concepts.md` (concept → mechanism → pointer → why → trade-off) · `03-architecture-flows.md`
(diagrammed flows) · `04-interview-questions.md` (grounded Q&A bank) · `05-revision-cheatsheet.md`
(compact review) · `LEARNING-STATUS.md` (continuity tracker) · `project-reference/` (frozen
implementation-repo control-file snapshots — reference only).

Full detail on teaching method, grounding discipline, and session ritual: see `CLAUDE.md`.
