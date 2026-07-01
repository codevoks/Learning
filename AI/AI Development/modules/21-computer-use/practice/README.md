# Module 21 — Assignments (Computer Use & Browser Agents)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`
> A1–A3 offline — `python <file>.py` → `_check()` pass.

## Progress checklist

- [ ] A1 — `action_schema.py`
- [ ] A2 — `grounding.py`
- [ ] A3 — `safety_gate.py`
- [ ] Active recall → NOTES

## Setup

```bash
cd modules/21-computer-use/practice
python3 -m venv .venv && source .venv/bin/activate
# A1-A3 sirf stdlib. Real browser agent: pip install playwright (ya Claude-in-Chrome)
```

---

## A1 — Action schema

| | |
|---|---|
| **Theory §** | §3 |
| **File** | `action_schema.py` |
| **Kya** | Action validate (allowlist) |
| **Pass** | `python action_schema.py` → `_check()` asserts pass |

## A2 — Grounding

| | |
|---|---|
| **Theory §** | §3 |
| **File** | `grounding.py` |
| **Kya** | Bbox center + point-inside |
| **Pass** | `python grounding.py` → `_check()` asserts pass |

## A3 — Safety gate

| | |
|---|---|
| **Theory §** | §5 |
| **File** | `safety_gate.py` |
| **Kya** | Destructive → HITL flag |
| **Pass** | `python safety_gate.py` → `_check()` asserts pass |

---

## Active recall (NOTES)

1. Perception-action loop 3 steps?
2. Grounding kyun #1 challenge?
3. Indirect injection computer-use mein zyada khatarnak kyun?

**Stuck?** `@modules/21-computer-use/MODULE.md` + error paste.
