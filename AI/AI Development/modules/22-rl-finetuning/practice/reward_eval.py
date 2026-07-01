"""A2 — Reward model eval: pairwise accuracy on preference pairs.

`python reward_eval.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract:
- pairwise_accuracy(reward_fn, pairs) -> float:
  `pairs` = [{"chosen":..., "rejected":...}, ...]. `reward_fn(text)` ek score deta hai.
  Fraction of pairs jahan reward_fn(chosen) > reward_fn(rejected). (Achha reward model
  = high pairwise accuracy — Module 10 eval, reward model pe.)
"""


def pairwise_accuracy(reward_fn, pairs: list[dict]) -> float:
    # TODO: fraction jahan reward(chosen) > reward(rejected)
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    pairs = [{"chosen": "good", "rejected": "bad"}, {"chosen": "yesss", "rejected": "no"}]

    # perfect reward: length se dono pairs mein chosen jeet-ta
    r_perfect = lambda t: len(t)   # good(4)>bad(3); yesss(5)>no(2)
    assert pairwise_accuracy(r_perfect, pairs) == 1.0, "sab sahi → 1.0"

    # ek galat: 'bad' ko zyada reward
    scores = {"good": 1, "bad": 2, "yesss": 5, "no": 1}
    r_half = lambda t: scores[t]   # good(1)>bad(2)? no; yesss(5)>no(1)? yes → 0.5
    assert pairwise_accuracy(r_half, pairs) == 0.5, "ek pair galat → 0.5"

    # random-worse: sab galat
    r_bad = lambda t: -len(t)
    assert pairwise_accuracy(r_bad, pairs) == 0.0, "sab galat → 0.0"
    print("OK: reward_eval A2 pass — pairwise accuracy verified")


if __name__ == "__main__":
    _check()
