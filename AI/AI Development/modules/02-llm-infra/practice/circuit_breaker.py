"""A3 — Circuit breaker wrapper. Complete the TODOs."""

from enum import Enum


class State(Enum):
    CLOSED = "closed"
    OPEN = "open"
    HALF_OPEN = "half_open"


class CircuitBreaker:
    # TODO: __init__(failure_threshold=3, recovery_timeout_seconds=30)
    # TODO: def call(self, fn) — wrap provider call
    # TODO: track failures, transition CLOSED → OPEN → HALF_OPEN → CLOSED
    pass


if __name__ == "__main__":
    # TODO: simulate 3 failures → OPEN, then wait → HALF_OPEN probe
    pass
