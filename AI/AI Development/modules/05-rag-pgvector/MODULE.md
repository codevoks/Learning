# Module 05 — RAG + pgvector

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Ship**: **Python** `services/rag/` (`@Projects.md` Project A).
> **Nav**: ← [Module 04](../04-prompt-engineering/MODULE.md) · Next → [Module 06](../06-tools-function-calling/MODULE.md)

> **Format**: Textbook — §0 terms pehle (RAG, chunk, embedding, pgvector), prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`

## At a glance

| | |
|---|---|
| Prerequisites | Module 04 (prompts). 00a (Postgres Docker). 00d/01 (embeddings concept) |
| Duration | ~5–7 sessions |
| Project? | No (par Project A ki neev) |
| Exit test | Chunk/retrieve pipeline + 3 RAG failure modes bina notes ke samjhao |

## Yeh module kis baare mein hai

LLM ka ek bada problem hai: usе sirf wahi pata hai jo training mein tha — tumhari company ka naya refund policy PDF, internal docs, kal ka data — kuch nahi. Aur agar tum poochho, wo confidently *guess* (hallucinate) kar dega. RAG (Retrieval-Augmented Generation) isका standard ilaaj hai aur 2026 ki sabse demanded skill — yeh LLM ko **tumhare** documents pe "grounded" jawab dene deta hai.

Core idea ek line mein: poora PDF prompt mein mat thunso. Pehle sawaal se **relevant tukde dhoondho** (Retrieve), phir sirf un tukdon ke saath LLM se jawab banwao (Generate). Open-book exam socho — bina kitab = LLM ki yaaddasht (purani, galat), RAG = pehle sahi page kholo phir likho.

```
docs → ingest → chunk → embed → [pgvector]
                                    ↑
