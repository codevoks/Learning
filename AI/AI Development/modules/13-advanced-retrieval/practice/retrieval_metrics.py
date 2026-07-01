"""A3 — Retrieval metrics: recall@k aur MRR (generation ke bina retrieval measure).

`python retrieval_metrics.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract (per-query lists, index i = query i):
- recall_at_k(results, relevant, k): fraction of queries jinme koi relevant doc
  top-k results mein aaya.
- mrr(results, relevant): mean of 1/(rank of FIRST relevant doc); koi relevant na
  mile to us query ka contribution 0. rank 1-based.
`results[i]` = ranked doc_ids; `relevant[i]` = us query ke relevant doc_ids (list/set).
"""


def recall_at_k(results: list[list[str]], relevant: list[list[str]], k: int) -> float:
    # TODO: har query — top-k mein koi relevant hai? fraction return karo
    raise NotImplementedError


def mrr(results: list[list[str]], relevant: list[list[str]]) -> float:
    # TODO: har query — pehle relevant ka rank → 1/rank; mean
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    results = [["d1", "d2", "d3"], ["x1", "x2", "x3"]]
    relevant = [["d2"], ["x9"]]  # q1: d2 rank 2; q2: relevant x9 absent

    assert recall_at_k(results, relevant, k=3) == 0.5, "q1 hit (top-3), q2 miss → 0.5"
    assert recall_at_k(results, relevant, k=1) == 0.0, "d2 rank 2 (top-1 nahi), q2 miss → 0.0"
    assert abs(mrr(results, relevant) - 0.25) < 1e-9, "q1=1/2, q2=0 → mean 0.25"

    perfect = [["a", "b"], ["c", "d"]]
    rel2 = [["a"], ["c"]]  # dono rank 1
    assert recall_at_k(perfect, rel2, k=1) == 1.0
    assert mrr(perfect, rel2) == 1.0
    print("OK: retrieval_metrics A3 pass — recall@k + MRR verified")


if __name__ == "__main__":
    _check()
