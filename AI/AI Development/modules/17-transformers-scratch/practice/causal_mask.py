"""A2 — Causal (autoregressive) attention mask.

`python causal_mask.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract:
- causal_mask(seq_len) -> np.ndarray [seq_len, seq_len]:
    diagonal aur uske NEECHE (past + self) = 0.0
    diagonal ke UPAR (future) = bada negative (-inf jaisा, jaise -1e9)
  Yeh mask attention scores mein ADD hota hai — future positions softmax mein 0 ho jaate.
"""

import numpy as np


def causal_mask(seq_len: int) -> np.ndarray:
    # TODO: lower-triangle (incl diag) = 0, upper = -1e9
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    m = causal_mask(3)
    assert m.shape == (3, 3), "shape [seq, seq]"

    # diagonal + neeche = 0 (dekh sakta hai)
    assert m[0, 0] == 0.0 and m[1, 0] == 0.0 and m[1, 1] == 0.0
    assert m[2, 0] == 0.0 and m[2, 1] == 0.0 and m[2, 2] == 0.0

    # upar (future) = bada negative
    assert m[0, 1] < -1e8 and m[0, 2] < -1e8 and m[1, 2] < -1e8, "future positions masked"

    # property: har row mein allowed (0) positions = row_index + 1
    for i in range(3):
        allowed = int(np.sum(m[i] == 0.0))
        assert allowed == i + 1, f"row {i} ko {i+1} positions dikhne chahiye (past+self)"
    print("OK: causal_mask A2 pass — lower-triangular mask, future blocked")


if __name__ == "__main__":
    _check()
