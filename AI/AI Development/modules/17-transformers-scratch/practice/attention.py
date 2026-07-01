"""A1 — Scaled dot-product self-attention (transformer ka dil).

`python attention.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract:
- attention(Q, K, V, mask=None) -> (output, weights):
    scores  = Q @ K.T / sqrt(d)           # d = Q ki last dimension
    if mask is not None: scores = scores + mask   # (mask mein future = -inf)
    weights = softmax(scores, last axis)   # har row sum = 1
    output  = weights @ V
  Q,K shape [seq, d]; V shape [seq, dv]. Return (output [seq, dv], weights [seq, seq]).
Hint: stable softmax (row-wise max subtract).
"""

import numpy as np


def attention(Q, K, V, mask=None):
    # TODO: scaled dot-product attention (upar ka formula)
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    Q = np.array([[1.0, 0.0], [0.0, 1.0]])
    out, w = attention(Q, Q, Q)
    assert out.shape == (2, 2), f"output shape [seq, dv] galat: {out.shape}"
    assert w.shape == (2, 2), f"weights shape [seq, seq] galat: {w.shape}"
    assert np.allclose(w.sum(axis=1), 1.0), "har query ke attention weights sum = 1"

    # causal-style mask: token 0 token 1 ko na dekhe (-inf)
    mask = np.array([[0.0, -1e9], [0.0, 0.0]])
    out2, w2 = attention(Q, Q, Q, mask=mask)
    assert w2[0, 1] < 1e-6, "masked position ka weight ~0 hona chahiye"
    assert abs(w2[0, 0] - 1.0) < 1e-6, "token 0 poora khud pe attend kare"
    assert np.allclose(w2.sum(axis=1), 1.0), "mask ke baad bhi rows sum 1"

    # output = values ka weighted mix (masked row 0 → V[0] exactly)
    V = np.array([[10.0, 20.0], [30.0, 40.0]])
    o3, _ = attention(Q, Q, V, mask=mask)
    assert np.allclose(o3[0], [10.0, 20.0]), "row0 sirf V[0] se bane"
    print("OK: attention A1 pass — scaled dot-product + softmax + mask verified")


if __name__ == "__main__":
    _check()
