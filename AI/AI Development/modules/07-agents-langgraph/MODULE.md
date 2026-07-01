# Module 07 — Agents & LangGraph

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 06](../06-tools-function-calling/MODULE.md) · Next → [Module 08](../08-mcp/MODULE.md)

> **Format**: Textbook — §0 terms zero se, prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`

## At a glance

| | |
|---|---|
| Prerequisites | Module 06 (tool call loop). 00c FastAPI recommended |
| Duration | ~5–8 sessions |
| Project? | No (par Project B mein yahi graph — Module 11) |
| Exit test | Agent loop guards + checkpoint resume bina notes ke samjhao |

## Yeh module kis baare mein hai

Module 06 mein tumne tool loop dekha: LLM → tool → result → LLM. **Agent** wahi loop hai jab LLM khud decide karta hai — kaunsa tool, kab, kitni baar, aur kab rukna hai. Chhote demos ke liye ek `while` loop kaafi hai, par jab workflow branch hone lage ("agar amount > 5000 to human approval, warna seedhe refund"), crash-recovery chahiye, aur audit trail chahiye — tab ek `while` + 15 `if` ka jhamela ban jaata hai. LangGraph isका jawab hai: workflow ko ek **state machine** banao jisme har step ek **node** hai.

Tumhare liye yeh naya nahi hai — tumne Zapier-style automation aur 5-stage refund state machines banaye hain. LangGraph wahi hai, bas har step Python function aur state ek shared object. §0 mein agent/node/edge/checkpoint zero se.

```
[START] → (classify) → (respond) → [END]
              └── conditional edge → billing path ya general path
   ◆ checkpoint = run ka snapshot (crash ke baad resume)
```

**Redraw challenge**: 3 nodes, 1 conditional edge, 1 checkpoint — bina dekhe banao.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + §1 Problem | Pseudo-loop likhke socho kahan toot-ega |
| 2 | §2 StateGraph | **A1** — `two_node_graph.py` |
| 3 | §3 ReAct loop | **A1** complete + **A2** start |
| 4 | §4 Loop guards | **A2** — `tool_agent_graph.py` |
| 5 | §5 Checkpoints | **A3** — `checkpoint_resume.py` |
| 6 | §6 Memory + §7 Kab graph? | Active recall NOTES |

---

## Theory

### §0. Terms pehli baar — agent, state graph, checkpoint

**Agent.** Sabse simple definition: agent = **LLM + tools + loop + stop condition.** User kehta hai "Delhi ka weather batao aur calendar mein reminder daalo" → LLM sochta hai (reason) → tool call karta hai (act) → result dekhta hai (observe) → phir sochta hai aur ya to dusra tool maangता hai ya final jawab deta hai. Yeh reason→act→observe cycle hi agent ka dil hai. Ek ops-person socho jo ticket dekhta hai, system call karta hai, result dekhta hai, phir decide karta hai aage kya.

Graph banane ke char shabd: **node** ek step ka code hai (state andar, partial update bahar); **edge** batata hai agla node kaun (fixed ya condition se); **state** poori run ki memory ek object mein; **checkpoint** us state ka disk pe snapshot (crash ke baad wahi se resume). Tumhare refund pipeline mein har stage ek node, payment-fail-pe-retry ek conditional edge, aur outbox commit ek checkpoint — yahi parallel hai.

**StateGraph — Zapier se.** Tumne Zapier banaya: trigger → action → filter → action → done. LangGraph wahi hai — trigger = START node, har action ek node, filter ek conditional edge, done = END. Farak sirf yeh ki Zapier UI mein draw karte ho, LangGraph code mein `add_node()` + `add_edge()`. Pehla chhota graph:

```python
from typing import TypedDict, Literal
from langgraph.graph import StateGraph, START, END

class AgentState(TypedDict):
    messages: list
    route: str
    step_count: int        # loop guard ke liye

