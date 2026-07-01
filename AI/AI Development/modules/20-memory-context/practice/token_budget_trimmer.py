"""A2 — Context budget trimmer: system rakho, purane drop, budget ke andar aao.

`python token_budget_trimmer.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract:
- trim_to_budget(messages, max_tokens, count_fn) -> list[dict]:
    * SAARE system messages hamesha rakho (kabhi drop nahi — wo policy).
    * Baaki mein se OLDEST non-system pehle drop karo jab tak
      total token count (sum of count_fn over kept) <= max_tokens na ho jaaye.
    * Order preserve karo.
`count_fn(content)` ek int deta hai (tokens ka estimate).
"""


def trim_to_budget(messages: list[dict], max_tokens: int, count_fn) -> list[dict]:
    # TODO: system always keep; oldest non-system drop until under budget
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    count = lambda c: len(c.split())  # word count = fake token count
    msgs = [
        {"role": "system", "content": "a b c"},        # 3, keep always
        {"role": "user", "content": "d e"},            # 2, oldest
        {"role": "assistant", "content": "f g h i"},   # 4
        {"role": "user", "content": "j"},              # 1, newest
    ]
    kept = trim_to_budget(msgs, max_tokens=7, count_fn=count)

    contents = [m["content"] for m in kept]
    assert "a b c" in contents, "system hamesha rakho"
    assert "j" in contents, "newest message rakho"
    assert "d e" not in contents, "oldest non-system drop hua"
    assert "f g h i" not in contents, "budget ke liye next oldest bhi drop"
    assert sum(count(m["content"]) for m in kept) <= 7, "total budget ke andar"

    # sab fit ho to kuch drop na ho
    small = [{"role": "system", "content": "x"}, {"role": "user", "content": "y"}]
    assert len(trim_to_budget(small, 100, count)) == 2, "budget mein sab fit → kuch drop nahi"
    print("OK: token_budget_trimmer A2 pass — system kept, oldest dropped, budget met")


if __name__ == "__main__":
    _check()
