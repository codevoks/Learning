# Practice — Module 05

Postgres + pgvector from repo root `docker compose`.

```bash
cd modules/05-rag-pgvector/practice
python3 -m venv .venv
source .venv/bin/activate
pip install psycopg2-binary openai python-dotenv
```

```sql
-- run once in postgres
CREATE EXTENSION IF NOT EXISTS vector;
```

| File | Assignment |
|------|------------|
| `chunker.py` | A1 |
| `embed_store.py` | A2 |
| `rag_endpoint.py` | A3 |
| `FAILURE_CASES.md` | A4 |
