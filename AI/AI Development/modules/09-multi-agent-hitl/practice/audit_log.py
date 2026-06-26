"""A3 — Audit log schema + write on each agent step. Complete TODOs."""

# TODO: AuditEntry dataclass or Pydantic model
# TODO: def log_step(run_id, agent, action, payload, **meta)
# TODO: def query_trail(run_id) -> list[AuditEntry]


def log_step(run_id: str, agent: str, action: str, payload: dict, **meta) -> None:
    raise NotImplementedError
