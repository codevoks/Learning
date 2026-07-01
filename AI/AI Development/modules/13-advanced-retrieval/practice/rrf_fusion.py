"""A1 — Reciprocal Rank Fusion: kai ranked lists ko merge karo.

`python rrf_fusion.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract:
- rrf(lists, k=60): `lists` = ranked doc-id lists (har list rank order mein, index 0 = rank 1).
  Har doc ka score = Σ 1/(k + rank) over lists jahan wo doc dikhta hai (rank 1-based).
  Return: (doc_id, score) tuples, score descending sorted.
"""


def rrf(lists: list[list[str]], k: int = 60) -> list[tuple[str, float]]:
    # TODO: har list mein rank (1-based) → score add karo; phir sort desc
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    dense = ["A", "B", "C"]
    bm25 = ["B", "D", "A"]
    ranked = rrf([dense, bm25], k=60)
    order = [d for d, _ in ranked]

    assert set(order) == {"A", "B", "C", "D"}, "saare unique docs aane chahiye"
    # B dono lists mein upar (consensus) → sabse upar
    assert order[0] == "B", f"B (dono lists mein top) pehle aana chahiye, mila {order[0]}"
    assert order == ["B", "A", "D", "C"], f"RRF order galat: {order}"
    # score check: B > A
    scores = dict(ranked)
    assert scores["B"] > scores["A"], "B ka score A se zyada"

    # single list → wahi order
    solo = [d for d, _ in rrf([["X", "Y", "Z"]], k=60)]
    assert solo == ["X", "Y", "Z"], "ek hi list → same order"
    print("OK: rrf_fusion A1 pass — consensus doc top, scale-free merge verified")


if __name__ == "__main__":
    _check()
