"""A2 — Gradient descent: ek function ka minimum dhoondho.

`python gradient_descent.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract:
- gradient_descent(grad, x0, lr=0.1, steps=100) -> float:
  x = x0 se shuru; har step: x = x - lr * grad(x). `steps` baad final x return karo.
  (grad ek function hai jo x pe loss ka gradient deta hai.)
"""


def gradient_descent(grad, x0: float, lr: float = 0.1, steps: int = 100) -> float:
    # TODO: loop — x = x - lr * grad(x)
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    # f(x) = (x - 3)^2  → grad = 2(x - 3), minimum x = 3
    g1 = lambda x: 2 * (x - 3)
    x = gradient_descent(g1, x0=0.0, lr=0.1, steps=200)
    assert abs(x - 3.0) < 1e-3, f"minimum 3 pe converge hona chahiye, mila {x}"

    # f(x) = (x + 2)^2 → minimum x = -2
    g2 = lambda x: 2 * (x + 2)
    x2 = gradient_descent(g2, x0=5.0, lr=0.1, steps=200)
    assert abs(x2 + 2.0) < 1e-3, f"minimum -2 pe converge, mila {x2}"

    # sanity: 0 steps → x0 wapas
    assert gradient_descent(g1, x0=1.5, lr=0.1, steps=0) == 1.5, "0 steps → x0"
    print("OK: gradient_descent A2 pass — dono functions minimum pe converge")


if __name__ == "__main__":
    _check()