query → embed query → retrieve top-k ┘ → context + prompt → LLM → answer
```

**Redraw challenge:** Ingest → chunk → embed → store → retrieve → generate, end-to-end bina dekhe banao.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + §1 Kyun RAG | Postgres + `CREATE EXTENSION vector;` |
| 2 | §2 Pipeline + §3 Chunking | **A1** — `chunker.py` |
| 3 | §4 Embeddings + pgvector | **A2** — `embed_store.py` |
| 4 | §5 Hybrid search | **A2** similarity query test |
| 5 | §6 Failure modes + end-to-end | **A3** — `rag_endpoint.py` |
| 6 | Review | **A4** — `FAILURE_CASES.md` |

---

## Theory

### §0. Terms pehli baar — RAG, chunking, embeddings, pgvector (25 min)

**RAG (Retrieval-Augmented Generation).** Do-step process hai. Bina RAG: user sawaal → LLM (sirf apni training memory) → jawab jo purana/galat ho sakta hai. RAG ke saath: user sawaal → relevant docs **dhoondho** → docs + sawaal → LLM → grounded jawab. Bas yahi — "pehle dhoondho, phir jawab banao".

**Chunking.** Lambे document ko **chhote tukdon** mein todna. Do reason: embedding model ki ek size limit hoti hai, aur retrieval ko sirf *relevant* tukda chahiye, poori 50-page PDF nahi. Ek 50-page PDF shायad 200 chunks × ~500 characters ban jaaye. Har chunk = ek text snippet + metadata (doc_id, page).

**Embedding.** Text ka **number vector** jo *meaning* capture karता hai (Module 00d se familiar). "refund policy" aur "return money" ke vectors paas-paas honge (high cosine similarity), kyunki matlab milta-julta hai. RAG mein search ka matlab — "query ke vector ke najdeek wale chunk vectors dhoondo".

**pgvector.** PostgreSQL ka ek extension jo `vector` type store karne deta hai — matlab tumhe alag se koi vector database nahi chahiye, tumhara existing Postgres hi kaafi hai. `CREATE EXTENSION vector;` ke baad columns mein `vector(1536)` type use kar sakte ho. Soch: Postgres = ledger, pgvector = usi ledger mein ek "similarity index" column.

**Top-k retrieval.** Similarity search se **k** best chunks lana (aksar k=3–10): query embed karo → sab chunk embeddings se compare → distance se sort → `LIMIT 5`.

Abhi Postgres pe extension chalao (00a ka Docker Postgres assume):

```bash
docker ps   # postgres container chal raha?
psql postgresql://postgres:postgres@localhost:5432/postgres -c "CREATE EXTENSION IF NOT EXISTS vector;"
# Expected: CREATE EXTENSION
```

> **Ruko, socho:** Tumne docs `text-embedding-3-small` se embed kiye, par query embed karne ke liye galti se alag model use kar liya. Search kaisा chalega? (Jawab: kachra — dono vectors alag "space" mein hain, unke beech distance bekaar. Ingest aur query **same model** se hone chahiye, hamesha.)

**§0 checkpoint (NOTES mein):** (1) RAG ke do steps? (2) Chunk kyun chahiye? (3) Embedding aur keyword search ka farak?

---

### §1. RAG kyun — LLM ko fresh/private knowledge do

Concrete problem: company ka naya refund policy PDF LLM ki training mein tha hi nahi. User poochhta hai "30 din refund hai ya 14?" — naive LLM guess karega (hallucination), aur galat policy bata sakta hai, jo legal problem hai.

Pehla naive fix — "poora PDF prompt mein paste kar do" — fail karta hai: context window overflow, bahut paisa, aur "lost in the middle" (lambे context mein model beech ki cheezein miss karta hai). RAG smart fix hai — sirf 3 relevant chunks retrieve karo, chhota context, sasta aur grounded.

Teen approaches compare karo: fine-tune (fast inference par mehenga aur jaldi stale), sirf long-context (simple par costly aur middle miss), aur RAG (fresh docs + sources cite kar sakte ho, par pipeline complexity). RAG zyादातar production cases ka default hai.

> **→ Practice A1** prep — chunker banega jo ingest ke liye pieces dega.

---

### §2. Pipeline — ingest se answer tak

RAG ke do alag phases hain, aur yeh farak samajhna zaroori hai. **Offline ingest** (doc upload ya nightly cron pe chalता hai, slow OK): documents load/parse → chunk → batches mein embed → pgvector mein store. **Online query** (har user request pe, fast hona chahiye): query embed karo → top-k similarity → context + question prompt → LLM generate → answer + chunk_ids cite. Ingest ek baar ka heavy kaam hai; query har baar ka light kaam (sirf 1 embed + ek SQL search).

Online flow numbered:

```
1. User: "What is the refund window?"
2. Query embed → vector q
3. SQL: ORDER BY embedding <=> q LIMIT 5
4. Chunk texts ko prompt mein: "Context: ... Question: ..."
5. LLM answer + chunk IDs cite
```

---

### §3. Chunking strategies

Chunk size ka ek **Goldilocks problem** hai. Bahut **chhota** chunk → sentence ka context kat jaata hai, galat retrieve. Bahut **bada** chunk → noise, relevant line dab jaati hai (wahi "lost in the middle"). Sahi size beech mein hai. Ek simple fixed-size chunker:

```python
def chunk_text(text: str, chunk_size: int = 500, overlap: int = 50) -> list[str]:
    if chunk_size <= overlap:
        raise ValueError("chunk_size must be > overlap")
    chunks, start = [], 0
    while start < len(text):
        end = start + chunk_size
        chunks.append(text[start:end])
        start = end - overlap        # agla chunk thoda peeche se — continuity
    return chunks
```

Asli trick `overlap` mein hai. Socho "Refund within 30 days" sentence theek chunk boundary pe kat gaya — pehle chunk mein "Refund within", doosre mein "30 days". Ab "30 days" waala sawaal poora context nahi paayega. Overlap (50 char repeat) se boundary ke aas-paas ka text dono chunks mein aa jaata hai, sentence tootta nahi. Aage behtar strategies hain — recursive (pehle `\n\n` pe split, phir `.`, phir char) aur semantic (similar sentences merge karo, par ingest mehenga) — par fixed-size + overlap shuruaat ke liye theek hai.

#### §3 common errors

| Symptom | Kyun | Fix |
|---------|------|-----|
| Keyword kisi chunk mein nahi | Chunk chhota + no overlap | Overlap badhao |
| Duplicate answers | Overlap zyada, same chunk 3x retrieve | Chunk IDs dedupe |
| Gibberish chunks | Binary PDF raw read | Proper parser (pdfplumber) |

> **→ Practice A1** (`chunker.py`) — `load_document` + `chunk_text`. Pass: chunks with overlap.

---

### §4. Embeddings + pgvector

Chunks list mein hain — ab unhe **searchable** banana hai. Har chunk ko vector banao aur Postgres mein store karo. Schema:

```sql
CREATE EXTENSION IF NOT EXISTS vector;
CREATE TABLE IF NOT EXISTS chunks (
  id SERIAL PRIMARY KEY,
  doc_id TEXT NOT NULL,
  content TEXT NOT NULL,
  embedding vector(1536),   -- text-embedding-3-small = 1536 dims
  metadata JSONB DEFAULT '{}',
  created_at TIMESTAMPTZ DEFAULT NOW()
);
CREATE INDEX IF NOT EXISTS chunks_embedding_idx
  ON chunks USING hnsw (embedding vector_cosine_ops);
