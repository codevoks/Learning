"""A4 — Inject trace_id + token counters into structured logs. Complete the TODOs."""

import json
import logging
import uuid

# TODO: configure JSON formatter or log dict directly
# TODO: def log_llm_request(trace_id, prompt_tokens, completion_tokens, latency_ms, **extra):
# TODO: middleware pattern — generate trace_id per request, attach to context


def new_trace_id() -> str:
    return str(uuid.uuid4())


if __name__ == "__main__":
    # TODO: demo log line
    pass
