# Module 12 — Assignments (Guardrails & AI Safety)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`
> Code files mein `TODO` search karo. A1–A3 offline — `python <file>.py` chala ke `_check()` pass karao.

## Progress checklist

- [ ] A1 — `pii_redactor.py`
- [ ] A2 — `injection_detector.py`
- [ ] A3 — `output_validator.py`
- [ ] A4 — `RED_TEAM.md`
- [ ] Active recall → NOTES

## Setup

```bash
cd modules/12-guardrails-safety/practice
python3 -m venv .venv && source .venv/bin/activate
# A1–A3 sirf stdlib (re). Production: presidio, moderation API.
```

---

## A1 — PII redactor (input guardrail)

| | |
|---|---|
| **Theory §** | §2 |
| **File** | `pii_redactor.py` |
| **Kya** | Card / email / phone → placeholders |
| **Pass** | `python pii_redactor.py` → `_check()` asserts pass |

## A2 — Injection detector (input guardrail)

| | |
|---|---|
| **Theory §** | §4 |
| **File** | `injection_detector.py` |
| **Kya** | Jailbreak patterns detect (heuristic layer) |
| **Pass** | `python injection_detector.py` → `_check()` asserts pass (attacks caught, legit passed) |

## A3 — Output validator (output guardrail)

| | |
|---|---|
| **Theory §** | §3 |
| **File** | `output_validator.py` |
| **Kya** | PII leak + banned-content check |
| **Pass** | `python output_validator.py` → `_check()` asserts pass |

## A4 — Red-team (written)

| | |
|---|---|
| **Theory §** | §6 |
| **File** | `RED_TEAM.md` |
| **Kya** | 8 attack cases + defending layer each |
| **Pass** | Coach / self review |

---

## Active recall (NOTES)

1. Input vs output guardrails — 2-2 examples?
2. Injection defense-in-depth — 4 layers?
3. OWASP LLM Top-10 — 3 risks + mitigation?

**Stuck?** `@modules/12-guardrails-safety/MODULE.md` + error paste.