def classify_node(state: AgentState) -> dict:
    last = state["messages"][-1]["content"]
    route = "billing" if "invoice" in last.lower() else "general"
    return {"route": route, "step_count": state.get("step_count", 0) + 1}   # sirf badli fields

def respond_node(state: AgentState) -> dict:
    return {"messages": state["messages"] + [{"role": "assistant", "content": f"Handled: {state['route']}"}]}

graph = StateGraph(AgentState)
graph.add_node("classify", classify_node)
graph.add_node("respond", respond_node)
graph.add_edge(START, "classify")
graph.add_edge("classify", "respond")
graph.add_edge("respond", END)
app = graph.compile()
```

Sabse important pattern jo naye log miss karte hain: **node poora state return nahi karta, sirf badli hui fields ka partial dict return karta hai** — LangGraph use purani state mein merge kar deta hai. `classify_node` ne sirf `route` aur `step_count` lautaaye, `messages` ko chhua bhi nahi; wo apne aap bana rahता hai. `TypedDict` state ka shape lock karta hai, aur `compile()` ek runnable app deta hai jise `.invoke()` se chalate ho.

> **Ruko, socho:** Agar `classify_node` galti se poora state return kare (saari keys, kuch galat values ke saath) bajaye sirf `{"route": ...}` ke, to kya problem ho sakti hai? (Jawab: tum apni hi history overwrite kar doge — jaise `messages` ko purani/khaali value se replace. Partial update isiliye safe hai: tum sirf wahi badalte ho jo badalna hai, baaki merge ho jaata hai.)

**§0 checkpoint:** (1) Node poora state return karta hai ya partial? (2) Fixed vs conditional edge — example? (3) Checkpoint crash ke bina kab useful?

---

### §1. Problem pehle — linear script kahan toot-ta hai

Module 06 ka `while` loop chhote demos ke liye theek tha. Par ek asli refund workflow dekho:

```
User refund request → classify intent → fetch order (tool)
  → if amount > 5000 → HUMAN APPROVAL      ← yahan script messy hone lagti hai
  → if approved → refund (tool)
  → if fail → retry ya escalate            ← aur messy
  → notify user
```

Isе ek `while` loop + 15 `if` mein likho to teen problem aati hain: crash ke baad **kahan se resume** karein — pata nahi; har branch ko **test** karna mushkil; aur **audit trail** nahi — kaunse step pe kya hua. Graph yeh teeno solve karta hai — har step node, routing edge, save checkpoint. Yeh tumhara outbox-pattern wala hi dimaag hai: state durable, steps idempotent. Flow simple hai: user message se initial state bano → graph node-by-node chalता hai → har node state update karta hai → edge next decide karta hai → END ya error pe rukta hai.

> **→ Practice A1** (pass: `two_node_graph.py` — classify → respond, 10/10 routing).

---

### §2. StateGraph — nodes aur edges detail se

Node ke char rules yaad rakho: signature `(state) -> dict` hai; node side-effect (LLM/DB call) kar *sakta* hai par jahan ho sake pure rakho (test ke liye); return hamesha **partial update**; aur node ke naam unique strings. Asli power **conditional edge** mein hai — ek router function jo state padhkar agle node ka naam return karta hai:

```python
def route_after_classify(state: AgentState) -> Literal["billing_respond", "general_respond"]:
    return "billing_respond" if state["route"] == "billing" else "general_respond"

