# Module 07 — Assignments (ek jagah)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`

Order: A1 → A3. `TODO` search in each file.

---

## Progress checklist

- [ ] A1 — `two_node_graph.py`
- [ ] A2 — `tool_agent_graph.py`
- [ ] A3 — `checkpoint_resume.py`
- [ ] Active recall → NOTES
- [ ] Redraw challenge

---

## Setup

```bash
cd modules/07-agents-langgraph/practice
python3 -m venv .venv && source .venv/bin/activate
pip install langgraph langchain-openai pydantic python-dotenv
```

---

## A1 — Two-node graph

| | |
|---|---|
| **File** | `two_node_graph.py` |
| **Kya** | classify → respond routing graph |
| **Pass** | 10/10 test inputs route correctly |

### Instructions

1. State TypedDict define karo
2. classify node: `billing` | `general`
3. respond node: route-specific prompt
4. `StateGraph` compile + test

---

## A2 — Tool agent graph

| | |
|---|---|
| **File** | `tool_agent_graph.py` |
| **Kya** | Tool-calling agent loop |
| **Pass** | Multi-step task completes |

### Instructions

- agent + tools node loop
- `max_iterations` guard

---

## A3 — Checkpoint resume

| | |
|---|---|
| **File** | `checkpoint_resume.py` |
| **Kya** | Kill mid-run → resume from checkpoint |
| **Pass** | Same `thread_id` se state continues |

### Hints

- `MemorySaver` or sqlite checkpointer
- Slow middle node for kill test

---

## Active recall (NOTES)

1. Infinite loop kaise rokoge production mein?
2. Checkpoint storage — memory vs Postgres?
3. Single agent vs graph — kab graph zaroori?

---

## Files

| File | Assignment |
|------|------------|
| `two_node_graph.py` | A1 |
| `tool_agent_graph.py` | A2 |
| `checkpoint_resume.py` | A3 |

**Stuck?** `@modules/07-agents-langgraph/MODULE.md` + error paste.
