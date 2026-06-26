"""A3 — RAG answer endpoint stub. Complete TODOs."""

from fastapi import FastAPI

app = FastAPI()

# TODO: retrieve top-k chunks
# TODO: build prompt with delimited context
# TODO: return { "answer": "...", "citations": ["chunk_id_1", ...] }


@app.post("/rag/ask")
async def ask(question: str):
    raise NotImplementedError
