"""A1 — Raw examples ko SFT chat-JSONL format mein badlo.

`python build_sft_dataset.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract:
- to_chat_jsonl(examples, system): `examples` = [{"instruction":..., "output":...}].
  Har example → {"messages": [system_msg, user_msg, assistant_msg]} jahan
  system content=`system`, user content=instruction, assistant content=output.
- validate_row(row): True agar row mein exactly 3 messages hain roles
  system→user→assistant order mein aur koi content khaali nahi.
"""


def to_chat_jsonl(examples: list[dict], system: str) -> list[dict]:
    # TODO: har example → {"messages":[{system},{user=instruction},{assistant=output}]}
    raise NotImplementedError


def validate_row(row: dict) -> bool:
    # TODO: 3 messages, roles system/user/assistant, non-empty content
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    examples = [
        {"instruction": "I was charged twice", "output": "billing_dispute"},
        {"instruction": "Where is my order?", "output": "order_status"},
    ]
    rows = to_chat_jsonl(examples, system="You are a classifier.")
    assert len(rows) == 2, "har example → ek row"

    msgs = rows[0]["messages"]
    assert [m["role"] for m in msgs] == ["system", "user", "assistant"], "role order galat"
    assert msgs[0]["content"] == "You are a classifier.", "system content"
    assert msgs[1]["content"] == "I was charged twice", "user = instruction"
    assert msgs[2]["content"] == "billing_dispute", "assistant = output"

    assert validate_row(rows[0]) is True, "valid row → True"
    bad = {"messages": [{"role": "user", "content": "x"}]}  # missing system/assistant
    assert validate_row(bad) is False, "adhura row → False"
    empty = {"messages": [{"role": "system", "content": ""},
                          {"role": "user", "content": "x"},
                          {"role": "assistant", "content": "y"}]}
    assert validate_row(empty) is False, "khaali content → False"
    print("OK: build_sft_dataset A1 pass — chat JSONL format + validation verified")


if __name__ == "__main__":
    _check()
