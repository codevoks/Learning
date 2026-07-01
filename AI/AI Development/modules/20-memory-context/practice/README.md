# Module 20 — Assignments (Memory & Context Engineering)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`
> A1–A3 offline — `python <file>.py` → `_check()` pass.

## Progress checklist

- [ ] A1 — `conversation_buffer.py`
- [ ] A2 — `token_budget_trimmer.py`
- [ ] A3 — `memory_store.py`
- [ ] Active recall → NOTES

## Setup

```bash
cd modules/20-memory-context/practice
python3 -m venv .venv && source .venv/bin/activate
# A1-A3 sirf stdlib. Real long-term memory: pgvector (Module 05) + embeddings.
```

---

## A1 — Conversation buffer

| | |
|---|---|
| **Theory §** | §2 |
| **File** | `conversation_buffer.py` |
| **Kya** | Sliding-window short-term memory |
| **Pass** | `python conversation_buffer.py` → `_check()` asserts pass |

## A2 — Token budget trimmer

| | |
|---|---|
| **Theory §** | §3 |
| **File** | `token_budget_trimmer.py` |
| **Kya** | System kept, oldest dropped, budget met |
| **Pass** | `python token_budget_trimmer.py` → `_check()` asserts pass |

## A3 — Memory store

| | |
|---|---|
| **Theory §** | §5 |
| **File** | `memory_store.py` |
| **Kya** | Write + relevance retrieve |
| **Pass** | `python memory_store.py` → `_check()` asserts pass |

---

## Active recall (NOTES)

1. Short vs long-term memory example?
2. Budget cross ho to kya drop, kya nahi?
3. RAG vs context engineering?

**Stuck?** `@modules/20-memory-context/MODULE.md` + error paste.
