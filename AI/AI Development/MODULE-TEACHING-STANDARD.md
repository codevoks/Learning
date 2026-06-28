# Module teaching standard — revision notes banned

> Har `MODULE.md` **textbook** hai, cheat sheet nahi.  
> Audience: **pehli baar seekh raha hai** ya **dusre stack se migrate** (TS/Node → Python/Go).

## Rule 1 — §0 pehle (syntax OR terms)

**Code modules (00a–00e):** §0 = language/tool syntax from zero (`:=`, `@`, docker commands).

**AI modules (01–11):** §0 = **terms from zero** — token, embedding, RAG, agent, MCP… har term define karo pehle analogy ke saath. Phir architecture.

High-level diagrams **§0 ke baad** — pehle nahi.

## Migration status

| Module | Status |
|--------|--------|
| 00a–00e, 01–11 | ✅ textbook rewrite (§0 + session table + line tables) |

Coach + agents: `@MODULE-TEMPLATE.md` follow karo.

## Rule 2 — Line-by-line, handwaving nahi

Har code block ke neeche:

| Line / symbol | Matlab |
|---------------|--------|

Ya numbered steps: "Request flow 1 → 2 → 3".

**Banned:** sirf code dump + ek line summary.

## Rule 3 — Theory § → Practice assignment

Har theory section ke end pe:

> **→ Practice Ax** (pass: curl / command output)

Ek section padho → assignment → agla section. Poora module ek din nahi.

## Rule 4 — Common errors table

Har major step pe:

| Error message | Kyun | Fix |

## Rule 5 — Read order table

Module top pe session-by-session table — kya padhna, kya karna.

## Module checklist (before ship)

- [ ] §0 syntax exists (new language/framework modules)
- [ ] No unexplained symbols in first code block
- [ ] curl / go run / python commands with expected output
- [ ] Prerequisites honest ("00b skip kiya toh §0 cover karo")
- [ ] Active recall questions test understanding, not memory

## Migration status

All modules follow `@MODULE-TEACHING-STANDARD.md` + `@MODULE-TEMPLATE.md` — **textbook, not cheat sheet**. Track 0: syntax §0. Track 1: terms §0.
