# Module 10 — Assignments (ek jagah)

> **Textbook**: `../MODULE.md` — §0 eval/LLMOps terms pehle. Golden recon CSV parallel socho.  
> **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`  
> **Standard**: `@MODULE-TEACHING-STANDARD.md`

| Assignment | Theory § padhne ke baad |
|------------|---------------------------|
| A1 | §0–§2 — golden dataset (10 cases + trajectory fields) |
| A2 | §2–§4 — trajectory scorer + report |
| A3 | §5 — CI regression script (`exit 1` on drop) |

Order: A1 → A3.

---

## Progress checklist

- [ ] A1 — `golden_dataset.json`
- [ ] A2 — `trajectory_scorer.py`
- [ ] A3 — `ci_eval.sh`
- [ ] Active recall → NOTES
- [ ] Redraw challenge

---

## Setup

```bash
cd modules/10-evals-llmops/practice
python3 -m venv .venv && source .venv/bin/activate
pip install pydantic python-dotenv
# optional: deepeval, langfuse
```

---

## A1 — Golden dataset

| | |
|---|---|
| **File** | `golden_dataset.json` |
| **Kya** | 10 golden Q&A pairs (replace TODOs) |
| **Pass** | Valid JSON committed |

### Format hint

Each entry: `input`, `expected_output`, optional `expected_steps` for trajectory eval.

---

## A2 — Trajectory scorer

| | |
|---|---|
| **File** | `trajectory_scorer.py` |
| **Kya** | Compare expected vs actual steps |
| **Pass** | Pass/fail report printed |

### Run

```bash
python trajectory_scorer.py
```

---

## A3 — CI eval script

| | |
|---|---|
| **File** | `ci_eval.sh` |
| **Kya** | Fail if pass rate drops below baseline |
| **Pass** | `bash ci_eval.sh` exits 1 on regression |

### Instructions

- `BASELINE_PASS_RATE` + threshold delta
- Run scorer on golden dataset
- `exit 1` if below threshold

---

## Active recall (NOTES)

1. LLM-as-judge bias?
2. Eval dataset vs production PII?
3. Online vs offline evals — kab kya?

---

## Files

| File | Assignment |
|------|------------|
| `golden_dataset.json` | A1 |
| `trajectory_scorer.py` | A2 |
| `ci_eval.sh` | A3 |

**Stuck?** `@modules/10-evals-llmops/MODULE.md` + error paste.
