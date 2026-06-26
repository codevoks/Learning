"""A3 — Request ID middleware."""

import uuid

# TODO: import BaseHTTPMiddleware from starlette.middleware.base


class RequestIDMiddleware:
    """Add X-Request-ID to every response."""

    # TODO: subclass BaseHTTPMiddleware
    # TODO: in dispatch: read X-Request-ID from request or generate uuid4
    # TODO: await call_next(request), set response header X-Request-ID
    pass
