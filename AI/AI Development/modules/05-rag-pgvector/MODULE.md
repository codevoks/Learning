# Module 05 — RAG + pgvector

> **Padho**: Isi file mein **Theory** — bahar mat jao.  
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`  
> **Ship**: **Python** `services/rag/` — Go platform phase 2 pe proxy karega (`@Projects.md` Project A).  
> **Nav**: ← [Module 04](../04-prompt-engineering/MODULE.md) · Next → [Module 06](../06-tools-function-calling/MODULE.md)

> **Kaun ke liye:** Pehli baar RAG seekh rahe ho. **§0 terms pehle** — pipeline diagram baad mein. Standard: `@MODULE-TEACHING-STANDARD.md`

## At a glance

| | |
|---|---|
| Prerequisites | Module 04 (prompts). Module 00a (Postgres Docker). Module 01 (embeddings API concept helpful) |
| Duration | ~5–7 sessions |
| Project? | No |
| Exit test | Chunk/retrieve pipeline + 3 RAG failure modes bina notes ke explain karo |

## Visual map

```
docs → ingest → chunk → embed → [pgvector]
                                      ↑
query → embed query → retrieve top-k ─┘
                              ↓
                    context + prompt → LLM → answer
```

**Mental model:** RAG = **Retrieve** (pehle relevant chunks dhoondo) + **Generate** (un chunks ke saath LLM se jawab banao). Poora PDF prompt mein mat daalo — sirf jo match kare woh lo.

**Redraw challenge:** Ingest → chunk → embed → store → retrieve → generate pipeline end-to-end bina dekhe draw karo.

---

## Read order (strict — session table)

| Session | Padho | Karo (Practice) |
|---------|-------|-----------------|
| 1 | §0 Terms + §1 Kyun RAG | Postgres + `CREATE EXTENSION vector;` |
| 2 | §2 Pipeline + §3 Chunking | **A1** — `chunker.py` |
| 3 | §4 Embeddings + pgvector | **A2** — `embed_store.py` |
| 4 | §5 Hybrid search (concept) | **A2** continued — similarity query test |
| 5 | §6 Failure modes + end-to-end | **A3** — `rag_endpoint.py` |
| 6 | Review + failure doc | **A4** — `FAILURE_CASES.md` |

---

## Learning hooks (optional — tera parallel)

| Concept | Parallel |
|---------|----------|
| Chunking | CSV chunked import (5MB limits) |
| Embeddings | Fingerprint / hash similarity |
| Top-k retrieval | 4-strategy cascade — cheapest first |
| Hybrid search | IBAN + invoice combo matching |
| Re-ingestion | Ledger correction replay |

---

## Theory

### §0. Terms pehli baar — RAG, chunking, embeddings, pgvector (25 min)

#### 0.1 RAG kya hai?

**RAG** = **R**etrieval-**A**ugmented **G**eneration.

```
Bina RAG:  User sawaal → LLM (sirf training memory) → jawab (purana / galat ho sakta)
RAG ke saath: User sawaal → relevant docs dhoondo → docs + sawaal → LLM → grounded jawab
```

**Analogy:** Open-book exam. Bina kitab = LLM weights. RAG = pehle index se sahi page kholo, phir jawab likho.

#### 0.2 Chunking kya hai?

Long document ko **chhote pieces** mein todo — taaki:
1. Embedding model ko fit ho
2. Retrieval sirf relevant piece laaye

```
Poora 50-page PDF → 200 chunks × ~500 characters
```

**Chunk** = ek text snippet + metadata (doc_id, page, etc.)

#### 0.3 Embedding kya hai?

**Embedding** = text ka **number vector** (list of floats) jo *meaning* capture kare.

```
"refund policy"  → [0.02, -0.11, 0.45, ...]   (1536 numbers — model dependent)
"return money"   → [0.03, -0.09, 0.43, ...]   (similar meaning → similar vector)
```

Similar meaning = vectors paas (cosine similarity high). Search = "query vector ke najdeek wale chunk vectors dhoondo."

#### 0.4 pgvector kya hai?

**pgvector** = PostgreSQL extension jo `vector` type store kare — tumhara existing Postgres, alag vector DB nahi.

```sql
CREATE EXTENSION vector;
-- ab columns mein vector(1536) type use kar sakte ho
```

**Analogy:** Postgres = ledger. pgvector = usi ledger mein "similarity index" column.

#### 0.5 Top-k retrieval

**Top-k** = similarity search se **k** best chunks lao (usually k=3–10).

```
Query embed → compare all chunk embeddings → sort by distance → LIMIT 5
```

#### 0.6 Terms quick reference

| Term | Ek line |
|------|---------|
| Ingest | Files load karke system mein laana |
| Index | Embeddings DB mein store + fast search |
| Cosine distance `<=>` | pgvector operator — chhota = zyada similar |
| Hallucination | Model ne context ke bina jhoot bola |
| Re-ingest | Docs update → purane chunks hatao, naye embed karo |

#### 0.7 Abhi try karo — Postgres + extension

Module 00a Docker Postgres assume:

```bash
docker ps   # postgres container running?
psql postgresql://postgres:postgres@localhost:5432/postgres -c "CREATE EXTENSION IF NOT EXISTS vector;"
# Expected: CREATE EXTENSION
```

**Common errors (§0):**

| Error | Kyun | Fix |
|-------|------|-----|
| `extension "vector" is not available` | pgvector image nahi | 00a docker-compose mein pgvector image |
| `connection refused` | Postgres down | `docker compose up -d` |
| Dimension mismatch baad mein | Model alag | Same model ingest + query dono |

**§0 checkpoint:**
1. RAG do steps mein kya hota hai?
2. Chunk kyun chahiye?
3. Embedding aur keyword search mein farq?

---

### §1. RAG kyun — LLM ko fresh/private knowledge do

#### Problem kya hai?

```
Company ka naya refund policy PDF → LLM training mein nahi tha
User: "30 din refund hai ya 14?"
Naive jawab: model guess karega (hallucination)
```

**Naive fix fail:**

```
Poora PDF prompt mein paste → context window overflow + $$$ + "lost in the middle"
```

**RAG fix:**

```
Sirf 3 relevant chunks retrieve → chhota context → cheaper + grounded
```

| Approach | Pros | Cons |
|----------|------|------|
| Fine-tune | Fast inference | Expensive, stale |
| Long context only | Simple | Cost, miss middle |
| RAG | Fresh docs, cite sources | Pipeline complexity |

> **→ Practice A1** prep — chunker banega jo ingest ke liye pieces dega.

---

### §2. Pipeline — ingest se answer tak

```mermaid
flowchart TB
    subgraph offline["Offline ingest (ek baar / cron)"]
        D[Documents] --> L[Load + parse]
        L --> C[Chunk]
        C --> E[Embed batches]
        E --> DB[(pgvector)]
    end
    subgraph online["Online query (har user request)"]
        Q[User question] --> QE[Embed query]
        QE --> R[Top-k similarity]
        DB --> R
        R --> P[Prompt: context + question]
        P --> LLM[Generate]
        LLM --> A[Answer + cite chunk_ids]
    end
