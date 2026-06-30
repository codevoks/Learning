# Module 09 — Multi-Agent & Human-in-the-Loop

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 08](../08-mcp/MODULE.md) · Next → [Module 10](../10-evals-llmops/MODULE.md)

> **Format**: Textbook — §0 terms zero se, prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`

## At a glance

| | |
|---|---|
| Prerequisites | Module 07 (LangGraph) + 08 (MCP tools). 06 structured outputs |
| Duration | ~4–6 sessions |
| Project? | No (Project B HITL gates — Module 11 M4) |
| Exit test | Supervisor routing + HITL interrupt flow bina notes ke whiteboard karo |

## Yeh module kis baare mein hai

Do ideas yahan judti hain. Ek — **multi-agent**: ek hi mega-agent ko 20 tools dene ke bajaye, kaam ko alag-alag *roles* mein baant do (supervisor, researcher, executor), har ek ke paas limited tools aur focused prompt. Do — **Human-in-the-Loop (HITL)**: koi irreversible ya high-risk action ($50,000 refund, data delete) se pehle **human ki approval** mandatory banao. Yeh dono production-grade agentic systems ki neev hain, aur tumhare payment-system background se seedhe baith jaate hain.

```
User task → Supervisor (routes)
              ├── Researcher (read-only tools)
              └── Executor (write tools)
                        ↓
                  [HITL GATE] ──approve──► execute irreversible action
                        └── reject → rollback → supervisor replan
```

**Redraw challenge**: Planner → 2 workers → HITL gate → execute; reject arrow wapas planner; audit log kahan likhte ho mark karo.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + §1 Problem | Socho: kaunse actions bina human ke nahi chalne chahiye |
| 2 | §2 Supervisor pattern | **A1** — `supervisor_router.py` |
| 3 | §3 Specialist agents | **A1** complete — 8/10 routing |
| 4 | §4 HITL gates | **A2** — `hitl_gate.py` |
| 5 | §5 Audit + rollback | **A3** — `audit_log.py` |
| 6 | §6 Production patterns | Recall + redraw |

---

## Theory

### §0. Terms pehli baar — multi-agent, HITL

**Multi-agent — ek LLM sab kyun nahi.** Ek single mega-agent ke teen problems hain: prompt mein 20 tools daloge to LLM confuse ho ke galat tool pick karega; ek hi (mehenga) model har kaam karega (Opus se "hello" route karna paisa jalana hai); aur blame mushkil — kaunse step ne galat refund kiya, pata nahi. Iska ilaaj kaam ko roles mein baantna hai. Typical team: **Supervisor** (route + synthesize, usually no writes), **Researcher** (facts gather, read-only tools), **Executor** (side-effects, write tools), aur optional **Critic** (output review, koi external IO nahi). Yeh bilkul tumhare Kafka orchestrator + domain microservices jaisा hai.

**HITL — Human-in-the-Loop.** Irreversible ya high-risk action se pehle human approval mandatory. Bina HITL: agent → `send_refund($50,000)` → done (disaster). HITL ke saath: agent → refund **propose** kare → **PAUSE** → human OK → tab execute. Tumhare payment system mein bada refund manager-approval queue mein jaata tha aur sign-off ke baad hi settle hota — yahi cheez. LangGraph mein `interrupt_before` graph ko pause karta hai, state save karta hai, aur UI se approve/reject karke resume.

Kuch aur shabd: **handoff** (ek agent ka output doosre ka input), **interrupt** (LangGraph API jo run pause karke checkpoint persist kare), **resume** (approve/reject ke baad graph aage), aur **audit trail** (har step ka JSON log — interview defence aur "yeh refund kyun hua" ka jawab).

> **Ruko, socho:** HITL sirf "slow/careful" workflows ke liye hai, ya safety ke liye bhi? (Jawab: dono — par primary safety hai. Iska maqsad sirf user ko intimate karna nahi, balki ek irreversible action ko ek human checkpoint ke peeche rokna hai. Refund execute hone se *pehle* ruकna hi poora point hai.)

**§0 checkpoint:** (1) Multi-agent kab zaroori — 2 reasons? (2) HITL safety ya speed? (3) Handoff example — researcher se executor ko kya milta hai?

---

### §1. Problem pehle — ek agent + 15 tools production mein

Project B mein user kahega: "Overdue invoice pe email bhejo, Slack task banao, aur agar amount > 10k ho to refund initiate karo." Ek single agent ke saath teen khतре: refund tool galti se email step pe chal jaaye; $10k refund bina kisi approval ke ho jaaye; aur debugging me 40 tool calls ek thread mein ulajh jaayein.

Solution ek payment-system jaisा architecture hai: **supervisor** task todta/route karta hai → **researcher** sirf data laata hai → **executor** write *propose* karta hai → **HITL** destructive propose pe pause → **audit** har transition log. Yeh "orchestrator → validation worker → approval gate → posting worker" ka hi roop hai.

> **→ Practice A1** (pass: supervisor 2 specialists ko 8/10 sahi route kare).

---

### §2. Supervisor pattern — routing graph

Supervisor ek central router node hai jo decide karta hai agla worker kaun, aur workers kaam karke **wapas supervisor ko report** karte hain (loop), jab tak supervisor `finish` na bole:

```python
class TeamState(TypedDict):
    messages: list
    next_worker: str
    task: str
    step_log: list

