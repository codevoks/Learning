# Module 19 — Agents from First Principles

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 18](../18-huggingface-open-models/MODULE.md) · Next → [Module 20](../20-memory-context/MODULE.md)

> **Format**: Textbook — §0 terms zero se, prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`
> **Track 3 (internals):** Module 07 ne LangGraph *use* karna sikhaya; yeh andar kya hai wo sikhata hai.
> ⏭️ **OPTIONAL for application jobs** — 07 (LangGraph) job-need cover karta hai; yeh understanding ke liye. Skim OK. Priority: [PRIORITY.md](../../PRIORITY.md).

## At a glance

| | |
|---|---|
| Prerequisites | Module 06 (tool loop), 07 (LangGraph) |
| Duration | ~3–5 sessions |
| Project? | Mini — apna chhota agent framework (portfolio piece) |
| Exit test | Agent loop + tool registry + stop conditions bina framework ke banao aur samjhao |

## Yeh module kis baare mein hai

Module 07 mein tumne LangGraph se agents banaye. Par LangGraph ek **abstraction** hai — usne bahut kuch chhupा diya. Interviewer (khaaskar YC/startup) aksar poochhता hai "agent framework ke bina, scratch se agent kaise banaoge?" — aur agar tum sirf "LangGraph use karta hoon" bol paate ho, wo red flag hai. Yeh module wo abstraction hataता hai: ek agent asal mein ek **while loop + tool registry + stop conditions** hai — bas. Yeh banake tum LangGraph ko *demystify* kar doge aur samajh jaoge wo tumhare liye kya karता hai (aur kya nahi).

Ek core insight jo poore module ka anchor hai — **"agent framework" koi jaadu nahi, ek loop hai:** model se poochho "ab kya karun?" → agar wo tool maange, tool chala ke result wapas do → agar wo final answer de, ruk jao → warna repeat. Module 06 ka tool loop hi hai, bas ise ek reusable framework mein pack karna.

```
run_agent(task):
  loop:
    decision = llm(scratchpad)         # "think"
    if decision is final → return       # stop
    result = tools[decision.tool](args) # "act"
    scratchpad += result                # "observe"
    guard: max_steps / repeated? → stop
