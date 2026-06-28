# Module 03 — Assignments (ek jagah)

> **Pehle padho**: `../MODULE.md` **§0 Terms** (gateway, BFF, router, tenant, metering) — lifecycle se pehle.  
> **Theory**: `../MODULE.md` · **Ship spec**: `../../Projects.md` Project C (Go)  
> **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md @Projects.md`

**Note:** Yeh learning sandbox hai — final ship Go mein Project C.

Order: §0 → session table follow → M1 → M7. `TODO` search in each file.

---

## Progress checklist

- [ ] M1 — `gateway_skeleton.py`
- [ ] M2 — `fallback_router.py`
- [ ] M3 — `complexity_router.py`
- [ ] M4 — `semantic_cache.py`
- [ ] M5 — `budget_middleware.py`
- [ ] M6 — `tracing_stub.py`
- [ ] M7 — `stream_passthrough.py`
- [ ] Interview prep bullets → NOTES
- [ ] Active recall → NOTES

---

## Setup

```bash
cd modules/03-project-llm-gateway/practice
python3 -m venv .venv && source .venv/bin/activate
pip install fastapi uvicorn httpx redis python-dotenv openai
# M6 optional: opentelemetry packages
```

00a Redis + Postgres recommended running.

---

## M1 — Gateway skeleton

| | |
|---|---|
| **File** | `gateway_skeleton.py` |
| **Kya** | Health + single provider passthrough |
| **Pass** | `curl` works |

---

## M2 — Fallback router

| | |
|---|---|
| **File** | `fallback_router.py` |
| **Kya** | Primary fail → secondary provider |
| **Pass** | Simulated 5xx → secondary OK |

---

## M3 — Complexity router

| | |
|---|---|
| **File** | `complexity_router.py` |
| **Kya** | 3-bucket classifier (Haiku/Sonnet/Opus style) |
| **Pass** | Test set routes correctly |

### Hints

- Start rule-based: `len(query) < 50` → small model bucket

---

## M4 — Semantic cache

| | |
|---|---|
| **File** | `semantic_cache.py` |
| **Kya** | Near-duplicate prompt → cache hit |
| **Pass** | LLM skip on similar prompt |

---

## M5 — Budget middleware

| | |
|---|---|
| **File** | `budget_middleware.py` |
| **Kya** | Over budget → 402/429 |
| **Pass** | Hard stop works |

---

## M6 — Tracing stub

| | |
|---|---|
| **File** | `tracing_stub.py` |
| **Kya** | Span with cost fields |
| **Pass** | Trace visible locally |

---

## M7 — Stream passthrough

| | |
|---|---|
| **File** | `stream_passthrough.py` |
| **Kya** | SSE end-to-end |
| **Pass** | `curl -N` token stream |

---

## NOTES extras (interview prep)

- "40% cost cut" — cache hit % + model mix before/after
- Cache invalidation strategy
- Per-tenant key rotation

---

## Active recall (NOTES)

1. Gateway router ↔ matching engine price tiers parallel?
2. Per-tenant cache scoping kyun mandatory?
3. "40% cost cut" kaise measure/defend?

---

## Files

| File | Milestone |
|------|-----------|
| `gateway_skeleton.py` | M1 |
| `fallback_router.py` | M2 |
| `complexity_router.py` | M3 |
| `semantic_cache.py` | M4 |
| `budget_middleware.py` | M5 |
| `tracing_stub.py` | M6 |
| `stream_passthrough.py` | M7 |

**Stuck?** `@modules/03-project-llm-gateway/MODULE.md` + error paste.
