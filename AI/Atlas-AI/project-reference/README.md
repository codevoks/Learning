# Project reference (snapshot, not active instructions)

The three files in this folder are **verbatim snapshots** of the original project-control
files from the Atlas AI implementation repository
([`codevoks/atlas-ai`](https://github.com/codevoks/atlas-ai)), copied on 2026-09-03:

- `AGENTS.md` — the implementation repo's agent operating manual
- `CLAUDE.md` — the implementation repo's Claude Code operating manual
- `PROMPT.md` — the implementation repo's build/collaboration prompt

They document how the Atlas AI *product* was actually built (phase discipline, invariants,
commands, workflow) and are preserved here purely as historical/reference material — so a
future session can see exactly what governed construction of the system being studied.

**These are not active learning instructions.** They are not rewritten, summarized into, or
merged with the learning material in this directory. The active learning files that a
teaching session should actually load are at the root of `AI/Atlas-AI/`:

- [`../AGENTS.md`](../AGENTS.md)
- [`../CLAUDE.md`](../CLAUDE.md)

Note: the source repository has no `PROMPTS.md` (plural) file — only `PROMPT.md`, copied above.

If the implementation repository's control files change in a future update, re-sync this
snapshot deliberately (don't silently drift) and note the date of the re-sync.
