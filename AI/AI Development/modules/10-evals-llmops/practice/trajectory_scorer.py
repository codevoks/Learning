"""A2 — Trajectory scorer: agent ke steps expected order se match karte hain?

`python trajectory_scorer.py` → `_check()` ke asserts pass hone chahiye. Harness
edit mat karo; sirf do functions bharo.

Contract:
- score_trajectory(expected, actual): True sirf jab actual == expected (exact
  order). HITL jaisा step skip hua → False (yahi safety catch hai).
- run_report(dataset_path): JSON list padho (har case mein `expected_steps` +
  `actual_steps`), har case score karo, aur dict return karo:
  {"pass_count": int, "fail_count": int, "pass_rate": float}.
"""

import json


def score_trajectory(expected: list[str], actual: list[str]) -> bool:
    # TODO: exact-order match (Module 10 §2)
    raise NotImplementedError


def run_report(dataset_path: str) -> dict:
    # TODO: json.load → har case pe score_trajectory(expected_steps, actual_steps)
    #       → pass_count / fail_count / pass_rate
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    assert score_trajectory(["a", "b"], ["a", "b"]) is True, "same steps → pass"
    assert score_trajectory(["a", "b"], ["b", "a"]) is False, "order galat → fail"
    assert score_trajectory(["a", "hitl", "b"], ["a", "b"]) is False, \
        "HITL skip hua → fail (outcome theek ho tab bhi)"

    import tempfile, os
    cases = [
        {"id": "p1", "expected_steps": ["x", "y"], "actual_steps": ["x", "y"]},
        {"id": "p2", "expected_steps": ["a"], "actual_steps": ["a"]},
        {"id": "f1", "expected_steps": ["a", "hitl", "b"], "actual_steps": ["a", "b"]},
    ]
    fd, path = tempfile.mkstemp(suffix=".json")
    with os.fdopen(fd, "w") as f:
        json.dump(cases, f)
    try:
        rep = run_report(path)
    finally:
        os.remove(path)

    assert rep["pass_count"] == 2, f"2 pass expected, mila {rep['pass_count']}"
    assert rep["fail_count"] == 1, f"1 fail expected, mila {rep['fail_count']}"
    assert abs(rep["pass_rate"] - 2 / 3) < 1e-6, "pass_rate = 2/3"

    print("OK: trajectory_scorer A2 pass — exact-order + report counts verified")


if __name__ == "__main__":
    _check()
