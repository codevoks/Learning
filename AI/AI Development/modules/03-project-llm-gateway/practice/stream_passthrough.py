"""M7 — SSE streaming passthrough. Complete TODOs."""

from fastapi import FastAPI
from fastapi.responses import StreamingResponse

app = FastAPI()

# TODO: POST /v1/chat/stream — proxy provider SSE to client unchanged
# TODO: log token usage at end of stream


@app.post("/v1/chat/stream")
async def stream_chat():
    raise NotImplementedError
