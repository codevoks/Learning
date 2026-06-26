# Module 01 — Assignments (ek jagah)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`

Order: A1 → A4. Har file mein `TODO` search karo.

---

## Progress checklist

- [ ] A1 — `chat_route.py`
- [ ] A2 — `stream_route.py`
- [ ] A3 — `cost_calculator.py`
- [ ] A4 — `context_trimmer.py`
- [ ] Active recall → NOTES
- [ ] Redraw challenge

---

## Setup

```bash
cd modules/01-llm-apis/practice
python3 -m venv .venv && source .venv/bin/activate
pip install fastapi uvicorn httpx python-dotenv openai
cp .env.example .env   # API key add karo
```

---

## A1 — Non-streaming chat

| | |
|---|---|
| **File** | `chat_route.py` |
| **Kya** | Completion route + token usage log |
| **Pass** | JSON response + `prompt_tokens` / `completion_tokens` logged |

### Run

```bash
uvicorn chat_route:app --reload
curl -X POST http://localhost:8000/chat -H "Content-Type: application/json" \
  -d '{"message":"Hello"}'
```

### Hints

- `httpx` ya official SDK — `usage` field response mein
- Log structured JSON mein

---

## A2 — SSE streaming

| | |
|---|---|
| **File** | `stream_route.py` |
| **Kya** | Streaming endpoint |
| **Pass** | Client ko incremental tokens milen |

### Run

```bash
curl -N http://localhost:8000/chat/stream -H "Content-Type: application/json" \
  -d '{"message":"Count to 5"}'
```

---

## A3 — Cost calculator

| | |
|---|---|
| **File** | `cost_calculator.py` |
| **Kya** | Model + tokens → USD |
| **Pass** | ±1% of provider pricing page |

### Run

```bash
python cost_calculator.py
```

### Hints

- Pricing dict per model — hardcode from provider page, comment date

---

## A4 — Context trimmer

| | |
|---|---|
| **File** | `context_trimmer.py` |
| **Kya** | Long history truncate strategy |
| **Pass** | Works + strategy NOTES ya docstring mein |

### Run

```bash
python context_trimmer.py
```

---

## Active recall (NOTES)

1. Input vs output token pricing alag kyun?
2. Streaming mein client disconnect — provider cost?
3. System prompt user message se alag kyun?

---

## Files

| File | Assignment |
|------|------------|
| `chat_route.py` | A1 |
| `stream_route.py` | A2 |
| `cost_calculator.py` | A3 |
| `context_trimmer.py` | A4 |
| `.env.example` | copy → `.env` |

**Stuck?** `@modules/01-llm-apis/MODULE.md` + error paste.
