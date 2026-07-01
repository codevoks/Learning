# Module 11 — PROJECT: Agentic Workflow (→ Project B)

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 10](../10-evals-llmops/MODULE.md) · Next → [Module 12 (advanced)](../12-guardrails-safety/MODULE.md)
> **Ship**: **Python** agents `services/agent/` · **Go** platform from Project A (`@Projects.md` Project B).

> **Format**: Textbook — §0 terms + milestones zero se, prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`

## At a glance

| | |
|---|---|
| Prerequisites | Modules 01–10 complete. `@Projects.md` Project B padha hua |
| Duration | ~3–4 weeks (Phase 1 sandbox → Phase 2 monorepo ship) |
| Project? | **Yes — Project B** (AI Workflow Automation SaaS) |
| Exit test | M1–M7 + full architecture + CV bullets bina notes ke defend karo |

## Yeh module kis baare mein hai

Yeh capstone hai — Modules 06–10 ke saare tukde yahan **ek ship-ready system** mein judte hain. Project B ek line mein: **AI Workflow Automation SaaS** — user natural language mein automation describe kare ("har subah overdue invoices check karke client ko email karo"), agent ek plan banaye, tools connect kare, aur use **safely + exactly-once** run kare.

Tumhara **unfair advantage** yahi hai. Competitors "AI magic" bechte hain; tum "AI + ledger-grade execution" bechte ho. Tumhare Zapier-clone/payments background se outbox + Kafka + idempotency aata hai — wahi reliability story jo investors aur engineers dono samajhte hain. Billable unit `task_run` hai (ek workflow execution), aur poora pitch yahi hai: "runs are billed and executed exactly once — never dropped, never doubled."

```
User natural language → Planner (NL → WorkflowPlan JSON) → LangGraph state machine
   ├── MCP tools (Slack, DB, webhooks)
   ├── read steps → direct execute
   └── write steps → Outbox → Kafka → HITL gate → approve → execute (idempotent)
                                                      → audit log + Langfuse trace + meter 1 run
```

**Redraw challenge**: NL → plan → graph → MCP + outbox/Kafka → HITL → execute; Go platform layer alag box (auth, metering); Phase 1 vs Phase 2 label.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + milestones | `@Projects.md` Project B read |
| 2 | §1 Thesis + §2 Architecture | **M1** — `nl_to_workflow.py` |
| 3 | §3 NL → plan | **M1** pass — 90%+ valid JSON |
| 4 | §4 LangGraph linear | **M2** — `linear_workflow_graph.py` |
| 5 | §5 MCP wire | **M3** — `mcp_tools_wire.py` |
| 6 | §6 HITL | **M4** — `hitl_destructive.py` |
| 7 | §7 Outbox exactly-once | **M5** — `outbox_stub.py` |
| 8 | §8 Eval harness | **M6** — `eval_harness.py` |
| 9 | §9 Demo + §10 Phase 2 | **M7** — `demo_refund/` |
| 10 | §11 CV narrative + recall | NOTES architecture diagram |

---

## Theory

### §0. Terms pehli baar — agentic workflow, milestones

**Agentic workflow.** Ek normal "workflow" trigger + ordered steps hai (tumhara Zapier JSON jaisा). **Agentic** ka matlab steps fixed nahi — LLM khud plan karta hai kaunse tools, kis order mein. Yeh plan ek **WorkflowPlan** (Pydantic model — machine-readable) ban jaata hai. Ek **task run** uska ek execution instance hai (yahi meter hota hai), aur **destructive step** wo hai jiska side-effect ho (refund, webhook, delete).

Schema pehle samjho, kyunki poora system iske ird-gird hai:

```python
class WorkflowStep(BaseModel):
    id: str
    tool: str
    args: dict
    needs_hitl: bool = False

class WorkflowPlan(BaseModel):
    trigger: str             # "schedule_daily" | "webhook" | "manual"
    steps: list[WorkflowStep]
