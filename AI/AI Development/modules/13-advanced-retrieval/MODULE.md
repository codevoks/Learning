# Module 13 — Advanced Retrieval & Reranking

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 12](../12-guardrails-safety/MODULE.md) · Next → [Module 14](../14-finetuning/MODULE.md)

> **Format**: Textbook — §0 terms zero se, prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`
> **Track 2 (advanced):** Module 05 (RAG) ka production upgrade.

## At a glance

| | |
|---|---|
| Prerequisites | Module 05 (RAG + pgvector), 00d (embeddings), 10 (evals) |
| Duration | ~4–6 sessions |
| Project? | No (Project A RAG ki quality ceiling yahan uthti hai) |
| Exit test | Retrieve→rerank two-stage + hybrid + retrieval metrics bina notes ke samjhao |

## Yeh module kis baare mein hai

Module 05 mein tumne basic RAG banaya — embed, top-k, generate. Interview mein woh "toy RAG" hai. Jab interviewer poochhta hai "aapka RAG relevant doc miss kar raha hai, kya karenge?" — wahan yeh module kaam aata hai. Production RAG ki quality ka 80% **retrieval** se aata hai (generation nahi) — agar sahi chunk retrieve hi nahi hua, best LLM bhi galat jawab dega ("garbage in, garbage out"). Yeh module retrieval ko toy se production banata hai: hybrid search, reranking, query transformation, aur measurement.

Ek core insight jo poore module ko baandhता hai: **retrieval ek do-stage kaam hona chahiye** — pehle sasta-aur-broad (bahut candidates recall karo, koi miss na ho), phir mehenga-aur-precise (unme se best ko rerank karo). Single-stage embedding search dono ek saath nahi kar sakta.

```
query → [query transform] → ┌─ dense (embeddings) ─┐
                            ├─ sparse (BM25) ───────┤→ RRF merge → top-N candidates
                            └───────────────────────┘        ↓
                                              [reranker: cross-encoder] → top-k precise → LLM
```

**Redraw challenge**: two-stage retrieval — hybrid recall → rerank → generate. Bina dekhe banao.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + §1 Naive top-k kahan fail | Socho: 05 ka RAG kaunse query pe miss karega |
| 2 | §2 Hybrid search + RRF | **A1** — `rrf_fusion.py` |
| 3 | §3 Reranking | **A2** — `mmr_rerank.py` |
| 4 | §4 Query transformation | **A4** — `query_rewrite.py` |
| 5 | §5 Contextual + §6 Retrieval eval | **A3** — `retrieval_metrics.py` |

---

## Theory

### §0. Terms pehli baar — reranker, hybrid, RRF, HyDE

**Bi-encoder vs cross-encoder.** Yeh farak reranking ka poora foundation hai. **Bi-encoder** (Module 05 ka embedding model) query aur doc ko *alag-alag* vector mein badalता hai, phir cosine — fast (docs pre-computed), par kam precise (query aur doc ek doosre ko "dekhte" nahi). **Cross-encoder** query aur doc ko *ek saath* model mein daalta hai aur ek relevance score deta hai — bahut precise (interaction dekhta hai), par slow (har query-doc pair ka fresh compute). Isliye: bi-encoder se hazaron docs se top-100 recall karo (fast), phir cross-encoder se un 100 ko rerank karke top-5 lo (precise). Yahi **reranker** hai.

**Hybrid search.** Dense (embedding/semantic) + sparse (keyword/BM25) search dono chalाke merge karna. Dense paraphrase pakadta hai; sparse exact terms (IDs, names, jargon) pakadta hai (Module 05 §5). Dono ki strength chahiye.

**BM25.** Classic keyword-ranking algorithm (TF-IDF ka evolved version) — exact term match pe strong. Postgres full-text search (`tsvector`) isका ek roop deta hai.

**RRF (Reciprocal Rank Fusion).** Do (ya zyada) ranked lists ko merge karne ka simple, robust tareeka. Har doc ka score = sum over lists of `1/(k + rank)`. Iska faayda — scores ko normalize karne ki zaroorat nahi (dense cosine aur BM25 scores alag scale pe hain); yeh sirf **rank** use karta hai, isliye scale-free.

**Query transformation.** User ka raw query aksar retrieval ke liye best nahi hota. **Rewriting** — query ko clean/expand karna. **HyDE (Hypothetical Document Embeddings)** — LLM se ek *fake ideal answer* likhwaao aur *uska* embedding search karo (answer, answer se zyada match karta hai vs question). **Multi-query** — ek query ke kai variants banaake sabse retrieve karo. **Decomposition** — complex query ko sub-queries mein todna.

**MMR (Maximal Marginal Relevance).** Top-k choose karte waqt sirf relevance nahi, **diversity** bhi — taaki 5 chunks lagभग same baat na bolein. MMR relevance aur "already-selected se kitna alag" dono balance karta hai.

**Retrieval metrics.** **Recall@k** — top-k mein sahi doc aaya kya (kitni baar)? **MRR (Mean Reciprocal Rank)** — sahi doc kis rank pe aaya (1/rank ka average)? **nDCG** — rank-weighted relevance. Yeh generation ke bina retrieval ko akela measure karte hain.

> **Ruko, socho:** Bi-encoder hazaron docs pe fast hai aur cross-encoder precise — to sab kuch cross-encoder se kyun nahi karte? (Jawab: cross-encoder har query-doc pair ka fresh forward-pass maangता hai — 1 million docs pe 1 million model calls per query = unusable latency/cost. Isliye bi-encoder se broadly recall karke chhote candidate set pe hi cross-encoder chalate hain.)

**§0 checkpoint:** (1) Bi vs cross encoder — kaunsa fast, kaunsa precise? (2) RRF scores normalize kyun nahi karta? (3) HyDE ka core trick kya hai?

---

### §1. Naive top-k kahan fail karta hai

Module 05 ka pure-embedding top-k teen jagah tootता hai. **Recall miss** — sahi jawab wale chunk ka embedding query se thoda door hota hai (alag wording), to wo top-k mein aata hi nahi, aur LLM ko wo kabhi milta nahi (yeh sabse bada RAG failure — jawab data mein tha par retrieve nahi hua). **Exact-match blindness** — "Invoice #INV-8842" jaise IDs/codes pe semantic search weak hai (number ka "meaning" nahi). **Redundancy** — top-5 mein 5 chunks jo lagभग same line bol rahe (ek hi doc ke overlapping chunks), to context waste, doosra angle miss.

Solution stack seedha map hota hai: recall miss → hybrid + rerank (broad recall phir precise); exact-match → hybrid (BM25 side); redundancy → MMR diversity. Yeh module har ek deta hai.

> **→ Practice A1** — RRF se shuru, kyunki wahi hybrid ka core merge hai.

---

### §2. Hybrid search + RRF fusion

Dense aur sparse dono chalाo, phir merge. Merge ka naive tareeka scores ko weighted-add karna hai (`α·dense + (1-α)·sparse`) — par dense cosine (0–1) aur BM25 (0–unbounded) alag scale pe hain, to yeh tuning-heavy aur nazuk hai. **RRF** isе elegantly solve karta hai — sirf rank use karo, score nahi:

```
RRF_score(doc) = Σ  1 / (k + rank_in_list_i)      # k usually 60
              over each list where doc appears
