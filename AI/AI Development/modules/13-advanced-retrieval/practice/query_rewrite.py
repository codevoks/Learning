"""A4 — Multi-query generation: ek query se kai retrieval-friendly variants.

`python query_rewrite.py` → `_check()` structural asserts pass. Harness edit mat
karo. Implementation LLM se karo (behtar) ya offline heuristic se (chalega) —
harness sirf STRUCTURE check karta hai, content nahi.

Contract:
- expand_query(query, n=3) -> list[str]: `n` variants return karo (original bhi
  list mein ho). Sab non-empty, kam se kam 2 distinct.
Note: production mein yeh ek LLM call hai (§4). Yahan bas interface + recall-boost
idea. HyDE / decomposition bhi try kar sakte ho.
"""


def expand_query(query: str, n: int = 3) -> list[str]:
    # TODO: LLM se n paraphrase/variants, ya offline heuristic (synonyms/expansions)
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo — structure only)
# ---------------------------------------------------------------------------
def _check() -> None:
    q = "refund policy"
    variants = expand_query(q, n=3)
    assert isinstance(variants, list) and len(variants) == 3, "n=3 variants chahiye"
    assert all(isinstance(v, str) and v.strip() for v in variants), "sab non-empty strings"
    assert q in variants, "original query bhi list mein ho"
    assert len(set(variants)) >= 2, "kam se kam 2 distinct variants"
    print("OK: query_rewrite A4 pass — multi-query structure verified")


if __name__ == "__main__":
    _check()