graph.add_conditional_edges("classify", route_after_classify)
```

Router ka return value ek **registered node ka naam** hona chahiye, warna "node not found". Yeh Zapier ka filter step hai — "Amount > 500" true → Slack path, false → Email path. Compile + invoke:

```python
app = graph.compile(checkpointer=memory)   # checkpointer §5 mein
config = {"configurable": {"thread_id": "user-42-session-1"}}
result = app.invoke({"messages": [{"role": "user", "content": "invoice #99 status?"}], "step_count": 0}, config=config)
```

Initial state dict banao, `thread_id` config mein do (checkpoint key), `invoke` START se END tak chalata hai aur final merged state return karta hai.

#### §2 common errors

| Error | Kyun | Fix |
|-------|------|-----|
| `KeyError: thread_id` | Checkpointer on, config missing | `configurable.thread_id` do |
| `GraphRecursionError` | Infinite loop | `step_count` guard + `recursion_limit` |
| Node not found | Router galat string laaya | Router returns = `add_node` names |

> **→ Practice A1** complete karo.

---

### §3. ReAct loop — reason + act graph mein

**ReAct** = Reason + Act. LLM sochta hai, tool call karta hai, observation leta hai, phir dobara sochta hai — jab tak jawab na mil jaaye:

```
Thought: User wants weather in Delhi
Action:  get_weather(city="Delhi")
Observation: {"temp_c": 38}
Thought: I have enough → Answer: Delhi mein abhi 38°C hai
```

LangGraph mein yeh ek **2-node loop** ban jaata hai — ek `agent` node (LLM call) aur ek `tools` node (tools execute), jo aapas mein loop karte hain jab tak model aur tool na maange:

```python
def should_continue(state: AgentState) -> Literal["tools", "__end__"]:
    last = state["messages"][-1]
    return "tools" if getattr(last, "tool_calls", None) else "__end__"

graph.add_conditional_edges("agent", should_continue)
graph.add_edge("tools", "agent")   # observation ke baad wapas reason
```

`agent` node LLM ko messages bhejता hai; agar response mein `tool_calls` hain to `should_continue` `tools` node bhejता hai jo har tool execute karke result append karta hai, phir wapas `agent`. Tool-calls na hon to `__end__`. Yeh Module 06 ka wahi tool loop hai — bas ab `if` chain ki jagah graph nodes mein bant gaya, jisse branching, checkpoint, aur audit possible ho gaye.

> **→ Practice A2** (pass: `tool_agent_graph.py` — multi-step task complete).

---

### §4. Loops — power aur production ka khatra

Agent loop unlimited chal sakta hai — aur production mein **yeh ek incident hai** (bill explode, infinite loop). Isliye guards zaroori hain, sabse basic `max_iterations`:

```python
MAX_ITERATIONS = 10

def agent_node(state: AgentState) -> dict:
    if state["step_count"] >= MAX_ITERATIONS:
        return {"messages": state["messages"] + [{"role": "assistant", "content": "Stopped: max steps reached"}]}
    # ... normal LLM call
    return {"step_count": state["step_count"] + 1, ...}
```

Interview ke liye char guards yaad rakho: **max_iterations** (hard cap on step_count), **repeated-tool detection** (last N calls ka hash compare karke same call baar-baar rokо), **timeout** (`asyncio.wait_for` / worker deadline — 5 min hang na ho), aur **human interrupt** (runaway agent ka kill switch — Module 09 HITL). LangGraph ka apna `recursion_limit` (default 25) bhi hai, par uspe bharosa mat karo — apna guard pehle lagao.

> **Ruko, socho:** Tumhara agent ek hi tool ko 20 baar same arguments se call kar raha hai aur `max_iterations` 50 hai. Sirf max_iterations kaafi hai? (Jawab: nahi — wo 50 tak paisa jala chuka hoga. Repeated-tool detection chahiye jo same call do-teen baar dekhte hi loop tod de, max tak pahunchne se pehle.)

> **→ Practice A2** mein `max_iterations` guard zaroor.

---

### §5. Checkpoints — durability (savepoint jaisा)

Problem: server beech run mein restart ho jaaye, to bina checkpoint user ko sab kuch START se karna padega — aur refund jaise workflow mein iska matlab **double refund** ka risk. Checkpoint state ko har node ke baad save karta hai, taaki crash ke baad wahi se resume ho. Yeh bilkul tumhara outbox parallel hai: jaise TX commit event durable banata hai aur worker crash ke baad dobara consume karta hai, waise hi node ke baad state save hota hai aur same `thread_id` se `invoke` resume karta hai.

```python
from langgraph.checkpoint.memory import MemorySaver

