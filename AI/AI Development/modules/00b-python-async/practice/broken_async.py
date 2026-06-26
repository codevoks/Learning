"""A3 — This code is intentionally broken. Fix blocking calls for async."""

import asyncio
import time

# BUG: sync libraries — replace with async-friendly versions
import requests

SLOW_URL = "https://httpbin.org/delay/1"


async def fetch_slow() -> str:
    """Should not block the event loop."""
    # BUG: blocks entire loop
    time.sleep(1)
    # BUG: blocking HTTP
    r = requests.get(SLOW_URL, timeout=10)
    return r.text[:50]


async def run_two():
    """Both fetches should overlap (~1s total, not ~2s)."""
    start = time.perf_counter()
    # TODO: run two fetch_slow() concurrently (gather)
    results = []  # replace after fix
    elapsed = time.perf_counter() - start
    print(f"elapsed={elapsed:.2f}s, results={len(results)}")
    # Pass when elapsed < 1.5s and you documented fix in NOTES.md


if __name__ == "__main__":
    asyncio.run(run_two())
