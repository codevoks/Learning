# Module 20 — Memory & Context Engineering

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 19](../19-agents-first-principles/MODULE.md) · Next → [Module 21](../21-computer-use/MODULE.md)

> **Format**: Textbook — §0 terms zero se, prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`
> **Track 3:** Module 07 §6 ka "memory" ab poora — plus context engineering (hot skill).

## At a glance

| | |
|---|---|
| Prerequisites | Module 05/13 (RAG), 07 (agents), 04 (prompts) |
| Duration | ~3–5 sessions |
| Project? | Mini — ek memory layer (portfolio) |
| Exit test | Short vs long-term memory + summarization + context budget bina notes ke samjhao |

## Yeh module kis baare mein hai

LLM **stateless** hai — har call ke baad sab bhool jaata hai (Module 01/03). Par ek useful agent ya chatbot ko **yaad** rakhna padta hai: is conversation mein pehle kya hua, aur cross-session facts ("yeh user Hinglish prefer karta hai"). Yeh module wo **memory** systems sikhata hai. Saath mein **context engineering** — ek hot 2026 skill — jo poochhता hai: "context window (limited jagah) mein *kya* daalein, *kaise* order karein, *kitna* compress karein taaki model best jawab de?" Yeh RAG (kya retrieve) se aage ka discipline hai: jo retrieve hua uska best use.

Do core ideas jo module ko anchor karti hain: (1) **memory do tarah ki** — short-term (is conversation ki, context window mein) aur long-term (cross-session, alag store se retrieve); (2) **context window ek scarce budget hai** — usme sab kuch nahi aata, to summarize/trim/prioritize karna padta hai (context engineering).

```
Short-term (working memory)      Long-term (persistent)
  conversation buffer              memory store (vector/SQL)
  sliding window / summary          write facts, retrieve relevant
        │                                  │
        └──────► CONTEXT WINDOW (budget) ◄─┘  ← context engineering: kya+kaise+kitna
