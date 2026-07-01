"""A3 — Output guardrail: model output ko user tak jaane se pehle validate.

`python output_validator.py` → `_check()` ke asserts pass hone chahiye. Harness +
BANNED edit mat karo; sirf `validate_output` bharo.

Contract:
- validate_output(text) -> {"ok": bool, "reasons": list[str]}
    * PII leak (email ya card) mile → ok False, reason mein "pii"
    * BANNED phrase (case-insensitive) mile → ok False, reason mein "banned"
    * clean → {"ok": True, "reasons": []}
Ek output mein kai problem ho to saare reasons list mein aayein.
"""

import re  # noqa: F401

BANNED = ["guaranteed returns", "as an ai language model"]


def validate_output(text: str) -> dict:
    # TODO: PII (email/card) + BANNED phrase check → {"ok":..., "reasons":[...]}
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    good = validate_output("Your refund will be processed within 3 business days.")
    assert good["ok"] is True and good["reasons"] == [], "clean output pass hona chahiye"

    pii = validate_output("Please contact the other customer at jane@example.com")
    assert pii["ok"] is False, "PII leak block hona chahiye"
    assert any("pii" in r.lower() for r in pii["reasons"]), "reason mein pii ho"

    banned = validate_output("We offer guaranteed returns on every trade!")
    assert banned["ok"] is False, "banned phrase block hona chahiye"
    assert any("banned" in r.lower() for r in banned["reasons"]), "reason mein banned ho"

    both = validate_output("As an AI language model, email me at x@y.com")
    assert both["ok"] is False and len(both["reasons"]) >= 2, "dono problems reason mein aayein"

    print("OK: output_validator A3 pass — PII + banned-content caught, clean passed")


if __name__ == "__main__":
    _check()
