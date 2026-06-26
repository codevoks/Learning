"""A1 — Redis token bucket rate limiter. Complete the TODOs."""

import redis

# TODO: connect redis.Redis(host="localhost", port=6379)
# TODO: def is_allowed(key: str, limit: int, window_seconds: int) -> bool
# TODO: def check_or_raise(key: str) -> None  # raises RateLimitExceeded if over limit


class RateLimitExceeded(Exception):
    pass


if __name__ == "__main__":
    # TODO: loop 70 requests — expect 429 after limit
    pass