```

Do cheezein dhyaan se. `embedding vector(1536)` ki length **fixed** hai aur model se bandhi hai — model badla to dimension badal jaayega aur purane vectors bekaar. Aur woh `hnsw` index fast approximate-nearest-neighbor search ke liye hai — bina index ke har search poori table scan karega (slow). Embed + insert:

```python
def embed_text(text: str) -> list[float]:
    return client.embeddings.create(model="text-embedding-3-small", input=text).data[0].embedding

def store_chunk(conn, doc_id: str, content: str) -> int:
    vec = embed_text(content)
    with conn.cursor() as cur:
        cur.execute("INSERT INTO chunks (doc_id, content, embedding) VALUES (%s, %s, %s::vector) RETURNING id",
                    (doc_id, content, vec))
        row = cur.fetchone()
    conn.commit()
    return row[0]
```

`%s::vector` psycopg2 ke string ko pgvector type mein cast karta hai, aur `RETURNING id` insert ke baad chunk ka ID deta hai (citation ke liye zaroori). Similarity query:

```python
def search_similar(conn, query: str, limit: int = 5) -> list[dict]:
    q = embed_text(query)
    with conn.cursor() as cur:
        cur.execute("""SELECT id, doc_id, content, 1 - (embedding <=> %s::vector) AS score
                       FROM chunks ORDER BY embedding <=> %s::vector LIMIT %s""",
                    (q, q, limit))
        rows = cur.fetchall()
    return [{"id": r[0], "doc_id": r[1], "content": r[2], "score": r[3]} for r in rows]
```

Yahan `<=>` pgvector ka cosine **distance** operator hai (0 = identical), isliye `1 - distance` se hum use ek similarity score banate hain (1 = best). `ORDER BY ... LIMIT` top-k nearest deta hai.

> **Ruko, socho:** Tumne embedding model `3-small` (1536) se `3-large` (3072) pe switch kiya. Bina kuch aur kiye search chalega? (Jawab: nahi — `vector(1536)` column 3072-dim vector reject karegа, aur agar column badal bhi do, purane chunks ab naye query se comparable nahi. Model change = **saare chunks re-embed**.)

#### §4 common errors

| Error | Kyun | Fix |
|-------|------|-----|
| `expected 1536 dimensions, not 3072` | Model mismatch | Same model + `vector(n)` match |
| Search random | Index nahi / table khaali | `CREATE INDEX`, rows verify |
| Slow search | No index | embedding column pe HNSW |

> **→ Practice A2** (`embed_store.py`) — embed + store + similarity. Pass: test query ka relevant chunk top pe.

---

### §5. Hybrid search — dense + keyword

Pure embedding (dense) search ki bhi ek seemа hai. User `"Invoice #INV-8842"` poochhe — semantic search exact IDs pe weak hai (number ka koi "meaning" nahi). Ulta, `"return policy for damaged goods"` jaisी paraphrase pe keyword-only search weak hai. **Hybrid search** dono ko jodता hai: embedding search + keyword search (Postgres ka `tsvector`/BM25), phir scores merge.

Merge ka simple tareeka: `final = α·dense + (1-α)·keyword`, ya Reciprocal Rank Fusion (RRF) jo rank-based aur scale-free hai. Yeh bilkul tumhare bank-recon waale din jaisा hai — IBAN ka exact match + naam ka fuzzy match milाke best result. Practice A2 mein sirf dense theek hai; hybrid ko A4 ke failure-cases mein sochna.

---

### §6. Failure modes + end-to-end

RAG bahut jagah toot sakta hai, aur interview mein yahi poochha jaata hai. Paanch common failures aur unke fixes:

| Failure | Example | Fix |
|---------|---------|-----|
| Retrieval miss | Answer chunk mein hai par top-k mein nahi aaya | Chhote chunks, hybrid, reranker |
| Wrong chunk | Similar par galat doc | metadata filter (`doc_id`, date) |
| Hallucination | Model context ignore karke jhoot | "Answer only from context" + cite |
| Doc injection | PDF mein "ignore instructions" | Delimiters (Module 04) |
| Stale index | Policy update, purane chunks | Re-ingest + version tags |

Yeh "lost in the middle" baar-baar aaya — yeh phenomenon hai ki bahut lambे context mein model start aur end dekhta hai par beech ko ignore karta hai. Isiliye RAG mein chhota, relevant context bade context se behtar hai.

**End-to-end ek chhote doc se** (yahi A3 hai): ek policy file ko chunk karo → embed + store → user query pe retrieve karo → phir generate. Generate step mein prompt critical hai:

```python
def rag_answer(question: str) -> dict:
    hits = search_similar(conn, question, limit=3)
    context = "\n---\n".join(f"[chunk_{h['id']}] {h['content']}" for h in hits)
    messages = [
        {"role": "system", "content": 'Answer ONLY using the context below. If not in context, say "I don\'t know." Cite chunk IDs like [chunk_12].'},
        {"role": "user", "content": f"Context:\n{context}\n\nQuestion: {question}"},
    ]
    resp = client.chat.completions.create(model="gpt-4o-mini", messages=messages, temperature=0)
    return {"answer": resp.choices[0].message.content, "sources": [h["id"] for h in hits]}
