"""M5 — Outbox + idempotent execution.

Goal: same idempotency_key do baar enqueue ho to side-effect sirf EK baar ho
(exactly-once). `python outbox_stub.py` chalao — `_check()` ke asserts pass hone
chahiye. Harness edit mat karo; sirf functions + storage bharo.

Contract:
- enqueue(event, key): event ko outbox mein daalo (dupe keys allowed in queue).
- process_outbox(): har pending event execute karo, par har UNIQUE key sirf ek
  baar side-effect kare. Jab koi key pehli baar execute ho, SIDE_EFFECTS mein ek
  entry append karo. Return: is call mein kitne NAYE side-effects hue.
"""

# Side-effect sink — process_outbox jab kisi key ko pehli baar execute kare,
# yahan ek entry append karo (yeh tumhare "real" action ka stand-in hai).
SIDE_EFFECTS: list[dict] = []


def enqueue(event: dict, idempotency_key: str) -> None:
    # TODO: in-memory list / sqlite mein (event, idempotency_key) store karo
    raise NotImplementedError


def process_outbox() -> int:
    """Pending events process karo; har unique key ek hi side-effect. Returns new count."""
    # TODO: processed keys track karo; nayi key pe SIDE_EFFECTS.append(...)
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    SIDE_EFFECTS.clear()
    enqueue({"action": "refund", "amount": 50}, "k1")
    enqueue({"action": "refund", "amount": 50}, "k1")   # duplicate key (retry)
    enqueue({"action": "email"}, "k2")

    new1 = process_outbox()
    assert new1 == 2, f"2 unique keys → 2 side-effects, mila {new1}"
    assert len(SIDE_EFFECTS) == 2, "duplicate k1 sirf ek baar execute hona chahiye"

    new2 = process_outbox()  # dobara process — kuch naya nahi
    assert new2 == 0, "already-processed events dobara execute na hon"
    assert len(SIDE_EFFECTS) == 2, "idempotent: total side-effects abhi bhi 2"

    print("OK: outbox M5 pass — duplicate enqueue → single side-effect (exactly-once)")


if __name__ == "__main__":
    _check()
