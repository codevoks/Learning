"""A1 — ChatRequest + ChatResponse Pydantic models. Complete the TODOs."""

from pydantic import BaseModel, Field, ValidationError

# TODO: import Field if not already used


class ChatRequest(BaseModel):
    """Incoming chat message from client."""

    # TODO: message — str, min_length=1, max_length=4000
    # TODO: model — str, default "gpt-4o-mini"
    # TODO: stream — bool, default False
    pass


class ChatResponse(BaseModel):
    """Gateway reply to client."""

    # TODO: reply — str, required
    # TODO: tokens_used — int, required
    pass


def _demo():
    # TODO: create valid ChatRequest from dict {"message": "hello"}
    # TODO: print model_dump()
    # TODO: try invalid message "" — catch ValidationError, print that validation failed
    raise NotImplementedError("Complete A1 TODOs")


if __name__ == "__main__":
    _demo()
