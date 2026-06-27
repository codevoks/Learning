"""A2 — Health check router."""

# TODO: import APIRouter
from fastapi import APIRouter

# router = None  # TODO: APIRouter(tags=["health"])
router = APIRouter(tags=["health"])

# TODO: @router.get("/health") — return {"status": "ok", "service": "practice-gateway"}
@router.get("/health")
async def health():
    return {"status":"ok","service":"practice-gateway"}