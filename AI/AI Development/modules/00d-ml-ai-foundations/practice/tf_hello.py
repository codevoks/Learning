"""A3 — Tiny Keras model: train on AND gate, predict on new input."""

import numpy as np

# TODO: import tensorflow as tf


def build_and_data():
    """2-bit input → 1-bit AND output."""
    X = np.array([[0, 0], [0, 1], [1, 0], [1, 1]], dtype=np.float32)
    y = np.array([[0], [0], [0], [1]], dtype=np.float32)
    return X, y


def main():
    X, y = build_and_data()

    # TODO: Sequential model — Dense(4, relu, input_shape=(2,)) + Dense(1, sigmoid)
    model = None

    # TODO: compile — optimizer adam, loss binary_crossentropy
    # TODO: fit X, y — epochs=50, verbose=1

    # TODO: predict [[1, 1]] — print value (expect ~1.0)
    raise NotImplementedError("Complete A3 TODOs")


if __name__ == "__main__":
    main()
