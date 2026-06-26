"""A5 — SSE stub: stream tick events."""

import asyncio

# TODO: import APIRouter, StreamingResponse

router = None  # TODO: APIRouter(tags=["events"])


async def tick_stream():
    """Yield 5 SSE events, 1 second apart."""
    # TODO: for i in range(5): yield f"data: tick {i}\\n\\n"; await asyncio.sleep(1)
    raise NotImplementedError


# TODO: GET /events → StreamingResponse(tick_stream(), media_type="text/event-stream")