```

#### Offline vs online

| Phase | Kab chalta | Slow? |
|-------|------------|-------|
| Offline ingest | Doc upload, nightly job | Haan — embed batches |
| Online query | User har sawaal | Fast — sirf 1 query embed + search |

**Request flow (online) — numbered:**

1. User: `"What is the refund window?"`
2. Query ko embed karo → vector `q`
3. SQL: `ORDER BY embedding <=> q LIMIT 5`
4. Chunk texts prompt mein: `"Context: ... Question: ..."`
5. LLM answer + chunk IDs cite karo

---

### §3. Chunking strategies (→ A1)

#### Problem kya hai?

Chunk bahut **chhota** → sentence ka context kata, galat retrieve.  
Chunk bahut **bada** → noise, relevant line dabb jaye ("lost in the middle").

#### Fixed size chunker — line by line

```python
def chunk_text(text: str, chunk_size: int = 500, overlap: int = 50) -> list[str]:
  """Split text into overlapping chunks."""
  if chunk_size <= overlap:
    raise ValueError("chunk_size must be > overlap")
  chunks: list[str] = []
  start = 0
  while start < len(text):
    end = start + chunk_size
    chunks.append(text[start:end])
    start = end - overlap  # next chunk pehle wale ka thoda repeat
  return chunks
