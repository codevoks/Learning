# MODULE.md template — copy structure, not content

> Har module isi skeleton follow kare. `@MODULE-TEACHING-STANDARD.md`

```markdown
# Module XX — Title

> Padho / Likho / Nav links

> **Format**: Textbook — §0 pehle (syntax OR terms from zero). `@MODULE-TEACHING-STANDARD.md`

## At a glance
| Prerequisites | Duration | Exit test |

## Visual map
+ Mental model (1 paragraph plain Hinglish)
+ Redraw challenge

## Read order (strict — session table)
| Session | Padho | Karo (Practice) |

## Learning hooks (optional — tera parallel)

## Theory

### §0. [Syntax OR "Terms pehli baar"]
- Har naya symbol/term define BEFORE use — **prose mein**, table-row mein nahi
- TS/infra parallel wakya ke andar (table cell mein nahi)
- Terminal/curl try block with expected output
- Common errors table (yeh table reference hai — rakho)
- §0 checkpoint questions

### §1. [First concrete concept — problem pehle]
- "Problem/kyun seekh rahe ho" paragraph se shuru
- Code block ke baad **narration** — sahi 2–3 cheezein + kyun (line-by-line table NAHI)
- Ek worked example numbers ke saath develop karo
- 1–2 "ruko socho" beats
- curl / python / go run test with expected output
- Common errors table (reference)
- → Practice A1

### §2…§N
(same pattern — each section ends with → Practice Ax)

## Practice
(table: # | Theory § | File | Pass when)
+ link practice/README.md

## Active recall

## Progress checklist

## Optional appendix
```

**AI concept modules (01–11):** §0 = "LLM/API/RAG term pehli baar" — token, embedding, agent, etc. with analogy + mini example.

**Code modules (00a–00e):** §0 = syntax or tooling from zero.

**Banned:** har concept ko table-row mein define karna; code ke neeche mechanical line-by-line table. Prose pehle, table sirf reference (errors/params/compare) ke liye. Voice copy: [`modules/01-llm-apis/MODULE.md`](modules/01-llm-apis/MODULE.md).
