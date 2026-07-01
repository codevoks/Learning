"""A1 — Ek neuron ka forward pass + sigmoid activation.

`python neuron_forward.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract:
- sigmoid(x): 1 / (1 + e^-x). NumPy array/scalar dono chalein.
- neuron_forward(x, w, b): sigmoid( dot(x, w) + b ).
"""

import numpy as np


def sigmoid(x):
    # TODO: 1 / (1 + np.exp(-x))
    raise NotImplementedError


def neuron_forward(x, w, b: float):
    # TODO: sigmoid(np.dot(x, w) + b)
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    assert abs(float(sigmoid(0.0)) - 0.5) < 1e-9, "sigmoid(0) = 0.5"
    assert float(sigmoid(20.0)) > 0.999, "bada input → ~1"
    assert float(sigmoid(-20.0)) < 0.001, "bahut negative → ~0"

    x = np.array([1.0, 2.0]); w = np.array([0.5, -0.5]); b = 0.0
    # dot = 0.5 - 1.0 = -0.5 → sigmoid(-0.5) ≈ 0.377541
    assert abs(float(neuron_forward(x, w, b)) - 0.3775406688) < 1e-6, "neuron forward value"

    # zero weights + zero bias → sigmoid(0) = 0.5
    assert abs(float(neuron_forward(x, np.array([0.0, 0.0]), 0.0)) - 0.5) < 1e-9
    print("OK: neuron_forward A1 pass — sigmoid + weighted-sum forward verified")


if __name__ == "__main__":
    _check()
