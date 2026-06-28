"""A4 shared — test sentences, pair scoring, runner."""

from __future__ import annotations
from cosine_similarity import cosine_similarity

SENTENCES = [
    "How do I get a refund for my order?",
    "What is the return policy for damaged items?",
    "The weather in Mumbai is sunny today.",
]


def best_pair(vectors: list[list[float]]) -> tuple[int, int, float]:
    """Return indices (i, j) i<j with highest cosine similarity and the score."""
    # TODO: import cosine_similarity from cosine_similarity OR inline numpy
    # TODO: compare all pairs, return best
    best_score=-1e6
    best_i:int
    best_j:int
    for i in range(len(vectors)):
        for j in range(i+1,len(vectors)):
            score=cosine_similarity(vectors[i],vectors[j])
            if score>best_score:
                best_score=score
                best_i=i
                best_j=j
    return best_i, best_j, best_score
    # raise NotImplementedError


def run(embed_sentences):
    """Call after implementing embed_sentences + best_pair."""
    vectors = embed_sentences(SENTENCES)
    i, j, score = best_pair(vectors)
    print(f"Most similar: [{i}] and [{j}]")
    print(f"  {SENTENCES[i]}")
    print(f"  {SENTENCES[j]}")
    print(f"  score={score:.4f}")
    # Pass when pair is the two refund/return sentences (indices 0 and 1)
