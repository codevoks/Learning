# Module 17 — Assignments (Transformers from Scratch)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`
> A1–A3 offline (NumPy) — `python <file>.py` → `_check()` pass. Attention dheere samjho.

## Progress checklist

- [ ] A1 — `attention.py`
- [ ] A2 — `causal_mask.py`
- [ ] A3 — `kv_cache.py`
- [ ] Active recall → NOTES

## Setup

```bash
cd modules/17-transformers-scratch/practice
python3 -m venv .venv && source .venv/bin/activate
pip install numpy
```

---

## A1 — Scaled dot-product attention

| | |
|---|---|
| **Theory §** | §2 |
| **File** | `attention.py` |
| **Kya** | Q·Kᵀ/√d → softmax → weighted V |
| **Pass** | `python attention.py` → `_check()` asserts pass |

## A2 — Causal mask

| | |
|---|---|
| **Theory §** | §6 |
| **File** | `causal_mask.py` |
| **Kya** | Lower-triangular mask (future blocked) |
| **Pass** | `python causal_mask.py` → `_check()` asserts pass |

## A3 — KV cache

| | |
|---|---|
| **Theory §** | §7 |
| **File** | `kv_cache.py` |
| **Kya** | Append + grow (O(n) generation) |
| **Pass** | `python kv_cache.py` → `_check()` asserts pass |

---

## Active recall (NOTES)

1. Q/K/V library analogy?
2. `√d` scaling kyun?
3. KV cache O(n²) → O(n) kaise?

**Stuck?** `@modules/17-transformers-scratch/MODULE.md` + error paste. Video: Karpathy "Let's build GPT".
