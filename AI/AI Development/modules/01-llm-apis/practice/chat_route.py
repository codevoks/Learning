"""A1 — Non-streaming chat completion. Complete the TODOs."""

from fastapi import FastAPI
from pydantic import BaseModel

app = FastAPI()


class ChatRequest(BaseModel):
    message: str


# TODO: load API key from .env (python-dotenv)
# TODO: POST handler — call LLM with system + user messages
# TODO: return { "content": "...", "usage": { "prompt_tokens": N, "completion_tokens": M } }
# TODO: log usage as structured JSON


@app.post("/chat")
async def chat(req: ChatRequest):
    raise NotImplementedError("Complete A1 TODOs")
