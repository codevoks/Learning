# Module 00b — Assignments (ek jagah)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`

Order: A1 → A4. Har file mein `# TODO` search karo.

---

## Progress checklist

- [ ] A1 — `chat_models.py`
- [ ] A2 — `parallel_fetch.py`
- [ ] A3 — `broken_async.py` + NOTES explanation
- [ ] A4 — Zod vs Pydantic in `../NOTES.md`
- [ ] Active recall → `../NOTES.md`
- [ ] Redraw challenge

---

## Setup

```bash
cd modules/00b-python-async/practice
python3 -m venv .venv
source .venv/bin/activate
pip install pydantic httpx
```

*(Ya 00a ka venv reuse — same deps add karo.)*

---

## A1 — Pydantic models

| | |
|---|---|
| **File** | `chat_models.py` |
| **Kya** | `ChatRequest` + `ChatResponse` TODOs complete |
| **Pass** | Invalid input → `ValidationError` |

### Instructions

1. `TODO` search → models complete karo
2. `python chat_models.py`

### Hints

- `Field(min_length=1)` message ke liye
- `tokens_used: int` response mein required

---

## A2 — Parallel fetch

| | |
|---|---|
| **File** | `parallel_fetch.py` |
| **Kya** | 3 URLs parallel `asyncio.gather` |
| **Pass** | Total time ≈ slowest URL, sum nahi |

### Instructions

1. TODOs complete
2. `python parallel_fetch.py` — timing dekho

### Hints

- Test URLs: `https://httpbin.org/delay/1` (3 alag paths)
- `time.perf_counter()` before/after

---

## A3 — Fix broken async

| | |
|---|---|
| **File** | `broken_async.py` |
| **Kya** | Sync blocking fix karo |
| **Pass** | Script chale + bug/fix `../NOTES.md` mein likho |

### Hints

- `time.sleep` → `asyncio.sleep`
- `requests` → `httpx.AsyncClient`

---

## A4 — Zod mapping (written)

| | |
|---|---|
| **File** | `../NOTES.md` |
| **Kya** | Ek schema — Zod + Pydantic side-by-side |
| **Pass** | Self-check / coach |

---

## Active recall (`../NOTES.md`)

1. `async def` ke andar sync blocking production mein kyun dangerous?
2. Pydantic vs dataclass — kab Pydantic?
3. LLM API call async kyun honi chahiye?

---

## Files

| File | Assignment |
|------|------------|
| `chat_models.py` | A1 |
| `parallel_fetch.py` | A2 |
| `broken_async.py` | A3 |

**Stuck?** `@modules/00b-python-async/MODULE.md` + error paste.
