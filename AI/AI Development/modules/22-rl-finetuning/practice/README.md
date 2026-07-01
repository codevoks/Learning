# Module 22 — Assignments (RL Fine-tuning)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`
> A1, A2 offline — `python <file>.py` → `_check()` pass. A3 written.

## Progress checklist

- [ ] A1 — `preference_dataset.py`
- [ ] A2 — `reward_eval.py`
- [ ] A3 — `DECISION.md`
- [ ] Active recall → NOTES

## Setup

```bash
cd modules/22-rl-finetuning/practice
python3 -m venv .venv && source .venv/bin/activate
# A1, A2 sirf stdlib. Actual RL: TRL (HuggingFace) — awareness.
```

---

## A1 — Preference dataset

| | |
|---|---|
| **Theory §** | §3 |
| **File** | `preference_dataset.py` |
| **Kya** | Ranked outputs → (chosen, rejected) pairs |
| **Pass** | `python preference_dataset.py` → `_check()` asserts pass |

## A2 — Reward eval

| | |
|---|---|
| **Theory §** | §3, §6 |
| **File** | `reward_eval.py` |
| **Kya** | Pairwise accuracy |
| **Pass** | `python reward_eval.py` → `_check()` asserts pass |

## A3 — Decision (written)

| | |
|---|---|
| **Theory §** | §4 |
| **File** | `DECISION.md` |
| **Kya** | 4 scenarios: SFT/DPO/GRPO/none |
| **Pass** | Self / coach review |

---

## Active recall (NOTES)

1. SFT vs RL — kya alag sikhate?
2. RLHF 3 stages?
3. Reward hacking + 2 defenses?

**Stuck?** `@modules/22-rl-finetuning/MODULE.md` + error paste.