```

| Line | Matlab |
|------|--------|
| `chunk_size=500` | ~500 characters per piece (tokens nahi — simple start) |
| `overlap=50` | 50 char repeat — sentence boundary cut se bachao |
| `start = end - overlap` | Agla chunk thoda peeche se — continuity |
| `chunks.append(text[start:end])` | Slice — Python string portion |

**Test:**

```python
text = "A" * 600 + "REFUND" + "B" * 600
parts = chunk_text(text, chunk_size=500, overlap=50)
print(len(parts))           # 3 ya zyada
print(any("REFUND" in p for p in parts))  # True
```

#### Strategies compare

| Strategy | How | Trade-off |
|----------|-----|-----------|
| Fixed size | 500 chars, overlap 50 | Simple, mid-sentence cut ho sakta |
| Recursive | split `\n\n`, then `.`, then char | Better structure |
| Semantic | embed sentences, merge while similar | Expensive ingest |

**Overlap kyun:** Agar "refund within 30" sentence boundary pe kata — overlap mein poora sentence next chunk mein aa jaye.

**Common errors (§3):**

| Symptom | Kyun | Fix |
|---------|------|-----|
| `REFUND` kisi chunk mein nahi | Chunk size chhota + no overlap | Overlap badhao |
| Duplicate answers | Overlap zyada + same chunk 3 baar retrieve | Dedupe chunk IDs |
| Gibberish chunks | Binary PDF raw read | Proper parser (pdfplumber, etc.) |

> **→ Practice A1** (`chunker.py`) — `load_document` + `chunk_text`. Pass: chunks with overlap.

---

### §4. Embeddings + pgvector (→ A2)

#### Problem kya hai?

Chunks list mein hai — ab unhe **searchable** banana hai. Har chunk → vector → Postgres.

#### Schema — line by line

```sql
CREATE EXTENSION IF NOT EXISTS vector;

CREATE TABLE IF NOT EXISTS chunks (
  id SERIAL PRIMARY KEY,
  doc_id TEXT NOT NULL,
  content TEXT NOT NULL,
  embedding vector(1536),  -- text-embedding-3-small = 1536 dims
  metadata JSONB DEFAULT '{}',
  created_at TIMESTAMPTZ DEFAULT NOW()
);

CREATE INDEX IF NOT EXISTS chunks_embedding_idx
  ON chunks USING hnsw (embedding vector_cosine_ops);
```

| Line | Matlab |
|------|--------|
| `vector(1536)` | Fixed length — model change = dimension change |
| `doc_id` | Kaunsi file se aaya |
| `metadata JSONB` | page, section — filter ke liye |
| `hnsw` index | Fast approximate nearest neighbor search |
| `vector_cosine_ops` | Cosine distance operator family |

#### Embed + insert — Python

```python
from openai import OpenAI
import psycopg2

client = OpenAI()

def embed_text(text: str) -> list[float]:
    resp = client.embeddings.create(
        model="text-embedding-3-small",
        input=text,
    )
    return resp.data[0].embedding

def store_chunk(conn, doc_id: str, content: str) -> int:
    vec = embed_text(content)
    with conn.cursor() as cur:
        cur.execute(
            """
            INSERT INTO chunks (doc_id, content, embedding)
            VALUES (%s, %s, %s::vector)
            RETURNING id
            """,
            (doc_id, content, vec),
        )
        row = cur.fetchone()
    conn.commit()
    return row[0]
```

| Line | Matlab |
|------|--------|
| `embeddings.create` | Text → vector API |
| `resp.data[0].embedding` | List of 1536 floats |
| `%s::vector` | psycopg2 string ko pgvector type |
| `RETURNING id` | Insert ke baad chunk ID — citation ke liye |

#### Similarity query

```python
def search_similar(conn, query: str, limit: int = 5) -> list[dict]:
    q_vec = embed_text(query)
    with conn.cursor() as cur:
        cur.execute(
            """
            SELECT id, doc_id, content,
                   1 - (embedding <=> %s::vector) AS score
            FROM chunks
            ORDER BY embedding <=> %s::vector
            LIMIT %s
            """,
            (q_vec, q_vec, limit),
        )
        rows = cur.fetchall()
    return [
        {"id": r[0], "doc_id": r[1], "content": r[2], "score": r[3]}
        for r in rows
    ]
