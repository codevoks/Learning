# Module 02 — Assignments (ek jagah)

> **Pehle padho**: `../MODULE.md` **§0 Terms** (rate limit, cache, circuit breaker, fallback) — diagrams se pehle.  
> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`

**Prereq:** Module 00a Redis running (`docker compose up -d` in `00a/practice`).

Order: §0 → session table follow → A1 → A4. `TODO` search in each file.

---

## Progress checklist

- [ ] A1 — `rate_limiter.py`
- [ ] A2 — `exact_cache.py`
- [ ] A3 — `circuit_breaker.py`
- [ ] A4 — `request_middleware.py`
- [ ] Active recall → NOTES
- [ ] Redraw challenge

---

## Setup

```bash
cd modules/02-llm-infra/practice
python3 -m venv .venv && source .venv/bin/activate
pip install redis httpx fastapi uvicorn python-dotenv
```

Redis: `redis://localhost:6379` (00a compose)

---

## A1 — Rate limiter

| | |
|---|---|
| **File** | `rate_limiter.py` |
| **Kya** | Redis token bucket |
| **Pass** | N requests ke baad 429 |

### Hints

- Key pattern: `rl:{identifier}:{window}`

---

## A2 — Exact cache

| | |
|---|---|
| **File** | `exact_cache.py` |
| **Kya** | Same prompt → cache hit, skip LLM |
| **Pass** | Duplicate prompt cached response deta hai |

---

## A3 — Circuit breaker

| | |
|---|---|
| **File** | `circuit_breaker.py` |
| **Kya** | Breaker wrapper around flaky call |
| **Pass** | 3 fails → open; half-open retry |

### Hints

- In-memory OK for learning — prod mein Redis shared state

---

## A4 — Request middleware

| | |
|---|---|
| **File** | `request_middleware.py` |
| **Kya** | `trace_id` + token counters |
| **Pass** | Structured JSON logs |

---

## Active recall (NOTES)

1. Semantic cache false positive ka production impact?
2. Circuit breaker half-open kyun?
3. Rate limit user-level vs IP-level — kab kya?

---

## Files

| File | Assignment |
|------|------------|
| `rate_limiter.py` | A1 |
| `exact_cache.py` | A2 |
| `circuit_breaker.py` | A3 |
| `request_middleware.py` | A4 |

**Stuck?** `@modules/02-llm-infra/MODULE.md` + error paste.