```

**Redraw challenge**: minimal agent loop — llm → tool? → execute → repeat, stop conditions ke saath — bina dekhe banao.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + §1 Why scratch + §2 Loop | Module 07 graph ko loop mein map karo |
| 2 | §3 Tool registry | **A1** — `tool_registry.py` |
| 3 | §4 Stop conditions + §5 Planning | **A2** — `agent_loop.py` |
| 4 | §6 Scratch vs framework | **A3** — `COMPARE.md` |

---

## Theory

### §0. Terms pehli baar — agent loop, registry, ReAct

**Agent loop.** Agent ka dil — ek `while` loop jo model se baar-baar poochhता hai "ab kya?" jab tak task poora na ho. Har iteration: think (model decide kare) → act (tool chale) → observe (result wapas). Yeh Module 06 ka tool loop hi hai.

**Tool registry.** Ek jagah jahan saare available tools register hote hain — naam, function, aur description (schema). Agent registry se tools list karta hai (model ko batane ke liye) aur naam se dispatch karta hai. Yeh "allowlist" bhi hai (Module 06 security) — sirf registered tools chal sakte hain.

**Dispatch.** Model ne tool call maanga (`{name, args}`) → registry us naam ka function dhoondh ke `args` ke saath chalata hai. Unknown naam → error (safe).

**Scratchpad.** Agent ki running memory — ab tak ke thoughts, tool calls, aur results. Har iteration model ko yeh poora context milta hai taaki wo agla step decide kar sake. (Yeh Module 07 ke `state["messages"]` jaisा hi hai.)

**Stop condition.** Loop kab ruke — model "final answer" de de, ya guards trip ho jaayein (max steps, repeated tool call, timeout — Module 07 §4). Bina stop condition ke agent infinite loop = production incident.

**ReAct (Reason + Act).** Ek popular agent pattern (Module 07 §3) — model pehle "thought" likhता hai (reasoning), phir "action" (tool call), phir "observation" (result), phir dobara. Yeh loop ko structure deta hai.

**Planner / executor.** Kuch agents pehle poora **plan** banate hain (steps ki list), phir execute karte hain (plan-and-execute) — vs ReAct jo har step pe decide karta hai. Dono trade-offs (§5).

> **Ruko, socho:** LangGraph (Module 07) ne is loop ke upar kya "extra" add kiya jo pure while-loop mein nahi? (Jawab: state persistence/checkpoints, conditional edges (branching graph), HITL interrupts, aur visualization. Core loop same hai — LangGraph usko durable, branchable, aur resumable banaता hai. Yeh jaanना ki wo kya add karta hai, hi decide karne deta hai kab framework chahiye.)

**§0 checkpoint:** (1) Agent loop 3 steps? (2) Tool registry ka dohra kaam (list + allowlist)? (3) Stop condition kyun zaroori?

---

### §1. Scratch se kyun — abstraction demystify

LangGraph shuru mein magic lagta hai — nodes, edges, state, checkpoints. Par jab tum use scratch se banaoge, do cheezein hongi: (1) tum samajh jaoge agent asal mein kitna simple hai (ek loop), jisse debugging + design decisions aasan ho jaate; (2) interview mein tum "internals se" bol paoge, sirf "library use karta hoon" nahi. Yeh wahi philosophy hai jo Module 17 (transformers scratch se) mein thi — abstraction ke neeche jaake control aur understanding paana. Aur practically — chhote use cases ke liye ek 30-line agent loop LangGraph se simpler aur faster hota hai (Module 07 §7 ka "kab framework" recap).

---

### §2. The minimal agent loop

Yeh Module 06 ka tool loop hai, ab ek reusable function ke roop mein:

```
run_agent(task, llm, tools, max_steps):
  scratchpad = [task]
  for step in range(max_steps):
      decision = llm(scratchpad)           # think: {"tool":name,"args":{}} ya {"final":text}
      if decision has "final":             # stop condition 1
          return decision["final"]
      result = dispatch(tools, decision["tool"], decision["args"])   # act
      scratchpad.append((decision, result))                          # observe
  return "stopped: max steps reached"      # stop condition 2 (guard)
