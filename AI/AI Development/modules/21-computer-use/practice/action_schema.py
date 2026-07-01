"""A1 — Computer-use action ko schema ke against validate (execute se pehle).

`python action_schema.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract:
- validate_action(action) -> bool. Valid actions (allowlist):
    {"type":"click", "x":int, "y":int}
    {"type":"type", "text":str}
    {"type":"scroll", "direction":"up"|"down"}
    {"type":"done"}
  Missing/galat field ya unknown type → False (allowlist — kuch bhi allowed nahi).
"""


def validate_action(action: dict) -> bool:
    # TODO: type ke hisaab se required fields check karo
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    assert validate_action({"type": "click", "x": 10, "y": 20}) is True
    assert validate_action({"type": "type", "text": "hello"}) is True
    assert validate_action({"type": "scroll", "direction": "down"}) is True
    assert validate_action({"type": "done"}) is True

    assert validate_action({"type": "click", "x": 10}) is False, "y missing"
    assert validate_action({"type": "type"}) is False, "text missing"
    assert validate_action({"type": "scroll", "direction": "sideways"}) is False, "invalid dir"
    assert validate_action({"type": "teleport"}) is False, "unknown type (allowlist)"
    assert validate_action({}) is False, "no type"
    print("OK: action_schema A1 pass — valid/invalid actions distinguished (allowlist)")


if __name__ == "__main__":
    _check()
