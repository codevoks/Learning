# Module 09 — Assignments (ek jagah)

> **Textbook**: `../MODULE.md` — §0 multi-agent + HITL terms pehle. Zapier/outbox parallel socho.  
> **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`  
> **Standard**: `@MODULE-TEACHING-STANDARD.md`

| Assignment | Theory § padhne ke baad |
|------------|---------------------------|
| A1 | §1–§3 — supervisor → specialist routing |
| A2 | §4 — `interrupt_before`, approve/reject |
| A3 | §5 — audit trail by `run_id` |

Order: A1 → A3. Har file mein `TODO` search karo.

---

## Progress checklist

- [ ] A1 — `supervisor_router.py`
- [ ] A2 — `hitl_gate.py`
- [ ] A3 — `audit_log.py`
- [ ] Active recall → NOTES
- [ ] Redraw challenge

---

## Setup

```bash
cd modules/09-multi-agent-hitl/practice
python3 -m venv .venv && source .venv/bin/activate
pip install langgraph pydantic python-dotenv
```

---

## A1 — Supervisor router

| | |
|---|---|
| **File** | `supervisor_router.py` |
| **Kya** | Route tasks to 2 specialist stubs |
| **Pass** | 8/10 tasks correct routing |

---

## A2 — HITL gate

| | |
|---|---|
| **File** | `hitl_gate.py` |
| **Kya** | Pause before irreversible action |
| **Pass** | Reject → rollback / replan path |

### Instructions

- `interrupt_before` destructive node
- `approve()` / `reject()` resume API

---

## A3 — Audit log

| | |
|---|---|
| **File** | `audit_log.py` |
| **Kya** | Log each agent step |
| **Pass** | Queryable decision trail by `run_id` |

---

## Active recall (NOTES)

1. HITL sync vs async — product impact?
2. Critic agent kab worth it?
3. Multi-agent cost control strategies?

---

## Files

| File | Assignment |
|------|------------|
| `supervisor_router.py` | A1 |
| `hitl_gate.py` | A2 |
| `audit_log.py` | A3 |

**Stuck?** `@modules/09-multi-agent-hitl/MODULE.md` + error paste.
