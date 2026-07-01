"""A3 — Voice pipeline latency budget: total, bottleneck, target check.

`python latency_budget.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract (stages = dict of {stage_name: milliseconds}):
- total_latency(stages): saare stages ka sum.
- bottleneck(stages): sabse bade latency wale stage ka naam.
- meets_target(stages, target_ms): True agar total <= target_ms.
"""


def total_latency(stages: dict) -> float:
    # TODO: sum of stage latencies
    raise NotImplementedError


def bottleneck(stages: dict) -> str:
    # TODO: max latency wale stage ka naam
    raise NotImplementedError


def meets_target(stages: dict, target_ms: float) -> bool:
    # TODO: total <= target_ms ?
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    stages = {"stt": 300, "llm_ttft": 500, "tts": 200, "network": 100}
    assert total_latency(stages) == 1100, "total = sum"
    assert bottleneck(stages) == "llm_ttft", "sabse bada stage llm_ttft"
    assert meets_target(stages, 800) is False, "1100 > 800 → miss"
    assert meets_target(stages, 1200) is True, "1100 <= 1200 → ok"

    # LLM optimize karne ke baad realtime threshold meet
    faster = {"stt": 300, "llm_ttft": 250, "tts": 200}
    assert bottleneck(faster) == "stt", "ab stt bottleneck"
    assert meets_target(faster, 800) is True
    print("OK: latency_budget A3 pass — total + bottleneck + target verified")


if __name__ == "__main__":
    _check()
