"""A1 — Cosine similarity between two vectors. Complete the TODOs."""

import numpy as np

# Test vectors — do not change
VEC_A = np.array([1.0, 0.0, 0.0])
VEC_B = np.array([0.9, 0.1, 0.0])
VEC_ORTHO = np.array([0.0, 1.0, 0.0])


def cosine_similarity(a: np.ndarray, b: np.ndarray) -> float:
    """
    Return cosine similarity between a and b.
    Formula: dot(a, b) / (norm(a) * norm(b))
    """
    # TODO: implement using np.dot and np.linalg.norm
    return np.dot(a,b)/(np.linalg.norm(a)*np.linalg.norm(b))
    # raise NotImplementedError


def _check():
    sim_ab = cosine_similarity(VEC_A, VEC_B)
    sim_ortho = cosine_similarity(VEC_A, VEC_ORTHO)
    sim_self = cosine_similarity(VEC_A, VEC_A)

    print(f"A·B ≈ high: {sim_ab:.4f} (expect > 0.9)")
    print(f"A·ortho ≈ 0: {sim_ortho:.4f}")
    print(f"A·A = 1: {sim_self:.4f}")

    # TODO: assert sim_self close to 1.0, sim_ortho close to 0.0
    assert abs(sim_self-1.0)<1e-6
    assert abs(sim_ortho-0.0)<1e-6


if __name__ == "__main__":
    _check()