```

Bas — yeh poora agent hai. `llm` model ko call karta hai jo ya to ek tool maangता hai ya final answer deta hai. Loop tool chala ke result scratchpad mein daal deta hai aur dobara model se poochhता hai. Do jagah rukता hai: model "final" bole (kaam ho gaya), ya `max_steps` khatam (guard). Sab kuch iske upar (planning, memory, HITL) additions hain. Jab tum yeh khud likh lete ho, LangGraph ke nodes/edges "oh, yeh to bas isi loop ka structured version hai" ban jaate hain.

---

### §3. Tool registry + dispatch

Agent ko tools chahiye, aur unhe manage karne ke liye ek **registry**. Registry teen cheezein karta hai: tools register karna (naam + function + description), model ke liye descriptions list karna (taaki model jaane kya available hai — Module 06 schema), aur naam se dispatch karna (execute). Aur ek security role — yeh **allowlist** hai: sirf registered tools chal sakte hain, model kuch aur "invent" nahi kar sakta.

```
registry.register("search", search_fn, "Search docs by keyword")
registry.register("calc", calc_fn, "Do arithmetic")
registry.list_tools()          # model ko dikhane ke liye [{name, description}, ...]
registry.dispatch("search", query="refund")   # execute; unknown naam → error
```

`dispatch` mein ek subtle safety point — unknown tool naam pe crash nahi, ek clean error do (jo model ko wapas ja sake, "yeh tool nahi hai, dobara socho"). Aur args validation (Module 06 Pydantic) yahin lagti hai execute se pehle.

> **→ Practice A1** (`tool_registry.py`) — register + list + dispatch (+ unknown-tool error).

---

### §4. Stop conditions + guards

Agent loop ka sabse important safety hissa — **kab rukna hai** (Module 07 §4 ka core). Char guards jo har production agent mein hone chahiye: **final-answer detection** (model ne kaam khatam bola), **max steps** (hard cap — infinite loop na ho), **repeated-call detection** (model same tool same args baar-baar maang raha → wo stuck hai, tod do), aur **timeout** (wall-clock deadline). Bina inke ek agent galat direction mein infinite chal ke bill jala sakta hai — yeh production incident hai, theory nahi. Yeh guards banana hi "agent ko production-ready" banana hai.

> **→ Practice A2** (`agent_loop.py`) — loop with stop conditions (fake `llm` se test).

---

### §5. Planning — ReAct vs plan-and-execute

Do tareeke agent kaam approach karta hai. **ReAct** (Module 07 §3) — har step pe model decide karta hai agla action, observation dekhকর adjust karta. Flexible (mid-course correct kar sakta), par kabhi bhatak jaata (no big-picture plan). **Plan-and-execute** — model pehle poora plan banata hai (steps ki list), phir ek-ek execute karta. Structured aur predictable, par rigid (plan galat ho to poora bhatka). Bade tasks mein hybrid: ek high-level plan + har step pe ReAct-style adjustment. Interview point: "simple tasks ReAct, complex multi-step tasks plan-and-execute ya hybrid — kyunki ReAct lambे tasks mein context/focus kho deta."

---

### §6. Scratch vs framework — kab graduate karo

Ab decision (Module 07 §7 ka andar-se-samjha version). **Scratch loop tab** jab task simple ho (1-2 tools, linear), tum full control/transparency chaहte ho, ya learning kar rahe ho. **Framework (LangGraph) tab** jab chahiye: durable state + checkpoints (crash recovery), complex branching (conditional graphs), HITL interrupts, multi-agent orchestration, ya observability integration. Kyunki tumne scratch se banaya hai, ab tum *exactly* jaante ho framework kya add kar raha hai — to tum informed choice kar sakte ho, cargo-cult nahi. Yeh maturity hai: "maine agent scratch se banaya, phir jab checkpoints + HITL chahiye the tab LangGraph pe move kiya."

> **→ Practice A3** (`COMPARE.md`) — tumhara scratch agent vs LangGraph: kya add hua, kab worth.

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge.
> A1, A2 offline (fake llm) — `python <file>.py` → `_check()` pass.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §3 | `tool_registry.py` | `_check()` asserts pass (register/list/dispatch + unknown error) |
| A2 | §2, §4 | `agent_loop.py` | `_check()` asserts pass (tool exec + stop conditions) |
| A3 | §6 | `COMPARE.md` | Scratch vs LangGraph: what/when |

### Setup

```bash
cd modules/19-agents-first-principles/practice
python3 -m venv .venv && source .venv/bin/activate
# A1, A2 sirf stdlib (fake llm se test). Real LLM se bhi try kar sakte ho.
```

---

## Active recall (khud jawab likho NOTES mein)

1. Agent = ? (ek line, framework ke bina)
2. Tool registry ka dohra kaam?
3. 4 stop conditions/guards?
4. ReAct vs plan-and-execute — kab kaunsa?
5. LangGraph tumhare scratch loop ke upar kya add karta hai?

**Chat drill** (optional): "Module 19 — 30-line agent framework whiteboard."

---

## Progress checklist

- [ ] §0 terms clear
- [ ] Theory §1–§6 padha
- [ ] Practice A1–A3 pass
- [ ] Redraw challenge (agent loop)
- [ ] Active recall NOTES mein
- [ ] NOTES session log

---

## Optional appendix

- [ReAct paper](https://arxiv.org/abs/2210.03629)
- [Anthropic — Building effective agents](https://www.anthropic.com/research/building-effective-agents)
- Module 06 (tool loop) · 07 (LangGraph — jab framework chahiye) · 09 (multi-agent)