```

Sabse important field `needs_hitl` hai — `True` hone par wo step execute hone se *pehle* human gate pe rukता hai. Ek example plan jisme do auto steps aur ek HITL step hai:

```json
{ "trigger": "schedule_daily", "steps": [
    {"id": "s1", "tool": "query_overdue_invoices", "args": {"days": 30}, "needs_hitl": false},
    {"id": "s2", "tool": "send_email", "args": {"template": "overdue"}, "needs_hitl": false},
    {"id": "s3", "tool": "create_slack_task", "args": {"channel": "#ops"}, "needs_hitl": true}
]}
```

**Milestones (M1–M7).** Project ko ek saath banana overwhelming hai, isliye 7 ordered deliverables hain — har ek pichle pe khada:

| M | Deliverable | Ek line mein |
|---|-------------|------------------|
| M1 | NL → workflow JSON | User sentence → valid `WorkflowPlan` |
| M2 | Linear LangGraph | 3 steps order mein (no branch) |
| M3 | MCP + custom tools | External + inline tools same graph |
| M4 | HITL destructive | Write se pehle pause — approve/reject |
| M5 | Outbox exactly-once | Duplicate enqueue → single effect + single bill |
| M6 | Eval + Langfuse | Bura planner change CI mein fail |
| M7 | Refund demo E2E | Recordable walkthrough + README |

**Phase 1** (yeh module ka practice): Python AI core, single user, no Stripe. **Phase 2** (monorepo ship): Go platform wrap — auth, tenants, metering, Stripe (Project A spine reuse).

> **Ruko, socho:** Milestones ka order fixed kyun hai — agar M5 (outbox/exactly-once) ko M4 (HITL) se pehle karo to kya miss hoga? (Jawab: exactly-once ka asli imtihaan tabhi aata hai jab koi destructive step approve hoke execute hota hai. Bina HITL gate (M4) ke tumhare paas wo controlled execute-point hi nahi jise idempotent banana hai — order intentional hai.)

**§0 checkpoint:** (1) Billable unit kya hai? (2) M1 vs M7 — ek sentence each? (3) `needs_hitl: true` runtime pe kya karta hai?

---

### §1. Project B thesis — yeh project tumhare liye kyun

Kaun pay karega: ops teams, solo founders — jo manual multi-step kaam automate karna chahte hain. Tum kyun jeetoge: **exactly-once execution + billing** — yeh tumhara payments background hai, tutorial code nahi. Yahi differentiation interview narrative banata hai, jise tum 7 steps mein bata sakte ho: user NL mein describe karta hai → planner validated plan banata hai → LangGraph MCP tools se execute karta hai → destructive steps HITL pe rukte hain → outbox once-only side-effect ensure karta hai → eval CI planner regressions pakadta hai → Phase 2 mein per-tenant meter Stripe se jodता hai.

---

### §2. End-to-end architecture — polyglot

Poora system do languages mein bantа hai (00e waala split). Request ka flow:

```
1.  User NL message platform pe (Phase 2: API key) — ya Phase 1 mein CLI
2.  Planner LLM → WorkflowPlan JSON
3.  Pydantic validate — invalid plan fail-fast, koi partial run nahi
4.  LangGraph compile — steps as nodes
5.  Read steps inline run
6.  Destructive step → outbox row, run-state ke SAME transaction mein
7.  Worker Kafka se → HITL queue
8.  Approve → execute with idempotency_key
9.  Exactly ek task_run meter (Phase 2)
10. Langfuse trace + audit log complete
```

Phase 1 aur Phase 2 ka farak yaad rakho: entry Phase 1 mein FastAPI/CLI direct hai, Phase 2 mein Go platform (auth, tenant) ke through; metering Phase 1 mein sirf log, Phase 2 mein idempotent usage events → Stripe; credentials Phase 1 mein `.env`, Phase 2 mein per-tenant encrypted vault; HITL UI Phase 1 mein CLI stub, Phase 2 mein Next.js dashboard. Monorepo mein yeh `apps/web/` (UI), `platform/` (Go spine), `services/agent/` (yeh module ka output) ban jaata hai.

---

### §3. M1 — NL → structured workflow plan

Raw LLM text ko execute nahi kar sakte — usse pehle ek **schema** chahiye jise tum validate kar sako. Yahi M1 hai. Planner prompt ke teen rules: sirf allowlisted tools use kare, writes/payments/webhooks pe `needs_hitl: true` set kare, aur JSON-only de (no markdown). Code seedha hai (Module 06 structured output + Pydantic):

```python
def nl_to_workflow(nl_request: str) -> WorkflowPlan:
    raw = call_planner_llm(nl_request, TOOL_ALLOWLIST)   # structured output
    return WorkflowPlan.model_validate_json(raw)          # invalid → ValidationError, no partial run
