"""A3 — Dataset quality: dedup + clean + deterministic train/holdout split.

`python dataset_quality.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract:
- prepare(examples, holdout_frac=0.2) -> {"train": [...], "holdout": [...], "dropped": int}
    1. Drop examples jinme output khaali/whitespace hai.
    2. Dedup by `instruction` (exact) — pehla rakho, baad ke duplicates hatao.
    3. Bache examples ko DETERMINISTICALLY split karo (jaise instruction se sort,
       phir pehle round(holdout_frac * n) ko holdout). Train/holdout mein OVERLAP na ho.
    "dropped" = kitne examples (empty + duplicate) hatae.
"""


def prepare(examples: list[dict], holdout_frac: float = 0.2) -> dict:
    # TODO: clean → dedup → deterministic split
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    raw = [{"instruction": f"q{i}", "output": f"a{i}"} for i in range(10)]
    raw.append({"instruction": "q0", "output": "a0"})   # duplicate instruction
    raw.append({"instruction": "qX", "output": "   "})  # empty output

    prep = prepare(raw, holdout_frac=0.2)
    total = len(prep["train"]) + len(prep["holdout"])
    assert total == 10, f"10 clean unique bachne chahiye, mile {total}"
    assert prep["dropped"] == 2, f"1 dup + 1 empty = 2 dropped, mila {prep['dropped']}"
    assert len(prep["holdout"]) == 2, "20% of 10 = 2 holdout"
    assert prep["train"] and prep["holdout"], "dono non-empty"

    train_ins = {e["instruction"] for e in prep["train"]}
    hold_ins = {e["instruction"] for e in prep["holdout"]}
    assert train_ins.isdisjoint(hold_ins), "train/holdout overlap → eval jhootha hoga"

    # deterministic: dobara chalao → wahi split
    prep2 = prepare(raw, holdout_frac=0.2)
    assert {e["instruction"] for e in prep2["holdout"]} == hold_ins, "split deterministic hona chahiye"
    print("OK: dataset_quality A3 pass — dedup + clean + no-leak deterministic split")


if __name__ == "__main__":
    _check()
