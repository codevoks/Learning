# Module 13 — Assignments (Advanced Retrieval & Reranking)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`
> Code files mein `TODO` search karo. A1–A4 offline — `python <file>.py` → `_check()` pass.

## Progress checklist

- [ ] A1 — `rrf_fusion.py`
- [ ] A2 — `mmr_rerank.py`
- [ ] A3 — `retrieval_metrics.py`
- [ ] A4 — `query_rewrite.py`
- [ ] Active recall → NOTES

## Setup

```bash
cd modules/13-advanced-retrieval/practice
python3 -m venv .venv && source .venv/bin/activate
pip install numpy    # A2 (cosine). A4 optional: openai python-dotenv
```

---

## A1 — RRF fusion

| | |
|---|---|
| **Theory §** | §2 |
| **File** | `rrf_fusion.py` |
| **Kya** | Kai ranked lists → ek merged ranking (scale-free) |
| **Pass** | `python rrf_fusion.py` → `_check()` asserts pass |

## A2 — MMR rerank

| | |
|---|---|
| **Theory §** | §3 |
| **File** | `mmr_rerank.py` |
| **Kya** | Relevance + diversity balance karke top-k |
| **Pass** | `python mmr_rerank.py` → `_check()` asserts pass |

## A3 — Retrieval metrics

| | |
|---|---|
| **Theory §** | §6 |
| **File** | `retrieval_metrics.py` |
| **Kya** | recall@k + MRR |
| **Pass** | `python retrieval_metrics.py` → `_check()` asserts pass |

## A4 — Multi-query rewrite

| | |
|---|---|
| **Theory §** | §4 |
| **File** | `query_rewrite.py` |
| **Kya** | Ek query → n variants (LLM ya heuristic) |
| **Pass** | `python query_rewrite.py` → `_check()` structure asserts pass |

---

## Active recall (NOTES)

1. Two-stage retrieval — dono stage ka goal + model type?
2. RRF weighted-score-sum se behtar kyun?
3. Retrieval vs generation problem — kaise alag karoge?

**Stuck?** `@modules/13-advanced-retrieval/MODULE.md` + error paste.
