"""A3 — Softmax + cross-entropy (attention aur classification dono ka core).

`python softmax_ce.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract:
- softmax(logits): probabilities jo sum = 1. NUMERICALLY STABLE — pehle max
  subtract karo (warna bade logits pe np.exp overflow).
- cross_entropy(probs, label_idx): -log(probs[label_idx]).
"""

import numpy as np


def softmax(logits):
    # TODO: stable softmax — exp(logits - max) / sum
    raise NotImplementedError


def cross_entropy(probs, label_idx: int) -> float:
    # TODO: -log(probs[label_idx])
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    p = softmax(np.array([1.0, 1.0, 1.0]))
    assert abs(float(np.sum(p)) - 1.0) < 1e-9, "probabilities sum = 1"
    assert np.allclose(p, [1 / 3, 1 / 3, 1 / 3]), "equal logits → uniform"

    # numerical stability: bade logits pe overflow/nan nahi
    big = softmax(np.array([1000.0, 0.0, 0.0]))
    assert not np.any(np.isnan(big)), "bade logits pe NaN nahi (max subtract kiya?)"
    assert big[0] > 0.99, "sabse bada logit → sabse zyada prob"

    # cross-entropy: sahi label (high prob) → chhota loss; galat → bada
    probs = softmax(np.array([2.0, 1.0, 0.0]))
    loss_right = cross_entropy(probs, 0)   # highest-prob class
    loss_wrong = cross_entropy(probs, 2)   # lowest-prob class
    assert loss_right < loss_wrong, "sahi label ka loss kam hona chahiye"
    assert loss_right > 0, "loss positive"
    print("OK: softmax_ce A3 pass — stable softmax + cross-entropy verified")


if __name__ == "__main__":
    _check()
