# Module 14 — Assignments (Fine-tuning & Model Customization)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`
> Code files mein `TODO` search karo. A1, A3 offline — `python <file>.py` → `_check()` pass.

## Progress checklist

- [ ] A1 — `build_sft_dataset.py`
- [ ] A2 — `DECISION.md`
- [ ] A3 — `dataset_quality.py`
- [ ] Active recall → NOTES

## Setup

```bash
cd modules/14-finetuning/practice
python3 -m venv .venv && source .venv/bin/activate
# A1, A3 sirf stdlib. Actual fine-tuning: OpenAI/Together/HF PEFT (awareness).
```

---

## A1 — Build SFT dataset

| | |
|---|---|
| **Theory §** | §2 |
| **File** | `build_sft_dataset.py` |
| **Kya** | Raw pairs → chat JSONL + validate |
| **Pass** | `python build_sft_dataset.py` → `_check()` asserts pass |

## A2 — Decision doc (written)

| | |
|---|---|
| **Theory §** | §1 |
| **File** | `DECISION.md` |
| **Kya** | 5 scenarios: prompt/RAG/finetune + reason |
| **Pass** | Coach / self review |

## A3 — Dataset quality

| | |
|---|---|
| **Theory §** | §5 |
| **File** | `dataset_quality.py` |
| **Kya** | Dedup + clean + no-leak deterministic split |
| **Pass** | `python dataset_quality.py` → `_check()` asserts pass |

---

## Active recall (NOTES)

1. Prompt vs RAG vs fine-tune — framework?
2. Fine-tune changing facts ke liye kyun galat?
3. Train/holdout leak se eval kyun jhootha?

**Stuck?** `@modules/14-finetuning/MODULE.md` + error paste.
