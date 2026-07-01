"""A3 — Long-term memory store: write + relevance-based retrieve.

`python memory_store.py` → `_check()` ke asserts pass. Harness edit mat karo.
(Real store embeddings + vector DB use karega — yeh keyword version concept ke liye.)

Contract:
- add(text): ek memory store karo.
- search(query, k=3) -> list[str]: stored memories jinme query se koi shabd overlap
  ho, RELEVANCE (shared words count) descending sorted, top-k. Koi overlap na ho → skip.
  Bilkul relevant kuch na ho → empty list.
"""


class MemoryStore:
    def __init__(self):
        # TODO: memories store karo
        raise NotImplementedError

    def add(self, text: str) -> None:
        # TODO
        raise NotImplementedError

    def search(self, query: str, k: int = 3) -> list[str]:
        # TODO: shared-word count se rank; >0 overlap; top-k
        raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    s = MemoryStore()
    s.add("user prefers Hinglish")
    s.add("user is on enterprise plan")
    s.add("weather is nice today")

    res = s.search("what plan is the user on", k=2)
    assert len(res) >= 1, "relevant memory milna chahiye"
    assert "enterprise" in res[0], "sabse relevant (plan waali) memory top pe"

    unrelated = s.search("quantum chromodynamics lagrangian", k=3)
    assert unrelated == [], "koi overlap nahi → empty (galat memory inject na ho)"
    print("OK: memory_store A3 pass — write + relevance retrieve verified")


if __name__ == "__main__":
    _check()
