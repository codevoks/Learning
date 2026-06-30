"""A1 — Document chunker with overlap.

Tumhe DO functions implement karne hain (TODO). Niche `_check()` ek runnable
test harness hai — `python chunker.py` chalao, jab tak saare asserts pass na
hon tab tak A1 done nahi. (Harness ko chhedna mat; sirf functions bharo.)
"""

from pathlib import Path


def load_document(path: str) -> str:
    """File ka poora text return karo (UTF-8). Missing file pe clear error."""
    # TODO: Path(path).read_text(...) — encoding handle karo
    raise NotImplementedError


def chunk_text(text: str, chunk_size: int = 500, overlap: int = 50) -> list[str]:
    """
    `text` ko overlapping chunks mein todo.
    - har chunk <= chunk_size characters
    - consecutive chunks `overlap` characters share karein (boundary word na kate)
    - poora text cover ho (koi character drop na ho)
    Guard: chunk_size <= overlap → ValueError.
    """
    # TODO: while-loop, start = end - overlap (MODULE.md §3 dekho)
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA — yeh harness pass hona chahiye (ise edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    text = "x" * 90 + "NEEDLE" + "y" * 104  # NEEDLE ek chunk-boundary pe baithega
    parts = chunk_text(text, chunk_size=100, overlap=20)

    assert len(parts) > 1, "ek se zyada chunk milne chahiye"
    assert all(len(p) <= 100 for p in parts), "koi chunk chunk_size se bada nahi"
    # overlap: agle chunk ka start = pichle chunk ke aakhri `overlap` chars
    assert parts[0][-20:] == parts[1][:20], "consecutive chunks 20 chars overlap karein"
    # boundary word poora kisi chunk mein dikhe (overlap >= len('NEEDLE'))
    assert any("NEEDLE" in p for p in parts), "boundary word overlap ki wajah se whole milna chahiye"
    # coverage: bina overlap ke jodo to poora text wapas aaye
    rebuilt = parts[0] + "".join(p[20:] for p in parts[1:])
    assert rebuilt == text, "chunks jodne pe original text wapas aana chahiye (koi char drop nahi)"

    try:
        chunk_text("abc", chunk_size=10, overlap=10)
        raise AssertionError("chunk_size <= overlap pe ValueError aana chahiye tha")
    except ValueError:
        pass

    print("OK: chunker A1 pass —", len(parts), "chunks, overlap + coverage verified")


if __name__ == "__main__":
    _check()
