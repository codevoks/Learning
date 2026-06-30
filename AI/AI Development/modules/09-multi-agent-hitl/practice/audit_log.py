"""A3 — Audit log: har agent step record karo, run_id se trail query karo.

`python audit_log.py` → `_check()` ke asserts pass hone chahiye. Harness edit
mat karo; sirf functions + storage bharo.

Contract:
- log_step(run_id, agent, action, payload, **meta): ek entry _LOG mein append
  karo jisme kam se kam run_id, agent, action, payload, aur ek timestamp ho.
- query_trail(run_id): sirf us run_id ki entries, insertion order mein, return karo.
"""

# In-memory audit store (production: Postgres append-only table)
_LOG: list[dict] = []


def log_step(run_id: str, agent: str, action: str, payload: dict, **meta) -> None:
    # TODO: _LOG.append({...run_id, agent, action, payload, timestamp, **meta})
    raise NotImplementedError


def query_trail(run_id: str) -> list[dict]:
    # TODO: _LOG se sirf is run_id ki entries (order preserve karte hue)
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    _LOG.clear()
    log_step("r1", "supervisor", "route", {"to": "executor"})
    log_step("r2", "executor", "refund", {"amount": 50})
    log_step("r1", "executor", "send_email", {"to": "a@b.com"}, hitl_status="approved")

    trail = query_trail("r1")
    assert len(trail) == 2, f"r1 ki 2 entries chahiye, mili {len(trail)}"
    assert [e["action"] for e in trail] == ["route", "send_email"], "order preserve hona chahiye"
    assert all(e["run_id"] == "r1" for e in trail), "doosre run ki entry leak na ho"
    assert all("timestamp" in e for e in trail), "har entry mein timestamp ho"
    assert query_trail("does-not-exist") == [], "unknown run_id → empty list"

    print("OK: audit_log A3 pass — per-run trail, order + isolation verified")


if __name__ == "__main__":
    _check()
