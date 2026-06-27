"""A4 — Dependency injection: API key verification."""

# TODO: import Depends, Header, HTTPException from fastapi
from fastapi import Depends, Header, HTTPException

DEV_API_KEY = "dev-secret"


async def verify_api_key(x_api_key:str=Header(...)):
    # TODO: x_api_key from Header — name "X-API-Key", required
    if(x_api_key==None or x_api_key!= DEV_API_KEY):
        raise HTTPException(status_code=401);
    else:
        return x_api_key
    """Raise 401 if key missing or wrong; return key on success."""
    # raise NotImplementedError