```

Asli kaam validation gate hai — agar plan invalid hai, user ko error do, koi adhura run mat chalao. M1 ka pass criteria ek `TEST_PHRASES` list pe **90%+ valid schema** hai:

```python
def eval_m1() -> float:
    ok = sum(1 for p in TEST_PHRASES if try_parse(p))
    return ok / len(TEST_PHRASES)
```

Do baatein jo aksar tooti hain: LLM markdown fence (```) ke andar JSON de deta hai (fix: `response_format` schema), aur destructive step pe `needs_hitl` set karna bhool jaata hai (fix: prompt mein destructive examples). Doosra wala security-critical hai — agar refund step `needs_hitl: false` aa gaya to HITL gate bypass ho jaayega.

> **→ Practice M1** (pass: 90%+ on `TEST_PHRASES`).

---

### §4. M2 — LangGraph linear 3-step workflow

Plan ban gaya — ab execute karna hai. Pehle **linear** (branch baad mein): ek node steps ke through iterate karta hai jab tak sab khatam na ho:

```python
class RunState(TypedDict):
    plan: WorkflowPlan
    current_step: int
    step_results: dict
    messages: list

def execute_step_node(state: RunState) -> dict:
    step = state["plan"].steps[state["current_step"]]
    result = run_tool(step.tool, step.args)
    return {"current_step": state["current_step"] + 1,
            "step_results": {**state["step_results"], step.id: result}}

def should_continue(state: RunState) -> Literal["execute_step", "__end__"]:
    return "__end__" if state["current_step"] >= len(state["plan"].steps) else "execute_step"
```

`current_step` ek index hai jo linear iterator ki tarah kaam karta hai, aur `step_results` har step ka output accumulate karta hai (partial update se merge, Module 07). Conditional edge loop banaता hai jab tak saare steps na ho jaayein. Yeh Zapier ka sequential-actions hi hai — step 2 tabhi jab step 1 success.

> **→ Practice M2** (pass: 3-step end-to-end complete).

---

### §5. M3 — MCP integration + custom tools

Saare tools Python mein rakhna theek nahi — generic integrations (Slack, GitHub) MCP servers mein, tumhari domain logic local mein. `run_tool` dono ko route karta hai:

```python
async def run_tool(name: str, args: dict) -> str:
    if name in MCP_TOOLS:
        return await mcp_session.call_tool(name, args)   # shared MCP server
    if name in LOCAL_TOOLS:
        return LOCAL_TOOLS[name](**args)                 # tumhari business logic
    raise ValueError(f"Unknown tool: {name}")
```

Decision rule: generic cheezein (`slack_post`, `write_webhook`) MCP se (reusable, alag credentials); tumhari domain SQL (`query_overdue_invoices`) local (business logic, fast). Ek credential rule jo Phase 2 mein critical hai — API keys **vault** se MCP server ke env mein inject karo, **kabhi prompt mein nahi**. Aur do MCP servers ke tool names takra sakte hain, to prefix lagao (`slack_`, `db_`).

> **→ Practice M3** (pass: MCP + local dono kaam karein).

---

### §6. M4 — HITL on destructive steps

`write_webhook`, `issue_refund` jaise steps bina human ke chalna OWASP LLM06 (excessive agency) hai. Route function plan ke `needs_hitl` flag ko padhkar destructive steps ko gate pe bhejta hai:

