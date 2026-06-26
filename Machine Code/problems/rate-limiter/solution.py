"""Rate Limiter (token bucket) — machine-coding stub (target 30 min). Run: python solution.py"""


class TokenBucket:
    def __init__(self, capacity: int, refill_per_sec: float):
        self.capacity = capacity
        self.rate = refill_per_sec
        self.tokens: dict[str, float] = {}
        self.last: dict[str, float] = {}
    def allow(self, key: str, now: float) -> bool:
        # TODO: refill tokens based on (now - last)*rate capped at capacity;
        # if tokens >= 1 consume one -> True else False
        raise NotImplementedError


if __name__ == "__main__":
    rl = TokenBucket(capacity=2, refill_per_sec=1)
    assert rl.allow("u", 0.0) and rl.allow("u", 0.0)   # 2 tokens
    assert not rl.allow("u", 0.0)                       # empty
    assert rl.allow("u", 1.0)                           # refilled 1
    print("PASS")

# PASSING CRITERIA: bursts up to capacity; denies when empty; refills correctly over time; per-key isolation.