```

Example: doc A dense-list mein rank 1, BM25-list mein rank 3 (k=60): score = 1/61 + 1/63. Doc B dense rank 2, BM25 mein absent: 1/62. A > B. Jo doc **dono** lists mein upar aata hai, uska score naturally sabse zyada — yani consensus reward hota hai. Aur kyunki sirf rank matter karta hai, tumhe dense aur BM25 scores ko normalize nahi karna padta — yahi RRF ki khoobsurti hai.

> **Ruko, socho:** Ek doc dense list mein rank 1 hai par BM25 list mein bilkul nahi. Ek doosra doc dono lists mein rank 2 hai. RRF (k=60) mein kaun jeetega? (Jawab: pehla = 1/61 ≈ 0.0164; doosra = 1/62 + 1/62 ≈ 0.0323. Doosra jeetega — dono jagah decent hona ek jagah top hone se behtar. RRF consensus ko reward karta hai.)

> **→ Practice A1** (`rrf_fusion.py`) — do ranked lists → RRF merged ranking.

---

### §3. Reranking — two-stage retrieval

Ab §0 ka bi/cross-encoder farak apply karo. **Stage 1 (recall):** hybrid search se bahut saare candidates lao (jaise top-50) — yahan goal recall hai, koi relevant doc chhoote nahi. **Stage 2 (precision):** un 50 ko ek **cross-encoder reranker** se score karke top-5 chuno — yahan goal precision hai. Kyunki reranker sirf 50 pairs pe chalta hai (poore corpus pe nahi), latency manage-able rehti hai.

```
query → hybrid retrieve top-50 (fast, high recall)
      → cross-encoder rerank → top-5 (precise) → LLM
