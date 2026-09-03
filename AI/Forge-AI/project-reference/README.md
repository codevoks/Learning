# Project reference (snapshot, not active instructions)

The three files in this folder are **verbatim snapshots** of the original project-control
files from the Forge AI implementation repository
([`codevoks/forge-ai`](https://github.com/codevoks/forge-ai)), copied on 2026-09-03 from a
repo state with all 14 planned phases (Phase 00–13) complete, plus one final
whole-project audit:

- `AGENTS.md` — the implementation repo's canonical, permanent agent operating manual
- `CLAUDE.md` — the implementation repo's local-only Claude Code operating guide (distills
  `AGENTS.md` into a Claude-Code-shaped manual; `AGENTS.md` wins on any conflict)
- `PROMPT.md` — the implementation repo's build/collaboration prompt

They document how the Forge AI *product* was actually built (phase discipline, architecture
invariants, security invariants, zero-cost requirement, git discipline, commands) and are
preserved here purely as historical/reference material — so a future session can see exactly
what governed construction of the system being studied.

**These are not active learning instructions.** They are not rewritten, summarized into, or
merged with the learning material in this directory. The active learning files that a
teaching session should actually load are at the root of `AI/Forge-AI/`:

- [`../AGENTS.md`](../AGENTS.md)
- [`../CLAUDE.md`](../CLAUDE.md)

Both `AGENTS.md` and `CLAUDE.md` existed in the implementation repo at snapshot time; there
was no `PROMPTS.md` (plural), only `PROMPT.md` (singular), copied above as-is.

Note: in the implementation repo, none of these three files are tracked by git — they are
kept out of version control deliberately (`.git/info/exclude`, per the repo's own privacy
policy) and only exist in local clones. This snapshot is therefore the only durable record of
their content; if you want the latest version, re-copy from a current local clone of
`codevoks/forge-ai` rather than looking for them on GitHub.

If the implementation repository's control files change in a future update, re-sync this
snapshot deliberately (don't silently drift) and note the date of the re-sync.
