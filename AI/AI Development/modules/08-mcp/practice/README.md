# Module 08 — Assignments (ek jagah)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`

Order: A1 → A3. `TODO` search in code files.

---

## Progress checklist

- [ ] A1 — `mcp_server.py`
- [ ] A2 — `agent_mcp_wire.py`
- [ ] A3 — `THREAT_MODEL.md`
- [ ] Active recall → NOTES
- [ ] Redraw challenge

---

## Setup

```bash
cd modules/08-mcp/practice
python3 -m venv .venv && source .venv/bin/activate
pip install mcp pydantic langgraph python-dotenv
```

---

## A1 — MCP server

| | |
|---|---|
| **File** | `mcp_server.py` |
| **Kya** | Minimal server: `read_db` + `write_webhook` stubs |
| **Pass** | Client discovers + invokes both tools |

### Instructions

- MCP Python SDK — 2 tools define
- `read_db(query)` — stub rows return
- `write_webhook(url, payload)` — stub log only
- stdio transport

---

## A2 — Agent wire

| | |
|---|---|
| **File** | `agent_mcp_wire.py` |
| **Kya** | MCP tools into LangGraph agent |
| **Pass** | Agent completes task via external MCP tool |

### Instructions

- Connect to `mcp_server.py`
- `list_tools` → LLM
- `call_tool` on model request

---

## A3 — Threat model (written)

| | |
|---|---|
| **File** | `THREAT_MODEL.md` |
| **Kya** | 5 risks + mitigations |
| **Pass** | Review complete |

---

## Active recall (NOTES)

1. MCP vs hardcoded Python functions — kab MCP?
2. MCP server crash — agent behavior?
3. Multiple servers — tool name collision?

---

## Files

| File | Assignment |
|------|------------|
| `mcp_server.py` | A1 |
| `agent_mcp_wire.py` | A2 |
| `THREAT_MODEL.md` | A3 |

**Stuck?** `@modules/08-mcp/MODULE.md` + error paste.