app = graph.compile(checkpointer=MemorySaver())
config = {"configurable": {"thread_id": "run-abc-123"}}
app.invoke(initial_state, config)   # beech mein ruk/crash ho sakta hai
app.invoke(None, config)            # same thread_id → state wahi se resume
```

`thread_id` ek conversation/workflow run ki unique key hai (same user ki nayi run = naya thread_id). Storage choose karo zaroorat se: `MemorySaver` (local dev — restart pe data gaya), `SqliteSaver` (file persist, local integration test), ya `PostgresSaver` (production — multi-instance, deploy survive). Resume pe khaali checkpoint mile to pehla suspect galat `thread_id`.

> **→ Practice A3** (pass: mid-run kill → same `thread_id` se resume).

---

### §6. Memory patterns — short vs long term  ⏭️ (deeper in Module 20)

> ⏭️ **Skim OK** — short/long-term memory ka poora treatment Module 20 (recommended) mein. Yahan bas concept.

Do tarah ki memory hoti hai aur inhe alag rakhna zaroori hai. **Short-term** `state["messages"]` mein hai — is run ki conversation + tool results, jo checkpoint ke saath persist ho sakta hai, par context-window limit ke kaaran purane messages ko summarize/truncate karna padta hai. **Long-term** ek alag store (vector DB / SQL) mein hai — cross-session facts jaise "User Hinglish prefer karta hai" ya "Acme ka billing contact Raj hai" — jise ek retrieve node se inject karte ho. Current turn ka tool output short-term mein, user preference long-term mein, workflow progress checkpoint mein. Module 11 mein workflow history Postgres mein jaayegi — wahi long-term hai.

---

### §7. Single loop vs graph — kab graph zaroori?

Har cheez ke liye graph ki zaroorat nahi. Ek simple `while` loop theek hai jab 1–2 tools hon, flow linear ho, prototype ho, aur crash-recovery na chahiye. Graph tab zaroori hai jab branching workflows hon, HITL gates (Module 09) hon, checkpoint + audit chahiye, ya kai specialists (researcher + executor) ho. Rule of thumb: agar whiteboard pe 3+ boxes aur "agar yeh to woh" arrows ban rahe hain → graph likho.

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge (`TODO` search).

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §0–§2 | `two_node_graph.py` | classify → respond, 10/10 routing |
| A2 | §3, §4 | `tool_agent_graph.py` | Multi-step task + `max_iterations` |
| A3 | §5 | `checkpoint_resume.py` | Mid-run kill → same state resume |

---

## Active recall (khud jawab likho NOTES mein)

1. Agent infinite loop production mein kaise rokoge — kam se kam 3 tareeke?
2. Checkpoint memory vs Postgres — kab kaunsa?
3. Zapier workflow ko LangGraph terms mein map karo (trigger → ?, step → ?).
4. Node partial update kyun return karta hai, poora state kyun nahi?

**Chat drill** (optional): "Module 07 — checkpoint flow + outbox parallel samjhao."

---

## Progress checklist

- [ ] §0 terms — agent, node, edge, checkpoint bina dekhe bol sakta hoon
- [ ] Session read order follow kiya
- [ ] Practice A1–A3 pass
- [ ] Redraw challenge
- [ ] Active recall NOTES mein
- [ ] NOTES session log updated

---

## Optional appendix (zarurat ho tab)

- [LangGraph Introduction](https://langchain-ai.github.io/langgraph/)
- [LangGraph Persistence](https://langchain-ai.github.io/langgraph/concepts/persistence/)
- Module 06 — tool loop · Module 11 — production workflow graph
