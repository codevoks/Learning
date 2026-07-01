"""A3 — Safety gate: destructive computer actions ko HITL ke liye flag karo.

`python safety_gate.py` → `_check()` ke asserts pass. Harness + sets edit mat karo;
sirf `needs_confirmation` bharo.

Contract:
- needs_confirmation(action) -> bool: True agar action DESTRUCTIVE hai —
    * action["type"] DESTRUCTIVE_TYPES mein hai, YA
    * type == "click" aur action ka "label" (case-insensitive) kisi
      DESTRUCTIVE_KEYWORD ko contain karta hai.
  Warna False (safe read-only action).
"""

DESTRUCTIVE_TYPES = {"purchase", "delete", "submit", "send_email", "transfer"}
DESTRUCTIVE_KEYWORDS = ["buy", "delete", "pay", "confirm order", "place order"]


def needs_confirmation(action: dict) -> bool:
    # TODO: type check + click label keyword check
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    assert needs_confirmation({"type": "purchase", "amount": 100}) is True, "purchase → HITL"
    assert needs_confirmation({"type": "delete", "id": 5}) is True, "delete → HITL"
    assert needs_confirmation({"type": "click", "label": "Buy now"}) is True, "buy click → HITL"
    assert needs_confirmation({"type": "click", "label": "Place Order"}) is True, "order → HITL"

    assert needs_confirmation({"type": "click", "label": "Read more"}) is False, "safe click"
    assert needs_confirmation({"type": "scroll", "direction": "down"}) is False, "scroll safe"
    assert needs_confirmation({"type": "type", "text": "hello"}) is False, "type safe"
    print("OK: safety_gate A3 pass — destructive actions gated, safe ones pass")


if __name__ == "__main__":
    _check()
