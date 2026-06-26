"""A2 — SSE streaming endpoint. Complete the TODOs."""

from fastapi import FastAPI
from fastapi.responses import StreamingResponse
from pydantic import BaseModel

app = FastAPI()


class ChatRequest(BaseModel):
    message: str


# TODO: call LLM with stream=True
# TODO: yield SSE chunks — format: data: {...}\n\n
# TODO: end with data: [DONE]\n\n


@app.post("/chat/stream")
async def chat_stream(req: ChatRequest):
  # TODO: return StreamingResponse(generator, media_type="text/event-stream")
  raise NotImplementedError("Complete A2 TODOs")
