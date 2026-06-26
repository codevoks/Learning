"""M1 — Gateway skeleton: health + provider passthrough. Complete TODOs."""

from fastapi import FastAPI

app = FastAPI()

# TODO: GET /health → {"status": "ok"}
# TODO: POST /v1/chat — forward to provider, return response + usage


@app.get("/health")
async def health():
    raise NotImplementedError
