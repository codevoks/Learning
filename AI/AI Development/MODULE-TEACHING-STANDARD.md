# Module teaching standard — revision notes banned

> Har `MODULE.md` **textbook** hai, cheat sheet nahi.  
> Audience: **pehli baar seekh raha hai** ya **dusre stack se migrate** (TS/Node → Python/Go).

## Rule 1 — Syntax pehle, architecture baad mein

Har module jahan nayi language/framework ho, **§0 = language syntax from zero**:

- Har naya operator/symbol (`:=`, `@`, `async`, `*`, `[]byte`) — table + example + common mistake
- TS/JS parallel jahan helpful — par Python/Go assume mat karo
- **Terminal try**: chhota snippet copy-paste karke chalao, phir aage badho

High-level diagrams **§0 ke baad** aate hain — pehle nahi.

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

## Migration backlog

Track 0 modules: **00b, 00c, 00e** = syntax-first (in progress).  
Track 1 (01–11): migrate jab user module start kare — same standard apply.

Coach + agents: naya MODULE likhte waqt is file follow karo.
