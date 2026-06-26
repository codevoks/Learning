# Module 11 — Assignments (ek jagah)

> **Theory**: `../MODULE.md` · **Ship spec**: `../../Projects.md` Project B  
> **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md @Projects.md`

**Note:** Learning sandbox — final ship main codebase mein Project B.

Order: M1 → M7. `TODO` search in each file.

---

## Progress checklist

- [ ] M1 — `nl_to_workflow.py`
- [ ] M2 — `linear_workflow_graph.py`
- [ ] M3 — `mcp_tools_wire.py`
- [ ] M4 — `hitl_destructive.py`
- [ ] M5 — `outbox_stub.py`
- [ ] M6 — `eval_harness.py`
- [ ] M7 — `demo_refund/`
- [ ] Active recall + architecture → NOTES

---

## Setup

```bash
cd modules/11-project-agentic-workflow/practice
python3 -m venv .venv && source .venv/bin/activate
pip install langgraph pydantic fastapi python-dotenv httpx
```

Prior modules: 06–10 concepts used here.

---

## M1 — NL → workflow JSON

| | |
|---|---|
| **File** | `nl_to_workflow.py` |
| **Kya** | Natural language → structured `WorkflowPlan` |
| **Pass** | 90%+ valid on test phrases |

---

## M2 — Linear workflow graph

| | |
|---|---|
| **File** | `linear_workflow_graph.py` |
| **Kya** | LangGraph 3-step linear execution |
| **Pass** | E2E test completes |

---

## M3 — MCP + custom tools

| | |
|---|---|
| **File** | `mcp_tools_wire.py` |
| **Kya** | MCP + Python tools same agent mein |
| **Pass** | External + DB tools work |

---

## M4 — HITL destructive steps

| | |
|---|---|
| **File** | `hitl_destructive.py` |
| **Kya** | Pause/approve on destructive steps |
| **Pass** | Reject triggers replan |

---

## M5 — Outbox idempotency

| | |
|---|---|
| **File** | `outbox_stub.py` |
| **Kya** | Idempotent execution via outbox pattern |
| **Pass** | Duplicate enqueue → single side effect |

---

## M6 — Eval harness

| | |
|---|---|
| **File** | `eval_harness.py` |
| **Kya** | Trajectory regression for workflow plans |
| **Pass** | Bad plan fails (CI-ready exit code) |

---

## M7 — Refund demo

| | |
|---|---|
| **Folder** | `demo_refund/` |
| **Kya** | End-to-end refund workflow — recordable demo |
| **Pass** | README + runnable walkthrough |

---

## Active recall (NOTES)

1. Outbox exactly-once ↔ billing guarantee link?
2. HITL on destructive steps kyun mandatory?
3. CV narrative — 3 defendable bullets?

---

## Files

| File | Milestone |
|------|-----------|
| `nl_to_workflow.py` | M1 |
| `linear_workflow_graph.py` | M2 |
| `mcp_tools_wire.py` | M3 |
| `hitl_destructive.py` | M4 |
| `outbox_stub.py` | M5 |
| `eval_harness.py` | M6 |
| `demo_refund/README.md` | M7 |

**Stuck?** `@modules/11-project-agentic-workflow/MODULE.md` + error paste.
