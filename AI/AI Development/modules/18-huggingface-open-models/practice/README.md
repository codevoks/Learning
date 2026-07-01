# Module 18 — Assignments (HuggingFace & Open Models)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`
> A1 offline — `python mini_tokenizer.py` → `_check()` pass. A2 model-dependent.

## Progress checklist

- [ ] A1 — `mini_tokenizer.py`
- [ ] A2 — `pipeline_run.py`
- [ ] A3 — `MODEL_CHOICE.md`
- [ ] Active recall → NOTES

## Setup

```bash
cd modules/18-huggingface-open-models/practice
python3 -m venv .venv && source .venv/bin/activate
# A1 sirf stdlib. A2: pip install transformers torch (ya Ollama install)
```

---

## A1 — Mini tokenizer

| | |
|---|---|
| **Theory §** | §4 |
| **File** | `mini_tokenizer.py` |
| **Kya** | encode/decode + special tokens |
| **Pass** | `python mini_tokenizer.py` → `_check()` asserts pass |

## A2 — Run open model

| | |
|---|---|
| **Theory §** | §3, §5 |
| **File** | `pipeline_run.py` |
| **Kya** | HF pipeline / AutoModel / Ollama se generate |
| **Pass** | Chhote open model se text generate ho |

## A3 — Model choice (written)

| | |
|---|---|
| **Theory §** | §6 |
| **File** | `MODEL_CHOICE.md` |
| **Kya** | 4 scenarios: open/API/hybrid |
| **Pass** | Self / coach review |

---

## Active recall (NOTES)

1. pipeline vs AutoModel — kab kaunsa?
2. Model + tokenizer match kyun?
3. Open vs API — 2-2 factors?

**Stuck?** `@modules/18-huggingface-open-models/MODULE.md` + error paste.
