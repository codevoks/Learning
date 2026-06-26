# Practice — Module 00c

1. Read theory in `../MODULE.md`
2. Complete TODOs in `app/`
3. Run with uvicorn

## Setup

```bash
cd modules/00c-fastapi/practice
python3 -m venv .venv
source .venv/bin/activate
pip install fastapi uvicorn httpx
```

## Run

```bash
uvicorn app.main:app --reload --port 8000
```

Open http://localhost:8000/docs

## Assignments

| File | Task |
|------|------|
| `app/main.py` | Wire app, routers, middleware |
| `app/models.py` | Pydantic echo models (A1) |
| `app/routes/health.py` | Health router (A2) |
| `app/routes/chat.py` | Chat POST echo (A1/A2) |
| `app/middleware.py` | X-Request-ID (A3) |
| `app/deps.py` | API key auth (A4) |
| `app/routes/events.py` | SSE stub (A5) |

## Quick tests

```bash
curl http://localhost:8000/health
curl -X POST http://localhost:8000/chat -H "Content-Type: application/json" \
  -H "X-API-Key: dev-secret" -d '{"message":"hi"}'
curl -i http://localhost:8000/chat   # should 401 without key
curl -N http://localhost:8000/events
```