```

Production mein cross-encoder tumhe khud host karne ki zaroorat nahi — Cohere Rerank, or a hosted `bge-reranker`/`ms-marco` cross-encoder use kar sakte ho. Yeh ek API call hai jo `(query, [docs])` leke reranked order deta hai. Impact bada hota hai: two-stage aksar retrieval quality ko dramatically uthata hai kyunki cross-encoder wo nuance pakadta hai jo bi-encoder ka single cosine miss karta hai.

Reranking ke saath ek aur cheez — **MMR** — jab tum final top-k choose karte ho, sirf highest-score nahi, thoda diversity bhi lo taaki 5 chunks alag-alag angle cover karein, ek hi baat 5 baar nahi. MMR har next pick pe "relevance minus similarity-to-already-picked" maximize karta hai.

> **→ Practice A2** (`mmr_rerank.py`) — MMR se relevance + diversity balance karke top-k select karo.

---

### §4. Query transformation — retrieval se pehle query sudharo

User ka raw query aksar retrieval-friendly nahi hota — chhota, ambiguous, ya answer se bahut alag worded. Char techniques (LLM se ek chhota pre-step):

- **Rewriting** — "refund??" → "What is the refund policy and time window?" (clean, complete).
- **HyDE** — LLM se ek *hypothetical ideal answer* likhwaao, phir *uska* embedding search karo. Kyun kaam karta hai? Kyunki ek answer doosre answer (doc) se zyada match karta hai vs ek question answer se — question aur answer ki wording alag hoti hai. HyDE us gap ko paatता hai.
- **Multi-query** — ek query ke 3 paraphrase banाo, teeno se retrieve karo, results union/RRF karo — recall badhta hai.
- **Decomposition** — "Compare refund policy for digital vs physical goods" → do sub-queries, dono retrieve, combine.

Tradeoff: har technique ek extra LLM call (latency + cost) add karti hai, isliye inhe tab use karo jab retrieval quality genuinely bottleneck ho, har query pe nahi.

> **→ Practice A4** (`query_rewrite.py`) — ek query se multi-query variants generate karo (LLM stub; ya offline heuristic version).

---

### §5. Contextual retrieval + chunk enrichment

Ek subtle problem: ek chunk apne aap mein context kho deta hai. "Isme 30 din ki limit hai" — kis cheez mein? Chunk se pata nahi, kyunki "refund" wale heading doosre chunk mein tha. **Contextual retrieval** (Anthropic ne popularize kiya) har chunk ke aage ek chhota context-blurb jodता hai (LLM se generate — "Yeh chunk Acme refund policy ka hai, returns section") *pehle* embed karne se. Isse chunk self-contained ho jaata hai aur retrieval accuracy badhti hai. Sasta version — chunk ke saath uska doc-title/section metadata prepend karo.

Isse related — **metadata filtering**. Embed ke saath structured metadata (doc_id, date, tenant, category) store karo, aur retrieve pe pehle filter karo (`WHERE category='refund' AND date > ...`), phir similarity. Yeh irrelevant docs ko search space se hi hata deta hai — tez aur zyada precise.

---

### §6. Retrieval eval — measure, guess nahi

RAG debug karne ke liye retrieval ko generation se **alag** measure karo (warna pata nahi problem retrieval mein hai ya LLM mein). Ek labeled set banao: query → known relevant doc_id(s). Phir:

- **Recall@k** — kitni queries mein sahi doc top-k mein aaya? (retrieval ki "kuch chhoota to nahi" health)
- **MRR** — sahi doc average kis rank pe? `mean(1/rank_of_first_relevant)`. Rank 1 = 1.0, rank 5 = 0.2. (kitni upar aa raha)

In do numbers se tum objectively compare kar sakte ho: "hybrid + rerank ne recall@5 0.72 se 0.91 kiya" — yahi interview mein defendable improvement hai, "lagta hai better hai" nahi. Isse CI mein daalо (Module 10) taaki koi retrieval change regression na laaye.

> **Ruko, socho:** Tumhara RAG galat jawab de raha hai. Tum kaise pata karoge problem retrieval mein hai ya generation mein? (Jawab: retrieval metrics alag naapo — agar recall@k low hai (sahi chunk aa hi nahi raha), problem retrieval; agar sahi chunk retrieve ho raha par jawab phir bhi galat, problem generation/prompt. Alag measure kiye bina tum andhере mein tune karoge.)

> **→ Practice A3** (`retrieval_metrics.py`) — recall@k + MRR compute karo labeled set pe.

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge.
> A1–A3 offline (pure math/logic) — `python <file>.py` → `_check()` pass.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §2 | `rrf_fusion.py` | `_check()` asserts pass (RRF merge) |
| A2 | §3 | `mmr_rerank.py` | `_check()` asserts pass (relevance + diversity) |
| A3 | §6 | `retrieval_metrics.py` | `_check()` asserts pass (recall@k + MRR) |
| A4 | §4 | `query_rewrite.py` | Multi-query variants (LLM ya heuristic) |

### Setup

```bash
cd modules/13-advanced-retrieval/practice
python3 -m venv .venv && source .venv/bin/activate
pip install numpy    # A2 ke liye (cosine). A4 optional: openai
```

---

## Active recall (khud jawab likho NOTES mein)

1. Two-stage retrieval — dono stage ka goal aur model type?
2. RRF weighted-score-sum se behtar kyun?
3. HyDE kyun kaam karta hai?
4. Retrieval problem vs generation problem — kaise alag karoge?

**Chat drill** (optional): "Module 13 — recall@5 improve karne ke 3 levers whiteboard."

---

## Progress checklist

- [ ] §0 terms clear
- [ ] Theory §1–§6 padha
- [ ] Practice A1–A4 pass
- [ ] Redraw challenge
- [ ] Active recall NOTES mein
- [ ] NOTES session log

---

## Optional appendix

- [Anthropic — Contextual Retrieval](https://www.anthropic.com/news/contextual-retrieval)
- [Cohere Rerank](https://docs.cohere.com/docs/rerank-overview)
- [BGE reranker (Hugging Face)](https://huggingface.co/BAAI/bge-reranker-base)
- Module 05 (RAG basics) · 10 (retrieval eval in CI)
