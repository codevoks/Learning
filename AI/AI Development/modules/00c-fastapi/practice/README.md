# Module 00c — Assignments (ek jagah)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`

Order: A1 → A6. `app/` folder mein `TODO` search karo.

---

## Progress checklist

- [ ] A1 — models + chat echo
- [ ] A2 — routers split
- [ ] A3 — middleware `X-Request-ID`
- [ ] A4 — API key auth
- [ ] A5 — SSE stub
- [ ] A6 — Express vs FastAPI table in NOTES
- [ ] Active recall → NOTES

---

## Setup & run

```bash
cd modules/00c-fastapi/practice
python3 -m venv .venv && source .venv/bin/activate
pip install fastapi uvicorn httpx
uvicorn app.main:app --reload --port 8000
```

Open http://localhost:8000/docs

---

## A1 — Pydantic echo

| | |
|---|---|
| **Files** | `app/main.py`, `app/models.py`, `app/routes/chat.py` |
| **Kya** | POST echo with Pydantic validation |
| **Pass** | Valid JSON → validated response |

---

## A2 — Routers

| | |
|---|---|
| **Files** | `app/routes/health.py`, `app/routes/chat.py`, `app/main.py` |
| **Kya** | Health + chat routers wire karo |
| **Pass** | `/docs` pe dono endpoints dikhen |

---

## A3 — Request ID middleware

| | |
|---|---|
| **File** | `app/middleware.py` |
| **Kya** | Har response pe `X-Request-ID` (UUID) |
| **Pass** | `curl -i` mein header dikhe |

---

## A4 — API key auth

| | |
|---|---|
| **File** | `app/deps.py` |
| **Kya** | Missing `X-API-Key` → 401 |
| **Pass** | Key ke bina chat fail |

### Hints

- Header: `X-API-Key`
- Dev secret: `dev-secret` (practice only)

### Quick tests

```bash
curl http://localhost:8000/health
curl -X POST http://localhost:8000/chat -H "Content-Type: application/json" \
  -H "X-API-Key: dev-secret" -d '{"message":"hi"}'
curl -i http://localhost:8000/chat   # 401 without key
```

---

## A5 — SSE stub

| | |
|---|---|
| **File** | `app/routes/events.py` |
| **Kya** | Timer ticks via Server-Sent Events |
| **Pass** | `curl -N http://localhost:8000/events` streams |

### Hints

- `media_type="text/event-stream"`
- Each event: `f"data: {payload}\n\n"`

---

## A6 — Written (NOTES)

| | |
|---|---|
| **File** | `../NOTES.md` |
| **Kya** | Express vs FastAPI — 5 row table |
| **Pass** | Self-check / coach |

---

## Active recall (NOTES)

1. FastAPI DI production mein kya solve karta hai?
2. Middleware vs Depends — kab kya?
3. SSE streaming ka content-type?

---

## Files map

| File | Task |
|------|------|
| `app/main.py` | Wire app, routers, middleware |
| `app/models.py` | Pydantic models (A1) |
| `app/routes/health.py` | Health router (A2) |
| `app/routes/chat.py` | Chat POST (A1/A2) |
| `app/middleware.py` | X-Request-ID (A3) |
| `app/deps.py` | API key (A4) |
| `app/routes/events.py` | SSE (A5) |

**Stuck?** `@modules/00c-fastapi/MODULE.md` + error paste.
