"""A3 — Request ID middleware."""

import uuid

# TODO: import BaseHTTPMiddleware from starlette.middleware.base
from starlette.middleware.base import BaseHTTPMiddleware


class RequestIDMiddleware(BaseHTTPMiddleware):
    """Add X-Request-ID to every response."""

    # TODO: subclass BaseHTTPMiddleware
    # TODO: in dispatch: read X-Request-ID from request or generate uuid4
    async def dispatch(self, request, call_next):
        request_id = request.headers.get("X-Request-ID") or str(uuid.uuid4())
    # TODO: await call_next(request), set response header X-Request-ID
        response= await call_next(request);
        response.headers["X-Request-ID"]=request_id
        return response
    pass
