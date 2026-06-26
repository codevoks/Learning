"""M1 — NL intent → structured workflow JSON. Complete TODOs."""

from pydantic import BaseModel


class WorkflowStep(BaseModel):
    id: str
    tool: str
    args: dict
    needs_hitl: bool = False


class WorkflowPlan(BaseModel):
    trigger: str
    steps: list[WorkflowStep]


# TODO: def nl_to_workflow(nl_request: str) -> WorkflowPlan
# TODO: TEST_PHRASES list — assert 90%+ valid schema


def nl_to_workflow(nl_request: str) -> WorkflowPlan:
    raise NotImplementedError
