"""M5 — Budget middleware. Complete TODOs."""

# TODO: track tokens_used per tenant_id in Redis
# TODO: def check_budget(tenant_id, estimated_tokens) -> None  # raises BudgetExceeded
# TODO: soft warn vs hard stop thresholds


class BudgetExceeded(Exception):
    status_code = 402
