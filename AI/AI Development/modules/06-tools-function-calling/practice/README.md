# Module 06 — Assignments (ek jagah)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`

Order: A1 → A3. `TODO` search in each file.

---

## Progress checklist

- [ ] A1 — `tool_schemas.py`
- [ ] A2 — `pydantic_tools.py`
- [ ] A3 — `multi_step_loop.py`
- [ ] Active recall → NOTES
- [ ] Redraw challenge

---

## Setup

```bash
cd modules/06-tools-function-calling/practice
python3 -m venv .venv && source .venv/bin/activate
pip install openai pydantic python-dotenv httpx
cp .env.example .env 2>/dev/null || true
```

---

## A1 — Tool schemas

| | |
|---|---|
| **File** | `tool_schemas.py` |
| **Kya** | 2 tools: `search_docs` + `get_weather` |
| **Pass** | LLM picks correct tool 10/10 |

---

## A2 — Pydantic validation

| | |
|---|---|
| **File** | `pydantic_tools.py` |
| **Kya** | Pydantic-validated tool args |
| **Pass** | Invalid args rejected pre-execute |

---

## A3 — Multi-step loop

| | |
|---|---|
| **File** | `multi_step_loop.py` |
| **Kya** | 2-tool chain stub |
| **Pass** | Query needing 2 tools completes |

---

## Active recall (NOTES)

1. Tool description quality output pe kyun matter?
2. Tool call fail — LLM ko kya message?
3. Structured output vs tool calling — kab alag?

---

## Files

| File | Assignment |
|------|------------|
| `tool_schemas.py` | A1 |
| `pydantic_tools.py` | A2 |
| `multi_step_loop.py` | A3 |

**Stuck?** `@modules/06-tools-function-calling/MODULE.md` + error paste.
