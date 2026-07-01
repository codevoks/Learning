"""A2 — Ek open model chalao (HuggingFace pipeline ya Ollama).

Yeh assignment model-dependent hai (download + compute) — koi offline `_check()` nahi.
Ek chhota instruct model uthao (jaise Qwen2.5-0.5B-Instruct) taaki laptop pe chal jaaye.

Contract:
- generate(prompt, max_new_tokens=40) -> str: model se text generate karke return karo.
  Option A (transformers pipeline): pipeline("text-generation", model=...).
  Option B (AutoModel + AutoTokenizer): full control (tokenize → generate → decode).
  Option C (Ollama): local `ollama run` + HTTP call.

Bonus: dono pipeline aur AutoModel version likho, aur NOTES mein farak likho
(kaunsa easy, kaunsa control). Tokenizer round-trip (`decode(encode(x))`) bhi verify karo.
"""


def generate(prompt: str, max_new_tokens: int = 40) -> str:
    # TODO: transformers pipeline ya AutoModel ya Ollama se text generate
    raise NotImplementedError


if __name__ == "__main__":
    print("A2 ko transformers/Ollama ke saath chalao (README setup dekho).")
    print("Chhota instruct model use karo taaki laptop pe chal jaaye.")
