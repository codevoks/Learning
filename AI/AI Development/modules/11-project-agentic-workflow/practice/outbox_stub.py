"""M5 — Outbox idempotent execution stub. Complete TODOs."""

# TODO: enqueue(event, idempotency_key) — in-memory or sqlite
# TODO: process_outbox() — execute once per key
# TODO: duplicate enqueue with same key → single side effect


def enqueue(event: dict, idempotency_key: str) -> None:
    raise NotImplementedError


def process_outbox() -> int:
    """Returns count of newly processed events."""
    raise NotImplementedError
