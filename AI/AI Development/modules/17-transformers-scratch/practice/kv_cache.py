"""A3 — KV cache: generation mein K,V dobara compute mat karo, append karo.

`python kv_cache.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract (ek layer/head ka cache):
- KVCache.append(k, v): naye token ka k, v (dono shape [1, d]) cache mein add karo.
- KVCache.get() -> (K, V): ab tak ke saare cached K, V stacked ([n, d]) return karo,
  insertion order mein.
Yeh wahi cache hai jo generation ko O(n^2) recompute se O(n) banata hai.
"""

import numpy as np


class KVCache:
    def __init__(self):
        # TODO: k aur v store karne ke liye lists/arrays
        raise NotImplementedError

    def append(self, k, v) -> None:
        # TODO: naye token ka k,v add karo
        raise NotImplementedError

    def get(self):
        # TODO: (K_all, V_all) stacked return karo
        raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    c = KVCache()
    c.append(np.array([[1.0, 2.0]]), np.array([[10.0, 20.0]]))
    K, V = c.get()
    assert K.shape == (1, 2) and V.shape == (1, 2), "ek token ke baad shape [1, d]"

    c.append(np.array([[3.0, 4.0]]), np.array([[30.0, 40.0]]))
    K, V = c.get()
    assert K.shape == (2, 2), "doosre token ke baad cache badhkar [2, d]"
    assert np.allclose(K, [[1, 2], [3, 4]]), "K insertion order mein"
    assert np.allclose(V, [[10, 20], [30, 40]]), "V insertion order mein"

    c.append(np.array([[5.0, 6.0]]), np.array([[50.0, 60.0]]))
    K, V = c.get()
    assert K.shape == (3, 2), "teesre token ke baad [3, d] — cache grow ho raha"
    print("OK: kv_cache A3 pass — append + grow (O(n) generation) verified")


if __name__ == "__main__":
    _check()
