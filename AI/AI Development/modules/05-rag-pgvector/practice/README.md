# Module 05 — Assignments (ek jagah)

> **Theory**: `../MODULE.md` (textbook — §0 RAG/chunking/embeddings/pgvector terms pehle)  
> **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`  
> **Standard**: `@MODULE-TEACHING-STANDARD.md` — har § ke baad mapped assignment neeche

**Prereq:** Module 00a Postgres Docker + `CREATE EXTENSION vector;` (MODULE.md §0 try block). Module 04 prompts — RAG answer step mein kaam aayega.

**Read order:** Session 2 → A1 · Session 3–4 → A2 · Session 5 → A3 · Session 6 → A4. Pehle MODULE.md end-to-end walkthrough (`sample_policy.txt`) khud chalao.

Order: A1 → A4. Code files mein `TODO` search karo.

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
| **Theory §** | §3 |
| **File** | `chunker.py` |
| **Kya** | Document loader + chunker with overlap |
| **Pass** | `python chunker.py` → `_check()` ke asserts pass (overlap + coverage) |

### Hints

- `RecursiveCharacterTextSplitter` concept — simple version khud pehle

---

## A2 — Embed + store

| | |
|---|---|
| **Theory §** | §4 |
| **File** | `embed_store.py` |
| **Kya** | Embed + pgvector store + similarity search |
| **Pass** | Query returns relevant chunk |

### Hints

- Postgres from 00a — `CREATE EXTENSION vector;`

---

## A3 — RAG endpoint

| | |
|---|---|
| **Theory §** | §2, §6 |
| **File** | `rag_endpoint.py` |
| **Kya** | RAG answer stub |
| **Pass** | Answer cites source chunk IDs |

---

## A4 — Failure cases (written)

| | |
|---|---|
| **Theory §** | §6 |
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
