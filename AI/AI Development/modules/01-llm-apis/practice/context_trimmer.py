"""A4 — Trim long message history to fit context window. Complete the TODOs."""

# Message shape: {"role": "system"|"user"|"assistant", "content": str}

def trim_messages(
    messages: list[dict],
    max_tokens: int,
    # TODO: optional tokenizer or char-based estimate
) -> list[dict]:
    """
    Strategy (document in docstring):
    1. Always keep system message
    2. Drop oldest user/assistant pairs until under budget
    3. ...
    """
    raise NotImplementedError


if __name__ == "__main__":
    sample = [
        {"role": "system", "content": "You are helpful."},
        {"role": "user", "content": "..." * 1000},
    ]
    # TODO: print trimmed result
    pass
