# Module 05 — Assignments (ek jagah)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`

**Prereq:** 00a Postgres + `CREATE EXTENSION vector;`

Order: A1 → A4. `TODO` search in code files.

---

## Progress checklist

- [ ] A1 — `chunker.py`
- [ ] A2 — `embed_store.py`
- [ ] A3 — `rag_endpoint.py`
- [ ] A4 — `FAILURE_CASES.md`
- [ ] Active recall → NOTES
- [ ] Redraw challenge

---

## Setup

```bash
cd modules/05-rag-pgvector/practice
python3 -m venv .venv && source .venv/bin/activate
pip install openai python-dotenv psycopg2-binary numpy httpx fastapi uvicorn
```

---

## A1 — Chunker

| | |
|---|---|
| **File** | `chunker.py` |
| **Kya** | Document loader + chunker with overlap |
| **Pass** | Chunks with overlap produced |

### Hints

- `RecursiveCharacterTextSplitter` concept — simple version khud pehle

---

## A2 — Embed + store

| | |
|---|---|
| **File** | `embed_store.py` |
| **Kya** | Embed + pgvector store + similarity search |
| **Pass** | Query returns relevant chunk |

### Hints

- Postgres from 00a — `CREATE EXTENSION vector;`

---

## A3 — RAG endpoint

| | |
|---|---|
| **File** | `rag_endpoint.py` |
| **Kya** | RAG answer stub |
| **Pass** | Answer cites source chunk IDs |

---

## A4 — Failure cases (written)

| | |
|---|---|
| **File** | `FAILURE_CASES.md` |
| **Kya** | 3 failure queries + fixes |
| **Pass** | Coach / self review |

---

## Active recall (NOTES)

1. Chunk size bada vs chota trade-offs?
2. Embedding model change → kya migrate?
3. "Lost in the middle" kya hai?

---

## Files

| File | Assignment |
|------|------------|
| `chunker.py` | A1 |
| `embed_store.py` | A2 |
| `rag_endpoint.py` | A3 |
| `FAILURE_CASES.md` | A4 |

**Stuck?** `@modules/05-rag-pgvector/MODULE.md` + error paste.
