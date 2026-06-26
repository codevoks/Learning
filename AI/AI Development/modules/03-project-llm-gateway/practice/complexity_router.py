"""M3 — Complexity classifier → model bucket. Complete TODOs."""

# Buckets: "haiku" | "sonnet" | "opus"

# TODO: def classify_complexity(query: str) -> str
# TODO: MODEL_MAP = { bucket: model_name }


def classify_complexity(query: str) -> str:
    raise NotImplementedError


if __name__ == "__main__":
    tests = [
        ("Hi", "haiku"),
        ("Summarize this 3-paragraph email", "sonnet"),
        ("Refactor this 200-line Python module with tests", "opus"),
    ]
    # TODO: assert routing
    pass
