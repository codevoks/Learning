"""A2 — Pydantic-validated tool args. Complete TODOs."""

from pydantic import BaseModel, Field


class SearchDocsArgs(BaseModel):
    query: str = Field(description="Search terms")
    limit: int = Field(default=5, ge=1, le=20)


# TODO: WeatherArgs model
# TODO: def validate_and_run(tool_name: str, raw_args: str) -> dict
# TODO: reject invalid JSON / out-of-range before execute


def validate_and_run(tool_name: str, raw_args: str) -> dict:
    raise NotImplementedError