```

| Symbol | Matlab |
|--------|--------|
| `<=>` | Cosine **distance** — 0 = identical |
| `1 - distance` | Distance → similarity score (1 = best) |
| `ORDER BY ... LIMIT` | Top-k nearest |

**Test:**

```python
conn = psycopg2.connect("postgresql://postgres:postgres@localhost:5432/postgres")
store_chunk(conn, "policy-v1", "Refunds allowed within 30 days with receipt.")
store_chunk(conn, "policy-v1", "Shipping is free for orders over fifty dollars.")
hits = search_similar(conn, "How long can I return a product?")
print(hits[0]["content"])  # refund wala chunk top pe
```

**Index choice:**

| Index | Pros | Cons |
|-------|------|------|
| IVFFlat | Faster build | Recall trade-off |
| HNSW | Better recall | More memory |

**Model change rule:** Embedding model badla → **saare chunks re-embed** — purane vectors comparable nahi.

**Common errors (§4):**

| Error | Kyun | Fix |
|-------|------|-----|
| `expected 1536 dimensions, not 3072` | Model mismatch | Same model + `vector(n)` match |
| Search returns random | Index not built / empty table | `CREATE INDEX`, verify rows |
| Slow search | No index | HNSW index on embedding column |

> **→ Practice A2** (`embed_store.py`) — embed + store + similarity. Pass: relevant chunk for test query.

---

### §5. Hybrid search — dense + keyword (concept)

#### Problem kya hai?

User: `"Invoice #INV-8842"` — embedding semantic search weak on exact IDs.  
User: `"return policy for damaged goods"` — keyword alone weak on paraphrase.

```mermaid
flowchart LR
    Q[Query] --> Dense[Embedding search]
    Q --> BM25[Keyword / tsvector]
    Dense --> Merge[RRF merge scores]
    BM25 --> Merge
    Merge --> TopK[Top-k chunks]
```

#### Kab hybrid use karo

| Query type | Dense | Keyword |
|------------|-------|---------|
| Invoice #, SKU, IBAN | weak | strong |
| "How do I feel about returns?" paraphrase | strong | weak |

**Merge (simple):**

```
final_score = α * dense_score + (1-α) * bm25_score
# ya Reciprocal Rank Fusion (RRF) — rank based, scale-free
```

**Tera hook:** Bank recon — IBAN exact match + fuzzy name = hybrid.

Assignment A2 mein sirf dense OK — hybrid A4 failure cases mein sochna.

---

### §6. Failure modes + end-to-end walkthrough (→ A3, A4)

#### Failure table

| Failure | Example | Fix |
|---------|---------|-----|
| Retrieval miss | Answer chunk mein hai par top-k mein nahi aaya | Chhota chunks, hybrid, reranker |
| Wrong chunk | Similar lekin galat doc | metadata filter (`doc_id`, date) |
| Hallucination | Model context ignore | "Answer only from context" prompt + cite |
| Injection in doc | PDF mein "ignore instructions" | Delimiters (Module 04) |
| Stale index | Policy update, purane chunks | Re-ingest pipeline, version tags |

**"Lost in the middle":** Bahut lamba context mein model start/end dekhta hai, beech ignore — isliye RAG mein **chhota relevant context** better.

---

### End-to-end walkthrough — ek chhota doc se answer

**Goal:** Ek policy file → chunk → embed → store → user query → cited answer.

**Step 1 — Sample document** (`sample_policy.txt`):

```
Acme Corp Refund Policy (2024).
1. Returns accepted within 30 days with original receipt.
2. Digital downloads are non-refundable after access.
3. Contact support@acme.com for damaged items.
```

**Step 2 — Chunk (§3)**

```python
from pathlib import Path
text = Path("sample_policy.txt").read_text()
chunks = chunk_text(text, chunk_size=200, overlap=30)
print(len(chunks), chunks[0][:80])
```

**Step 3 — Ingest (§4)**

```python
for i, c in enumerate(chunks):
    chunk_id = store_chunk(conn, "policy-2024", c)
    print("stored", chunk_id)
