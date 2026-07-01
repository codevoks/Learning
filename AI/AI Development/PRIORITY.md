# Priority & Skip Guide — Application/Product AI Engineer

> **Target:** YC startups + remote US SaaS + backend/AI application roles.
> Tum **products** banate ho (RAG, agents, gateways, LLM apps) — models train nahi karte.
> Isliye deep internals (transformers scratch se, RL, DL foundations) **job ke liye zaroori nahi** — woh curiosity / top-lab-interview ke liye hain.

**Legend:** 🎯 **CORE** (must do — job isi pe khadi) · ⭐ **EDGE** (recommended — alag dikhne ke liye) · ⏭️ **OPTIONAL** (skip if short on time; interest ya lab-interviews ke liye baad mein).

---

## Minimum path to job-ready (agar time kam hai — sirf yeh)

```
00a → 00b → 00c → 00d(core) → 01 → 02 → 03 → 04 → 05 → 06 → 07 → 09 → 10 → 11 → 12 → 13 → 20
```

Yeh 17 modules tumhe portfolio banane + core interviews clear karne ke liye kaafi hain. Baaki sab uske upar edge/depth.

---

## Full tiering

### 🎯 CORE — yeh sab karo (job-critical)

| # | Module | Kyun core |
|---|--------|-----------|
| 00a | Dev Environment | Bina iske kuch build nahi hoga |
| 00b | Python Async & Pydantic | Har FastAPI/LLM call ka base |
| 00c | FastAPI | Tumhara backend layer |
| 00d | ML Foundations | Token/embedding/inference terms (§6 TensorFlow **skip**) |
| 01 | LLM APIs | Core |
| 02 | LLM Infra | Cache/breaker/rate-limit — production |
| 03 | LLM Gateway | Flagship Project C |
| 04 | Prompt Engineering | Core |
| 05 | RAG + pgvector | #1 job skill |
| 06 | Tools & Function Calling | Core |
| 07 | Agents & LangGraph | Core |
| 09 | Multi-Agent & HITL | Production agents |
| 10 | Evals & LLMOps | Har role maangta |
| 11 | Agentic Workflow (Project B) | Flagship project |
| 12 | Guardrails & Safety | #1 hiring gap |
| 13 | Advanced Retrieval | RAG ko production banata |

### ⭐ EDGE — recommended (core ke baad, alag dikhne ke liye)

| # | Module | Kyun / kitna |
|---|--------|--------------|
| 00e | Go Platform | Sirf agar platform/polyglot roles target karo; pure-Python AI roles ke liye **skip OK** |
| 08 | MCP | Increasingly poochha jaata; core-adjacent |
| 14 | Fine-tuning | **§1 (prompt vs RAG vs finetune decision) MUST** — classic interview Q. Baaki (§3 LoRA, §4 DPO, §6 distillation) skim/skip |
| 20 | Memory & Context Engineering | Context engineering ek hot applied skill — recommended |

### ⏭️ OPTIONAL — skip for the job (curiosity / top-lab prep ke liye baad mein)

| # | Module | Kyun skippable (application eng ke liye) |
|---|--------|------------------------------------------|
| 15 | Voice & Multimodal | Vision kabhi useful; voice niche. Skip unless voice/vision product |
| 16 | DL Foundations (NN/RNN/CNN) | Build karne ke liye nahi chahiye; "kaise kaam karta" curiosity |
| 17 | Transformers from Scratch | Interview-gold **labs ke liye**, application-build ke liye nahi. Skip (ya sirf §2 attention intuition padho) |
| 18 | HuggingFace / Open Models | Sirf jab open models self-host karo |
| 19 | Agents from First Principles | 07 (LangGraph) job-need cover karta; yeh understanding ke liye — skim OK |
| 21 | Computer Use & Browser Agents | Emerging/niche — skip unless computer-use product |
| 22 | RL Fine-tuning | Research-adjacent — application eng mein rarely |

---

## Skippable SECTIONS within CORE/EDGE modules

Yeh modules karo, par yeh sections **skim ya skip** kar sakte ho:

| Module | Skip/skim section | Kyun |
|--------|-------------------|------|
| 00d | §6 TensorFlow/Keras hello | "Awareness only" — tum train nahi karte |
| 14 | §3 LoRA detail, §4 DPO, §6 distillation | §1 decision + §2 SFT format + §5 dataset kaafi hai |
| 05 | §5 Hybrid search | Module 13 mein deeper — wahan padho |
| 02 | §7 Observability deep-dive | Concept kaafi; deep OTEL setup baad mein |

---

## Ek line mein

> **Job ke liye:** 🎯 CORE sab karo → ⭐ EDGE se 1-2 pick → ⏭️ OPTIONAL baad ke liye chhodo.
> Deep internals (16, 17, 22) **galat nahi hain** — bas *is job* ke liye critical-path pe nahi. Portfolio ship karna > internals ratna.

Detailed reasoning kisi module mein confusion ho to us MODULE.md ka header badge dekho (🎯/⭐/⏭️).
