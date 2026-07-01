"""A1 — Sliding-window conversation buffer (short-term memory).

`python conversation_buffer.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract:
- ConversationBuffer(max_messages): recent messages rakho, purane drop.
- add(role, content): ek message add karo.
- get() -> list[dict]: sirf last `max_messages` messages ({"role","content"}), order mein.
"""


class ConversationBuffer:
    def __init__(self, max_messages: int):
        # TODO: max_messages + storage
        raise NotImplementedError

    def add(self, role: str, content: str) -> None:
        # TODO: append; window se bahar purane drop
        raise NotImplementedError

    def get(self) -> list[dict]:
        # TODO: last max_messages messages
        raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    b = ConversationBuffer(max_messages=3)
    for i in range(5):
        b.add("user", f"m{i}")
    msgs = b.get()
    assert len(msgs) == 3, f"sirf 3 recent messages, mile {len(msgs)}"
    assert [m["content"] for m in msgs] == ["m2", "m3", "m4"], "last 3 (purane drop)"
    assert all("role" in m and "content" in m for m in msgs), "har message {role, content}"

    b2 = ConversationBuffer(max_messages=10)
    b2.add("system", "rules")
    assert b2.get() == [{"role": "system", "content": "rules"}], "window ke andar sab rahein"
    print("OK: conversation_buffer A1 pass — sliding window (recent kept, old dropped)")


if __name__ == "__main__":
    _check()
