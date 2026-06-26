"""A4 — Embed 3 sentences and find the most similar pair."""

from __future__ import annotations

# TODO: pick ONE approach — OpenAI API OR sentence-transformers (local)

SENTENCES = [
    "How do I get a refund for my order?",
    "What is the return policy for damaged items?",
    "The weather in Mumbai is sunny today.",
]


def embed_sentences(texts: list[str]) -> list[list[float]]:
    """Return one embedding vector per text."""
    # Option A — OpenAI:
    #   from openai import OpenAI
    #   client = OpenAI()  # needs OPENAI_API_KEY in .env
    #   resp = client.embeddings.create(model="text-embedding-3-small", input=texts)
    #   return [d.embedding for d in resp.data]

    # Option B — local:
    #   from sentence_transformers import SentenceTransformer
    #   model = SentenceTransformer("all-MiniLM-L6-v2")
    #   return model.encode(texts).tolist()

    raise NotImplementedError("Implement embed_sentences")


def best_pair(vectors: list[list[float]]) -> tuple[int, int, float]:
    """Return indices (i, j) i<j with highest cosine similarity and the score."""
    # TODO: import cosine_similarity from cosine_similarity OR inline numpy
    # TODO: compare all pairs, return best
    raise NotImplementedError


def main():
    vectors = embed_sentences(SENTENCES)
    i, j, score = best_pair(vectors)
    print(f"Most similar: [{i}] and [{j}]")
    print(f"  {SENTENCES[i]}")
    print(f"  {SENTENCES[j]}")
    print(f"  score={score:.4f}")
    # Pass when pair is the two refund/return sentences (indices 0 and 1)


if __name__ == "__main__":
    main()
