"""A2 — Maximal Marginal Relevance: relevance + diversity balance karke top-k.

`python mmr_rerank.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract:
- mmr(query, docs, k, lambda_=0.5): `query` ek vector (list[float]); `docs` dict
  {doc_id: vector}. Har step pe wo doc pick karo jo yeh maximize kare:
      lambda_ * relevance(doc, query) - (1 - lambda_) * max_sim(doc, already_picked)
  relevance/sim = cosine similarity. k docs ki ORDERED list return karo.
Hint: numpy cosine. Pehla pick sirf relevance se (kuch selected nahi).
"""

import numpy as np


def _cos(a, b) -> float:
    a, b = np.asarray(a, float), np.asarray(b, float)
    return float(np.dot(a, b) / (np.linalg.norm(a) * np.linalg.norm(b)))


def mmr(query, docs: dict, k: int, lambda_: float = 0.5) -> list[str]:
    # TODO: greedy MMR selection — upar ka formula
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    query = [1.0, 0.0]
    docs = {
        "a":  [0.90, 0.20],   # sabse relevant
        "a2": [0.85, 0.25],   # a ka near-duplicate (redundant)
        "b":  [0.25, 0.90],   # kam relevant par diverse
        "c":  [0.10, 0.99],   # aur diverse
    }
    # lambda_ chhota = diversity ko zyada weight (redundant docs avoid)
    picked = mmr(query, docs, k=2, lambda_=0.3)
    assert len(picked) == 2, "k=2 docs milne chahiye"
    assert picked[0] == "a", f"sabse relevant 'a' pehle, mila {picked[0]}"
    # diversity: doosra pick 'a2' (redundant near-dup) nahi hona chahiye
    assert "a2" not in picked, "MMR ko redundant near-duplicate 'a2' avoid karna chahiye"
    assert picked[1] in ("b", "c"), f"doosra pick diverse hona chahiye, mila {picked[1]}"
    print("OK: mmr_rerank A2 pass — top relevant + diversity (redundant dropped)")


if __name__ == "__main__":
    _check()
