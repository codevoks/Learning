"""A3 — Circuit breaker wrapper (CLOSED → OPEN → HALF_OPEN → CLOSED).

`python circuit_breaker.py` → `_check()` ke asserts pass hone chahiye. Harness
edit mat karo; sirf `CircuitBreaker.__init__` aur `.call` bharo.

Contract:
- __init__(failure_threshold=3, recovery_timeout_seconds=30)
- call(fn): CLOSED mein fn() chalao.
    * fn exception phenke → failure count++. threshold pe pahunche → OPEN.
    * OPEN mein: fn ko call MAT karo, seedha CircuitOpenError raise karo (fast fail).
    * OPEN ke recovery_timeout baad ek probe allow karo (HALF_OPEN). probe success
      → CLOSED + reset; probe fail → wapas OPEN.
Time ke liye `time.monotonic()` use karo (test chhota timeout deta hai).
"""

import time
from enum import Enum


class State(Enum):
    CLOSED = "closed"
    OPEN = "open"
    HALF_OPEN = "half_open"


class CircuitOpenError(Exception):
    """Breaker OPEN — provider call kiye bina fast fail."""


class CircuitBreaker:
    # TODO: __init__(self, failure_threshold=3, recovery_timeout_seconds=30)
    # TODO: def call(self, fn): state machine — upar ka contract follow karo
    pass


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    cb = CircuitBreaker(failure_threshold=3, recovery_timeout_seconds=0.05)

    def boom():
        raise RuntimeError("provider down")

    # 3 failures → OPEN
    for _ in range(3):
        try:
            cb.call(boom)
        except RuntimeError:
            pass

    # OPEN: agla call fn ko chhue bina fast-fail kare
    calls = {"n": 0}
    def probe():
        calls["n"] += 1
        return "ok"

    try:
        cb.call(probe)
        raise AssertionError("OPEN state mein CircuitOpenError aana chahiye tha")
    except CircuitOpenError:
        pass
    assert calls["n"] == 0, "OPEN mein fn call nahi hona chahiye (fast fail)"

    time.sleep(0.06)  # recovery_timeout cross → HALF_OPEN probe allowed
    assert cb.call(probe) == "ok", "recovery ke baad probe chalna chahiye"
    assert calls["n"] == 1, "probe ne fn ek baar call kiya"

    # probe success → CLOSED: normal calls phir chalein
    assert cb.call(probe) == "ok"
    print("OK: circuit_breaker A3 pass — OPEN fast-fail + HALF_OPEN probe + recovery")


if __name__ == "__main__":
    _check()
