"""A2 — Pydantic-validated tool args (execute se PEHLE validate).

`python pydantic_tools.py` → `_check()` ke asserts pass hone chahiye. Harness aur
TOOL_FUNCS fixtures edit mat karo; tumhe `WeatherArgs` + `validate_and_run` bharne hain.

Contract for validate_and_run(tool_name, raw_args):
- raw_args ek JSON string hai. Use parse + sahi pydantic model se validate karo.
- Valid → us tool ka function chalao (TOOL_FUNCS se) aur uska dict return karo.
- Invalid JSON / missing field / out-of-range → execute MAT karo; ek
  {"error": "..."} dict return karo.
"""

from pydantic import BaseModel, Field


class SearchDocsArgs(BaseModel):
    query: str = Field(description="Search terms")
    limit: int = Field(default=5, ge=1, le=20)


# TODO: WeatherArgs — `city: str` required (min_length=1)


# Given fixtures — yeh "tools" hain (inhe edit mat karo). Tumhe sirf validation likhna hai.
def _search_docs(query: str, limit: int = 5) -> dict:
    return {"results": [f"doc about {query}"][:limit]}


def _get_weather(city: str) -> dict:
    return {"city": city, "temp_c": 18}


TOOL_FUNCS = {"search_docs": _search_docs, "get_weather": _get_weather}
SCHEMA_MAP: dict[str, type[BaseModel]] = {"search_docs": SearchDocsArgs}  # TODO: get_weather add karo


def validate_and_run(tool_name: str, raw_args: str) -> dict:
    # TODO: SCHEMA_MAP[tool_name].model_validate_json(raw_args) try/except;
    #       valid → TOOL_FUNCS[tool_name](**args.model_dump()); invalid → {"error": ...}
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    ok = validate_and_run("search_docs", '{"query": "refund", "limit": 3}')
    assert "error" not in ok and "results" in ok, "valid args → tool chale"

    bad_range = validate_and_run("search_docs", '{"query": "x", "limit": 999}')
    assert "error" in bad_range, "limit > 20 → reject (execute se pehle)"

    bad_json = validate_and_run("search_docs", "not even json")
    assert "error" in bad_json, "invalid JSON → reject, crash nahi"

    bad_missing = validate_and_run("get_weather", "{}")
    assert "error" in bad_missing, "required city missing → reject"

    good_weather = validate_and_run("get_weather", '{"city": "Berlin"}')
    assert good_weather.get("city") == "Berlin", "valid weather args → tool chale"

    print("OK: pydantic_tools A2 pass — invalid args execute se pehle reject")


if __name__ == "__main__":
    _check()
