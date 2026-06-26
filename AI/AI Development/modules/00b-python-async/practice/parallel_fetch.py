"""A2 — Fetch 3 URLs in parallel with asyncio.gather. Complete the TODOs."""

import asyncio
import time

# TODO: import httpx

URLS = [
    "https://httpbin.org/delay/1",
    "https://httpbin.org/delay/1",
    "https://httpbin.org/delay/1",
]


async def fetch_status(url: str) -> int:
    """Return HTTP status code for url."""
    # TODO: use httpx.AsyncClient with timeout=15.0
    # TODO: GET url, return response.status_code
    raise NotImplementedError


async def fetch_all_parallel(urls: list[str]) -> list[int]:
    """Fetch all URLs concurrently."""
    # TODO: build list of coroutines and await asyncio.gather
    raise NotImplementedError


async def main():
    start = time.perf_counter()
    # TODO: call fetch_all_parallel(URLS)
    # TODO: print statuses and elapsed seconds
    # Pass when elapsed ≈ 1–2s (not ~3s serial)
    raise NotImplementedError


if __name__ == "__main__":
    asyncio.run(main())
