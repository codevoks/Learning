"""A4 — Dependency injection: API key verification."""

# TODO: import Depends, Header, HTTPException from fastapi

DEV_API_KEY = "dev-secret"


async def verify_api_key(
    # TODO: x_api_key from Header — name "X-API-Key", required
):
    """Raise 401 if key missing or wrong; return key on success."""
    raise NotImplementedError