def supervisor_node(state: TeamState) -> dict:
    decision = route_task(state["task"], state["messages"])   # "research" | "execute" | "finish"
    return {"next_worker": decision,
            "step_log": state["step_log"] + [{"agent": "supervisor", "decision": decision}]}

def route_supervisor(state: TeamState) -> Literal["researcher", "executor", "finish"]:
    return state["next_worker"]

graph.add_conditional_edges("supervisor", route_supervisor)
graph.add_edge("researcher", "supervisor")   # worker → wapas boss
graph.add_edge("executor", "supervisor")
```

Pattern dekho: supervisor ka decision `next_worker` mein jaata hai, conditional edge use padhkar route karti hai, aur har worker khatam hoke wapas supervisor pe aata hai (yeh loop multi-step delegation deta hai). `step_log` har decision record karta hai (audit). Production cost-control zaroori hai: chhota model supervisor pe (Haiku route kare, Sonnet sirf hard execute), max-delegation depth (10 loops ke baad stop), aur researcher cache (same `order_id` dobara query mat karo).

> **Ruko, socho:** Supervisor kabhi `finish` nahi bol raha aur graph loop kar raha hai. Kis cheez ki kami hai? (Jawab: ek `max_delegations` guard — N supervisor loops ke baad forced END. Module 07 ka loop-guard yahan bhi lagta hai, warna infinite delegation + bill explode.)

#### §2 common errors

| Error | Kyun | Fix |
|-------|------|-----|
| Infinite supervisor loop | Kabhi `finish` nahi | `max_delegations` + forced END |
| Wrong worker | Task vague | Supervisor prompt mein examples |

---

### §3. Specialist agents — least privilege tools

Asli security yahan hai: **har agent ko sirf wahi tools do jo uske role ke liye chahiye.** Researcher ko sirf read-only tools (`search_orders`, `get_invoice`), executor ko write tools (`send_email`, `propose_refund`). Yeh "least privilege" hai — agar researcher ka prompt inject bhi ho jaaye, uske paas koi destructive tool hai hi nahi.

```python
RESEARCHER_TOOLS = ["search_orders", "get_invoice"]   # read-only, low risk
EXECUTOR_TOOLS   = ["send_email", "propose_refund"]   # writes — HITL ke pehle
```

Role ke hisaab se model aur risk bhi alag: researcher chhota model bhi chal jaata hai (low risk), executor bada model + HITL (high risk), aur optional critic medium model bina kisi tool ke (bure drafts pakadne ke liye). Critic kab worth hai? High-stakes external email ya legal text pe haan; internal lookup summary pe overhead, skip kar do.

> **→ Practice A1** complete.

---

### §4. HITL gates — LangGraph interrupt

Pehle saaf karo kaunse actions gate ke peeche hain. **Destructive (HITL chahiye):** `send_payment`, `write_webhook`, `delete_record`, `issue_refund`. **Non-destructive (no HITL):** `search_docs`, `summarize`, `list_orders`. Ab LangGraph mein gate `interrupt_before` se banta hai — graph us node se *pehle* ruk jaata hai aur state save kar deta hai:

```python
app = graph.compile(checkpointer=MemorySaver(), interrupt_before=["execute_destructive"])
config = {"configurable": {"thread_id": "run-xyz"}}