```

**Redraw challenge**: short-term + long-term memory → context window (budget) flow — bina dekhe banao.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + §1 Why memory + §2 Short-term | **A1** — `conversation_buffer.py` |
| 2 | §3 Context budget + §4 Summarization | **A2** — `token_budget_trimmer.py` |
| 3 | §5 Long-term memory | **A3** — `memory_store.py` |
| 4 | §6 Context engineering | Recall + NOTES |

---

## Theory

### §0. Terms pehli baar — short/long-term, context window, summary buffer

**Short-term (working) memory.** Is conversation/run ki memory — recent turns, tool results. Context window mein rehti hai, checkpoint (Module 07) ke saath persist ho sakti hai. Session khatam → aksar chali jaati.

**Long-term memory.** Cross-session, persistent facts — user preferences, past decisions, learned info. Ek alag store (vector DB / SQL) mein rehti hai, aur zaroorat pe retrieve karke context mein inject hoti hai. Yeh RAG hi hai, par "conversation/user memory" pe applied.

**Context window.** Model ek call mein jitne tokens le sakta hai (Module 01) — ek **fixed budget**. System prompt + memory + retrieved docs + user query sab isi mein fit hone chahiye.

**Summarization buffer.** Jab conversation lambi ho jaaye aur context budget khatam ho, purane turns ko ek chhote **summary** mein nichод do (poore turns ki jagah). Isse lambi conversation bhi budget mein rehti hai.

**Episodic vs semantic memory.** Do tarah ki long-term memory (insaan se udhaar). **Episodic** — specific events/interactions ("pichle hafte user ne refund maanga tha"). **Semantic** — general facts ("user enterprise plan pe hai"). Dono alag store/retrieve ho sakte hain.

**Context engineering.** Yeh discipline — context window mein kya daalein, kis order mein, aur kaise compress karein. RAG "kya retrieve" karta hai; context engineering us retrieved + memory + instructions ko *best arrange* karta hai. Yeh 2026 ka hot skill hai kyunki model ki quality bahut context ke construction pe depend karti hai.

> **Ruko, socho:** Conversation 200 turns lambi ho gayi aur context budget se bahar. Poore turns kyun na rakhein, summarize kyun karein? (Jawab: context window fixed hai — 200 turns fit hi nahi honge, aur agar fit bhi ho to "lost in the middle" (Module 05) se model beech ki cheezein miss karta + cost badhता. Purane turns ka summary key info bachaता hai kam tokens mein.)

**§0 checkpoint:** (1) Short vs long-term memory? (2) Context window ek budget kyun? (3) RAG vs context engineering ka farak?

---

### §1. Memory kyun — stateless LLM ko yaad dilana

LLM har request stateless handle karta hai (Module 03) — usके paas apni koi memory nahi. Do problems isse: (1) chatbot ko conversation ka flow yaad rakhna hai (turn 5 pe turn 2 ki baat reference ho), aur (2) ek assistant ko user ke baare mein cross-session facts yaad rakhne hain (har baar dobara na poochhe). Solution: **memory tumhe manage karni padti hai** — short-term ke liye conversation ko context mein carry karo, long-term ke liye ek store mein likho aur relevant hone pe retrieve karo. Yeh module dono ka mechanics deta hai.

---

### §2. Short-term / working memory

Sabse basic — conversation buffer. Har turn (user + assistant) ko ek list mein rakho aur agli call mein bhejo (Module 01 ka `messages[]`). Par yeh unbounded badh jaayega, to do strategies: **sliding window** (sirf last N turns rakho — purane drop) ya **summary buffer** (purane turns ko summary mein nichод do, recent turns as-is). Sliding window simple par purani important baat kho sakti; summary buffer key info bachaता hai par ek extra LLM call (summarize) maangता. Aksar hybrid — recent K turns verbatim + usse purane ka running summary.

> **→ Practice A1** (`conversation_buffer.py`) — sliding-window buffer (last N turns).

---

### §3. Context window management — token budget

Context ek scarce budget hai, to usme cheezein **priority** se daalo aur budget cross hone pe **trim** karo. Ek typical priority: system prompt (kabhi drop nahi — policy), phir retrieved context/memory (relevant), phir recent conversation, phir purani conversation (pehle drop). Trimming ka rule (Module 01 §6 ka recap, ab memory pe): budget count karo, cross ho to sabse kam-priority (purane turns) pehle drop karo, system hamesha rakho, aur zaroorat ho to purane ko summarize karके daalо. Yeh sochने ka tareeka — "har token ki value hai, budget ke andar highest-value cheezein rakho" — hi context engineering ka core hai.

> **→ Practice A2** (`token_budget_trimmer.py`) — messages ko token budget mein trim karo (system rakho, purane drop).

---

### §4. Summarization strategies

Jab lambी cheez ko chhota karna ho (conversation, ek bada doc), summarization aati hai. **Running summary** — har naye turn pe summary update karo (incremental). **Hierarchical / map-reduce** — bade content ko chunks mein summarize karo (map), phir summaries ko summarize karo (reduce) — bahut lambे docs ke liye. **Extractive vs abstractive** — key sentences uthaao (extractive, sasta) ya LLM se naya summary likhwaao (abstractive, behtar par LLM call). Trade-off wahi — quality vs cost/latency. Production tip: summary mein **key facts + decisions** bachао (naam, numbers, commitments), fluff drop — kyunki summary ka maqsad downstream reasoning enable karna hai.

---

### §5. Long-term memory — store aur retrieve

Cross-session memory ke liye ek **memory store** chahiye. Do operations: **write** (ek fact/interaction ko store karo — embed karke vector DB mein, ya structured SQL mein) aur **retrieve** (current context ke relevant memories nikaalo — semantic search, Module 05/13). Yeh RAG hi hai, par "user/agent memory" pe. Ek design question — **kya store karein?** Sab kuch store karna noise banata; important facts/decisions/preferences hi store karo (aksar ek LLM se "is turn se yaad rakhने layak kya hai?" extract karके). **mem0** jaise memory frameworks yahi automate karte hain — extract, dedupe, update, retrieve. Episodic (events) aur semantic (facts) ko alag rakhna retrieval ko sharp karta hai.

> **→ Practice A3** (`memory_store.py`) — write + retrieve (keyword/relevance-based).

---

### §6. Context engineering — the discipline

Yeh sab jodता hai. Ek request ke liye context banate waqt tum decide karte ho: **kya** (system rules + relevant long-term memory + recent short-term + retrieved docs + tools), **kis order mein** (important cheezein start/end pe — "lost in the middle" se bacho; instructions clear aur upar), aur **kitna** (budget ke andar — trim/summarize). Achhi context engineering se ek chhota model bhi accha perform karta; buri se bada model bhi bhatak jaata. Interview point: "quality ka bada hissa model nahi, context construction hai — maine relevant memory retrieve ki, budget ke andar trim ki, aur instructions ko position kiya taaki model reliably follow kare." Yeh RAG + memory + prompt engineering ka sangam hai, aur yahi "context engineer" role ki demand hai.

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge.
> A1–A3 offline — `python <file>.py` → `_check()` pass.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §2 | `conversation_buffer.py` | `_check()` asserts pass (sliding window) |
| A2 | §3 | `token_budget_trimmer.py` | `_check()` asserts pass (system kept, oldest dropped) |
| A3 | §5 | `memory_store.py` | `_check()` asserts pass (write + retrieve) |

### Setup

```bash
cd modules/20-memory-context/practice
python3 -m venv .venv && source .venv/bin/activate
# A1-A3 sirf stdlib. Real long-term memory: pgvector (Module 05) + embeddings.
```

---

## Active recall (khud jawab likho NOTES mein)

1. Short vs long-term memory — ek example each?
2. Sliding window vs summary buffer — trade-off?
3. Context budget cross ho to kya pehle drop, kya kabhi nahi?
4. RAG vs context engineering — farak?

**Chat drill** (optional): "Module 20 — ek chatbot ka memory + context pipeline whiteboard."

---

## Progress checklist

- [ ] §0 terms clear
- [ ] Theory §1–§6 padha
- [ ] Practice A1–A3 pass
- [ ] Redraw challenge (memory → context)
- [ ] Active recall NOTES mein
- [ ] NOTES session log

---

## Optional appendix

- [mem0 — memory framework](https://github.com/mem0ai/mem0)
- [Anthropic — Effective context engineering](https://www.anthropic.com/engineering)
- Module 05/13 (RAG = long-term memory retrieval) · 07 (checkpoints = short-term persist)
