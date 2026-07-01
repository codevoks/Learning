"""A1 — PII redactor (input guardrail).

`python pii_redactor.py` → `_check()` ke asserts pass hone chahiye. Harness edit
mat karo; sirf `redact_pii` bharo.

Contract:
- redact_pii(text): card number → "[CARD]", email → "[EMAIL]", 10-digit phone →
  "[PHONE]". Baaki text as-is. Order dhyaan se (card ke digit-groups phone se
  takra sakte hain — card pehle redact karo).
Hint: `re` module. Card ~ 4 groups of 4 digits (optional - / space); email ~
  `\S+@\S+\.\S+`; phone ~ 10 digits.
"""

import re  # noqa: F401  (tumhe use karna hai)


def redact_pii(text: str) -> str:
    # TODO: re.sub se card → [CARD], email → [EMAIL], phone → [PHONE]
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    out = redact_pii("Pay 4111-1111-1111-1111 from john@doe.com or call 9876543210")
    assert "[CARD]" in out, "card redact hona chahiye"
    assert "[EMAIL]" in out, "email redact hona chahiye"
    assert "[PHONE]" in out, "phone redact hona chahiye"
    assert "4111" not in out, "raw card number leak nahi hona chahiye"
    assert "john@doe.com" not in out, "raw email leak nahi"
    assert "9876543210" not in out, "raw phone leak nahi"
    assert redact_pii("What is your refund policy?") == "What is your refund policy?", \
        "normal text nahi badalna chahiye"
    print("OK: pii_redactor A1 pass — card/email/phone redacted, clean text untouched")


if __name__ == "__main__":
    _check()
