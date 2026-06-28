"""A4 Option B — local sentence-transformers (no API key)."""

from __future__ import annotations

from embeddings_common import run
from sentence_transformers import SentenceTransformer

model = SentenceTransformer("sentence-transformers/all-MiniLM-L6-v2")


def embed_sentences(texts: list[str]) -> list[list[float]]:
    """Return one embedding vector per text via local model."""
    # TODO:
    #   from sentence_transformers import SentenceTransformer
    #   model = SentenceTransformer("all-MiniLM-L6-v2")
    #   return model.encode(texts).tolist()
    return model.encode(texts)
    # raise NotImplementedError("Implement embed_sentences (local)")


if __name__ == "__main__":
    run(embed_sentences)
