"""A1 — Mini tokenizer scratch se (encode/decode + special tokens).

`python mini_tokenizer.py` → `_check()` ke asserts pass. Harness edit mat karo.
(Real tokenizers BPE use karte — yeh word-level chhota version concept ke liye.)

Contract:
- __init__(self, vocab): `vocab` = {word: id}. Iske BAAD 3 special tokens add karo —
  <bos>, <eos>, <unk> — naye ids ke saath, aur set: self.bos_id, self.eos_id,
  self.unk_id. Reverse map (id→word) bhi banao.
- encode(text): text ko space pe split; [bos_id] + [word ka id ya unk_id agar OOV] + [eos_id].
- decode(ids): non-special ids ko words mein badlo, space se join. Special tokens skip.
"""


class MiniTokenizer:
    def __init__(self, vocab: dict):
        # TODO: word2id = dict(vocab); specials add karo; bos_id/eos_id/unk_id set; id2word banao
        raise NotImplementedError

    def encode(self, text: str) -> list[int]:
        # TODO: [bos] + ids (unk for OOV) + [eos]
        raise NotImplementedError

    def decode(self, ids: list[int]) -> str:
        # TODO: non-special ids → words, space-joined
        raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    tok = MiniTokenizer({"hello": 0, "world": 1, "rag": 2})
    ids = tok.encode("hello world")
    assert ids[0] == tok.bos_id, "pehla token <bos>"
    assert ids[-1] == tok.eos_id, "aakhri token <eos>"
    assert ids[1:-1] == [0, 1], "hello world → [0, 1]"
    assert tok.decode(ids) == "hello world", "round-trip (specials stripped) original dena chahiye"

    oov = tok.encode("hello foobar")
    assert tok.unk_id in oov, "OOV word (foobar) → unk_id"

    # specials distinct hone chahiye
    assert len({tok.bos_id, tok.eos_id, tok.unk_id}) == 3, "3 distinct special ids"
    print("OK: mini_tokenizer A1 pass — encode/decode round-trip + special tokens verified")


if __name__ == "__main__":
    _check()