```python
def route_step(state: RunState) -> Literal["execute_step", "hitl_gate", "__end__"]:
    if state["current_step"] >= len(state["plan"].steps):
        return "__end__"
    step = state["plan"].steps[state["current_step"]]
    return "hitl_gate" if step.needs_hitl else "execute_step"

app = graph.compile(checkpointer=memory, interrupt_before=["hitl_gate"])
```

Flow (Module 09): graph `hitl_gate` pe pause hota hai aur UI proposal dikhata hai → human approve kare to us step ka `execute_step` chale → reject kare to `replan` (planner dobara ya user edit). Practice mein sync CLI `approve y/n`; production mein web approval queue. Ek baat jo M5 se judti hai — approve pe resume karte waqt **double-execute** ka risk hai, jise idempotency key (agla section) rokта hai.

> **→ Practice M4** (pass: reject → replan trigger ho).

---

### §7. M5 — Outbox + Kafka exactly-once execution

Yeh tumhara signature module hai. Problem: worker crash ya retry pe duplicate webhook = duplicate refund = **double billing** — ek SaaS ko maar dene wali cheez. Tumhara Zapier-clone wala outbox pattern yahi solve karta hai. Intent ko run-state ke **same transaction** mein durable karo:

```python
def enqueue_execute(step_id: str, run_id: str, idempotency_key: str):
    with db.transaction():
        db.execute("UPDATE workflow_runs SET status=%s WHERE id=%s", ("pending", run_id))
        db.execute("INSERT INTO outbox (event_type, payload, idempotency_key) VALUES (%s, %s, %s)",
                   ("execute_step", {"step_id": step_id, "run_id": run_id}, idempotency_key))

def worker_execute(idempotency_key: str, fn):
    if db.exists("processed_keys", idempotency_key):
        return db.get("processed_keys", idempotency_key)   # already done — same result, no-op
    result = fn()
    db.insert("processed_keys", idempotency_key, result)
    return result
```

Teen layers milkar exactly-once dete hain: **outbox** intent ko state ke saath atomically durable karta hai (event kabhi lost nahi, kyunki same TX); **Kafka** use deliver karta hai; aur **idempotency_key** ensure karta hai effect ek hi baar ho (worker do baar bhi process kare to doosri baar no-op). Aur yahi key family **billing** se judti hai — har execute exactly ek `task_run` meter karta hai, isliye duplicate Stripe charge nahi. Interview line: "outbox makes intent durable; Kafka delivers; idempotency_key makes the effect once — billing uses the same key family."

> **Ruko, socho:** Agar tum outbox INSERT ko run-state UPDATE se **alag** transaction mein karo, to kaunsa failure window khulta hai? (Jawab: agar state update commit ho jaaye par outbox insert se pehle crash ho, to run "pending" dikhega par koi event enqueue nahi hua — step kabhi execute nahi hoga (lost). Dono ek hi TX mein hone se yeh gap band hota hai — yahi outbox pattern ka poora point hai.)

> **→ Practice M5** (pass: duplicate enqueue → single side effect).

---

### §8. M6 — Eval harness + Langfuse

Planner prompt ka ek chhota tweak silently M1 ko 90% se 70% gira sakta hai, aur kisi ko pata nahi chalega. Eval harness (Module 10) isе CI mein pakadta hai — golden NL phrases pe planner chalाo aur pass-rate measure karo:

```python
def eval_planner_regression() -> dict:
    results = [validate_plan(nl_to_workflow(c["input"]), c) for c in golden_cases]
    return {"pass_rate": sum(results) / len(results), "details": results}
```

Outcome ke saath **trajectory eval** bhi (Module 10 §2) — `expected_steps = ["query_overdue", "send_email", "hitl", "slack_post"]` ko actual tool-sequence se match karo, taaki HITL skip jaisी process-galti pakdi jaaye. Langfuse har run pe `prompt_version`, `plan_hash`, `cost_usd`, `trajectory_match` track karta hai (dashboard: cost per task, p99, fail reasons). CI gate: `eval_harness.py` exit 1 jab pass-rate baseline-minus-delta se kam.

