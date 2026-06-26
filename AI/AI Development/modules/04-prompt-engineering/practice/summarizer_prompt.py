"""A1 — Fix broken summarizer prompt. Complete TODOs."""

# BROKEN_PROMPT below produces inconsistent output — fix SYSTEM_PROMPT + params

BROKEN_PROMPT = "summarize"

# TODO: SYSTEM_PROMPT with max 3 bullets, no preamble
# TODO: def summarize(text: str) -> list[str]
# TODO: temperature=0, run 10x stability test


def summarize(text: str) -> list[str]:
    raise NotImplementedError
