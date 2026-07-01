"""A1 — Preference dataset builder: ranked outputs se (chosen, rejected) pairs.

`python preference_dataset.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract:
- build_preference_pairs(prompt, ranked) -> list[dict]:
  `ranked` = outputs, best-first order. Har pair (i, j) jahan i, j se BEHTAR (upar)
  hai, ek {"prompt":..., "chosen": ranked[i], "rejected": ranked[j]} banao.
  (n outputs → C(n,2) pairs.)
"""


def build_preference_pairs(prompt: str, ranked: list[str]) -> list[dict]:
    # TODO: har i<j pe (chosen=ranked[i], rejected=ranked[j])
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    ranked = ["best", "mid", "worst"]
    pairs = build_preference_pairs("q", ranked)

    assert len(pairs) == 3, f"C(3,2)=3 pairs chahiye, mile {len(pairs)}"
    assert {"prompt": "q", "chosen": "best", "rejected": "worst"} in pairs
    assert {"prompt": "q", "chosen": "mid", "rejected": "worst"} in pairs
    # chosen hamesha rejected se upar (better) rank pe
    for p in pairs:
        assert ranked.index(p["chosen"]) < ranked.index(p["rejected"]), "chosen better hona chahiye"
        assert p["prompt"] == "q", "prompt carry ho"

    assert build_preference_pairs("x", ["only"]) == [], "ek output → koi pair nahi"
    print("OK: preference_dataset A1 pass — chosen/rejected pairs from ranking verified")


if __name__ == "__main__":
    _check()