> **→ Practice M6** (pass: jaanboojhke bura plan harness mein fail kare).

---

### §9. M7 — Refund workflow demo E2E

Portfolio ko ek **recordable story** chahiye, aur fintech domain tumhara ghar hai. Demo script: user kahe "If order o_99 charge disputed, partial refund 50% after approval" → planner ek plan banaye jisme `get_order`, `propose_refund` (HITL), `execute_refund` hon → graph chale, HITL pe ruke, approve ho → outbox se single execution → audit log + Langfuse trace dikhe. README mein architecture diagram (redraw waala), `./run_demo.sh` steps, aur measured numbers (latency, cost, eval pass-rate — Phase 1 mein placeholder OK) hon. Demo flake se bachne ke liye `temperature=0` + stub option rakho.

> **→ Practice M7** (pass: runnable demo + README).

---

### §10. Phase 2 wrap — Go platform spine

Practice sandbox single-user hai. Ship ke liye Project A ka Go spine reuse karo: multi-tenancy (runs per-org isolated), usage metering (`task_run` idempotent count), Stripe metered billing (monthly invoice by runs), per-tenant budget (LLM spend hard stop), aur credential vault (MCP secrets per tenant). Ek important rule — **codebase restart mat karo**; practice code ko `services/agent/` mein move karke Go platform se wrap karo.

```
User → Go API (auth) → Python agent (internal) → meter task_run (exactly once with execution)
```

---

### §11. CV narrative — 3 defendable bullets

Yeh shape hai (Projects.md se; numbers actually measure karke replace karo):

1. "Built a multi-tenant AI workflow SaaS on Postgres outbox + Kafka with **exactly-once execution and billing**, human-in-the-loop checkpoints, least-privilege MCP tools, and a per-tenant credential vault; metered N task runs with zero double-billing."
2. "LangGraph orchestration + MCP integrations; **trajectory eval in CI** blocked planner regressions; Langfuse cost-per-task tracking."
3. "Refund workflow demo — HITL + audit trail + idempotent execute — domain-grounded fintech automation."

Har bullet ke peeche poora ek module hai jise tum 10 min mein whiteboard kar sakte ho — yahi defendability hai.

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Learning sandbox; ship `@Projects.md` Project B.
> Stuck? `@modules/11-project-agentic-workflow/MODULE.md @Projects.md`

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| M1 | §3 | `nl_to_workflow.py` | 90%+ valid on test phrases |
| M2 | §4 | `linear_workflow_graph.py` | 3-step E2E |
| M3 | §5 | `mcp_tools_wire.py` | MCP + local tools |
| M4 | §6 | `hitl_destructive.py` | Reject → replan |
| M5 | §7 | `outbox_stub.py` | Duplicate → single effect |
| M6 | §8 | `eval_harness.py` | Bad plan CI mein fail |
| M7 | §9 | `demo_refund/` | Recordable demo + README |

---

## Active recall (khud jawab likho NOTES mein)

1. Outbox exactly-once aur billing guarantee kaise jude hain — 3 sentences?
2. HITL destructive steps pe mandatory kyun — compliance + safety?
3. M1→M7 order fixed kyun — M5 pehle karoge to kya miss?
4. Phase 1 vs Phase 2 — kya reuse, kya naya?
5. CV ke 3 bullets apne shabdon mein.

**Chat drill** (optional): "Module 11 — full architecture + outbox whiteboard."

---

## Progress checklist

- [ ] §0 milestones map samjha
- [ ] `@Projects.md` Project B read
- [ ] Practice M1–M7 pass
- [ ] Redraw challenge — Go + Python boxes
- [ ] Active recall NOTES
- [ ] NOTES: architecture diagram + eval scores + demo link
- [ ] Phase 2 plan noted

---

## Optional appendix

- [`@Projects.md` Project B](../../Projects.md) — full ship spec
- [Transactional outbox pattern](https://microservices.io/patterns/data/transactional-outbox.html)
- Modules 07–10 — building blocks · Project A spine — Phase 2 prerequisite
