"""FastAPI app — wire routers, middleware, lifespan."""

# TODO: import FastAPI
from sys import version
from fastapi import FastAPI
# TODO: import routers from app.routes.health, chat, events
from app.routes import health, chat, events
# TODO: import RequestIDMiddleware from app.middleware
from app.middleware import RequestIDMiddleware

# app = None  # TODO: FastAPI(title="Module 00c Practice", version="0.1.0")
app = FastAPI(title="Module 00c Practice", version="0.1.0")

# TODO: app.add_middleware(RequestIDMiddleware)
app.add_middleware(RequestIDMiddleware)

# TODO: include_router for health, chat, events
app.include_router(health.router)
app.include_router(chat.router)
app.include_router(events.router)
# Hint: if chat router has no prefix, mount at root; align paths with README curl examples