app.invoke(initial_state, config)   # interrupt tak chala — ab state saved, human UI proposal dikhata hai
app.invoke({"approve": True}, config)    # approve → execute chalega
app.invoke({"approve": False}, config)   # reject → replan edge
```

`interrupt_before` graph ko named node se pehle STOP karta hai; `checkpointer` pause pe state persist karta hai; `thread_id` resume key hai; aur `approve: True/False` human input hai jo agla edge decide karta hai. Yeh checkpoint (Module 07) ke upar hi bana hai — bina checkpointer ke resume possible hi nahi.

Product level pe do flavours hain: **sync HITL** (user screen pe "Approve?" button dekhता hai, fast decisions, high trust) aur **async HITL** (Slack/email approval, run kai din pause reh sakta hai — long enterprise workflows). Ek critical detail: execute node ko **idempotent** banao (`idempotency_key`), warna approve pe double-execute ka risk hai.

#### §4 common errors

| Error | Kyun | Fix |
|-------|------|-----|
| Resume without checkpoint | `checkpointer=None` | `MemorySaver` / Postgres |
| Approve pe double execute | Idempotency missing | Execute pe `idempotency_key` |
| Interrupt kabhi hit nahi hota | Node name typo | `interrupt_before` exact match |

> **→ Practice A2** (pass: reject → replan path kaam kare).

---

### §5. Audit log — har step traceable

Production mein customer support poochhega "yeh refund kyun hua?" — aur jawab guess se nahi, **audit log** se aata hai. Har significant step ka ek structured entry:

```json
{ "run_id": "run_abc", "step": 3, "agent": "executor", "action": "propose_refund",
  "payload": {"order_id": "o_1", "amount": 500},
  "hitl_status": "approved", "approved_by": "user_42", "timestamp": "2026-06-26T10:00:00Z" }
```

```python
def append_audit(state, agent, action, payload):
    entry = {"run_id": state["run_id"], "step": len(state["step_log"]) + 1,
             "agent": agent, "action": action, "payload": payload,
             "timestamp": datetime.utcnow().isoformat() + "Z"}
    return state["step_log"] + [entry]
```

Yahan ek elegant property hai — **reject pe rollback "free" hai.** Kyun? Kyunki HITL gate ne action ko execute node tak pahunchने hi nahi diya — koi side-effect hua hi nahi. State bas `next_worker = "supervisor"` ho jaata hai (replan), aur audit mein `hitl_status: "rejected"` log hota hai. Koi DB rollback nahi, kyunki kuch commit hua hi nahi. (Ek privacy rule: audit mein full card number/PII redact karo.)

> **→ Practice A3** (pass: `run_id` se poora trail query).

---

### §6. Production patterns — sync UI, kill switch, quotas

Practice CLI-approve use karta hai; production mein teen cheezein extra chahiye. **HITL UI contract:** jab graph pause ho, API ek proposal return kare (`status: awaiting_approval`, `proposal`, `run_id`, aur `expires_at` — stale proposals auto-reject, security ke liye), aur `POST /runs/{id}/approve` ya `/reject` se resume ho. **Kill switch** (OWASP excessive-agency): ek admin toggle (feature flag / Redis) jo bina deploy ke saare writes rok de — aur ise **har write node pe** check karo, sirf start pe nahi (warna race). **Per-tenant quota:** multi-agent loops quota jaldi khaते hain, isliye supervisor `max_delegations` + cost cap (Module 10) se link karo.

```python
def executor_node(state):
    if os.getenv("AGENT_EXECUTION_ENABLED", "true") != "true":
        return {"messages": state["messages"] + [{"role": "assistant", "content": "Execution disabled by admin."}]}
    ...
```

#### §6 common errors

| Error | Kyun | Fix |
|-------|------|-----|
| Orphaned paused run | User ne approve nahi kiya | Expiry job + notify |
| Kill switch race | Sirf start pe check | Har write node pe check |

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge.
> Stuck? `@modules/09-multi-agent-hitl/MODULE.md` + error paste.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §1–§3 | `supervisor_router.py` | 8/10 tasks sahi specialist pe |
| A2 | §4 | `hitl_gate.py` | Interrupt + approve/reject paths |
| A3 | §5 | `audit_log.py` | `run_id` se queryable trail |

---

## Active recall (khud jawab likho NOTES mein)

1. HITL sync vs async — ek-ek product example?
2. Critic agent kab worth hai vs skip?
3. Multi-agent cost control — 3 strategies?
4. Reject ke baad rollback kyun "safe" hai — execute node chhua hi nahi?

**Chat drill** (optional): "Module 09 — refund HITL flow whiteboard."

---

## Progress checklist

- [ ] §0 terms — multi-agent, HITL, interrupt, audit
- [ ] Session table follow
- [ ] Practice A1–A3 pass
- [ ] Redraw challenge
- [ ] Active recall NOTES
- [ ] NOTES session log

---

## Optional appendix

- [LangGraph Multi-agent](https://langchain-ai.github.io/langgraph/concepts/multi_agent/)
- [LangGraph Human-in-the-loop](https://langchain-ai.github.io/langgraph/how-tos/human_in_the_loop/)
- Module 07 checkpoints · Module 11 M4 — production HITL + credential vault
