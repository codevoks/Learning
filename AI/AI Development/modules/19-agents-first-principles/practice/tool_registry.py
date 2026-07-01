"""A1 — Tool registry: register, list (model ke liye), dispatch (execute + allowlist).

`python tool_registry.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract:
- register(name, fn, description): tool add karo.
- list_tools() -> list[dict]: [{"name":..., "description":...}, ...] (model ko dikhane ke liye).
- dispatch(name, **kwargs): registered tool ko args ke saath chalao aur result return karo.
  Unknown name → ValueError raise karo (allowlist — koi bhi tool nahi chal sakta).
"""


class ToolRegistry:
    def __init__(self):
        # TODO: tools store karne ke liye dict {name: (fn, description)}
        raise NotImplementedError

    def register(self, name: str, fn, description: str) -> None:
        # TODO: add
        raise NotImplementedError

    def list_tools(self) -> list[dict]:
        # TODO: [{"name":..., "description":...}, ...]
        raise NotImplementedError

    def dispatch(self, name: str, **kwargs):
        # TODO: unknown → ValueError; warna fn(**kwargs)
        raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    r = ToolRegistry()
    r.register("add", lambda a, b: a + b, "Add two numbers")
    r.register("upper", lambda s: s.upper(), "Uppercase a string")

    assert r.dispatch("add", a=2, b=3) == 5, "dispatch add"
    assert r.dispatch("upper", s="hi") == "HI", "dispatch upper"

    tools = r.list_tools()
    assert {t["name"] for t in tools} == {"add", "upper"}, "list_tools names"
    assert all("description" in t for t in tools), "har tool ka description"

    try:
        r.dispatch("delete_everything")   # unregistered
        raise AssertionError("unknown tool pe ValueError aana chahiye (allowlist)")
    except ValueError:
        pass
    print("OK: tool_registry A1 pass — register/list/dispatch + allowlist verified")


if __name__ == "__main__":
    _check()