```

Teen cheezein hallucination rokti hain: context mein sirf retrieved chunks dena, "ONLY using the context" + "I don't know" instruction, aur chunk IDs cite karwana (taaki tum verify kar sako jawab kahan se aaya — `sources` API response mein bhi return karo). FastAPI stub pe curl test:

```bash
uvicorn rag_endpoint:app --reload --port 8010
curl -s -X POST http://localhost:8010/rag -H "Content-Type: application/json" \
  -d '{"question":"Can I return after 3 weeks?"}' | python3 -m json.tool
# answer mein "30 days", sources array non-empty
```

#### end-to-end common errors

| Symptom | Kyun | Fix |
|---------|------|-----|
| Hamesha "I don't know" | Retrieval miss / DB khaali | Re-ingest, §4 query test |
| Citation nahi | Prompt weak | Cite instruction + eval |
| Galat 30 vs 14 days | Hallucination | `temperature=0`, stricter prompt |

> **→ Practice A3** (`rag_endpoint.py`) — RAG answer with chunk-ID cites.
> **→ Practice A4** (`FAILURE_CASES.md`) — 3 real failure queries + fix proposal.

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge (`TODO` search).

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §3 | `chunker.py` | Chunks with overlap |
| A2 | §4 | `embed_store.py` | Similarity relevant chunk laaye |
| A3 | §2, §6 | `rag_endpoint.py` | Answer source chunk IDs cite kare |
| A4 | §6 | `FAILURE_CASES.md` | 3 failure queries + fixes |

### Hints
- A1: pehle simple version khud, phir `RecursiveCharacterTextSplitter` concept.
- A2: Postgres 00a se — `CREATE EXTENSION vector;`.

---

## Active recall (khud jawab likho NOTES mein)

1. Chunk size bada vs chhota — trade-offs?
2. Embedding model change pe kya migrate karna padta hai aur kyun?
3. "Lost in the middle" kya hai?
4. Dense vs hybrid — ek-ek example query?

**Chat drill** (optional): "Module 05 — 3 RAG failure modes samjhao."

---

## Progress checklist

- [ ] §0 terms clear (RAG, chunk, embedding, pgvector)
- [ ] Theory §1–§6 padha
- [ ] End-to-end walkthrough chalaya
- [ ] Redraw challenge
- [ ] Practice A1–A4 pass
- [ ] Active recall NOTES mein

---

## Optional appendix

- [pgvector README](https://github.com/pgvector/pgvector)
- [OpenAI Embeddings guide](https://platform.openai.com/docs/guides/embeddings)