```

**Step 4 — Retrieve**

```python
hits = search_similar(conn, "Can I return after 3 weeks?", limit=3)
for h in hits:
    print(h["id"], h["score"], h["content"][:60])
```

Expected: chunk with "30 days" top score.

**Step 5 — Generate with prompt (Module 04)**

```python
def rag_answer(question: str) -> dict:
    hits = search_similar(conn, question, limit=3)
    context = "\n---\n".join(
        f"[chunk_{h['id']}] {h['content']}" for h in hits
    )
    messages = [
        {"role": "system", "content": """Answer ONLY using the context below.
If answer not in context, say "I don't know."
Cite chunk IDs like [chunk_12] in your answer."""},
        {"role": "user", "content": f"Context:\n{context}\n\nQuestion: {question}"},
    ]
    resp = client.chat.completions.create(
        model="gpt-4o-mini",
        messages=messages,
        temperature=0,
    )
    return {
        "answer": resp.choices[0].message.content,
        "sources": [h["id"] for h in hits],
    }

print(rag_answer("What is the refund window?"))
```

| Line | Matlab |
|------|--------|
| `context` joined chunks | LLM ko sirf retrieved text |
| `[chunk_id]` labels | Citation + debug |
| `ONLY using context` | Hallucination kam |
| `sources` in return | API response mein prove karo kahan se aaya |

**Step 6 — curl test (A3 FastAPI stub)**

```bash
uvicorn rag_endpoint:app --reload --port 8010
curl -s -X POST http://localhost:8010/rag \
  -H "Content-Type: application/json" \
  -d '{"question":"Can I return after 3 weeks?"}' | python3 -m json.tool
```

Expected JSON: `answer` mentions 30 days, `sources` array non-empty.

**Common errors (end-to-end):**

| Symptom | Kyun | Fix |
|---------|------|-----|
| "I don't know" always | Retrieval miss / empty DB | Re-ingest, query test §4 |
| Answer without citation | Prompt weak | Cite instruction + eval |
| Wrong 30 vs 14 days | Hallucination | temperature=0, stricter prompt |

> **→ Practice A3** (`rag_endpoint.py`) — RAG answer stub with chunk ID cites.  
> **→ Practice A4** (`FAILURE_CASES.md`) — 3 real failure queries + fix proposal.

---

## Practice

> **Saare assignments ek jagah**: [`practice/README.md`](practice/README.md)  
> Code **tum** likhoge. Stubs mein `TODO` search karo.

| # | Theory § | File | Kya karna hai | Pass when |
|---|----------|------|---------------|-----------|
| A1 | §3 | `practice/chunker.py` | Document loader + chunker | Chunks with overlap |
| A2 | §4 | `practice/embed_store.py` | Embed + pgvector store | Similarity returns relevant chunk |
| A3 | §2, §6 | `practice/rag_endpoint.py` | RAG answer stub | Answer cites source chunk IDs |
| A4 | §6 | `practice/FAILURE_CASES.md` | 3 failure queries + fixes | Coach/self review |

### A1 hints

- `RecursiveCharacterTextSplitter` concept — pehle simple version khud

### A2 hints

- Postgres from 00a — `CREATE EXTENSION vector;`

---

## Active recall (khud jawab likho NOTES mein)

1. Chunk size bada vs chota — trade-offs?
2. Embedding model change pe kya migrate karna padta hai?
3. "Lost in the middle" kya hai?
4. Dense vs hybrid — ek example query each?

**Chat drill** (optional): "Module 05 — 3 RAG failure modes explain karo"

---

## Progress checklist

- [ ] §0 terms clear (RAG, chunk, embedding, pgvector)
- [ ] Theory §1–§6 padh liya
- [ ] End-to-end walkthrough chalaya
- [ ] Redraw challenge kiya
- [ ] Practice A1–A4 pass
- [ ] Active recall NOTES mein likha

---

## Optional appendix

- [pgvector README](https://github.com/pgvector/pgvector) — index tuning
- [OpenAI Embeddings guide](https://platform.openai.com/docs/guides/embeddings) — model dimensions
