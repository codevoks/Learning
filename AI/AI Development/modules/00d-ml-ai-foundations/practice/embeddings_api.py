"""A4 Option A — OpenAI embeddings API (needs OPENAI_API_KEY in .env)."""

from __future__ import annotations

from embeddings_common import run


def embed_sentences(texts: list[str]) -> list[list[float]]:
    """Return one embedding vector per text via OpenAI API."""
    # TODO:
    #   from openai import OpenAI
    #   from dotenv import load_dotenv
    #   load_dotenv()
    #   client = OpenAI()
    #   resp = client.embeddings.create(model="text-embedding-3-small", input=texts)
    #   return [d.embedding for d in resp.data]
    raise NotImplementedError("Implement embed_sentences (OpenAI)")


if __name__ == "__main__":
    run(embed_sentences)
