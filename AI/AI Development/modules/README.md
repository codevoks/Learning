# Modules Index

Har module = **ek naya Cursor agent**. Same coaching rules (`@Memory.md`), alag focus.

## Polyglot split (locked)

| Language | Kya likhoge | Modules |
|----------|-------------|---------|
| **Go** | Platform API — auth, tenants, billing, gateway, proxy | **00e**, ship 03 → Project C |
| **Python** | AI — RAG, agents, evals (FastAPI) | **00c**, 04–11 |

## Quick start

1. `@Memory.md` — shared context
2. `@modules/XX-.../MODULE.md` — theory + practice
3. `@Projects.md` — SaaS ship spec

**Naye ho?** **00a → 00b → 00c → 00d → 01...** (00e Go optional — pure-Python AI roles ke liye skip OK)

> 🎯 **Kitna zaroori hai? Kya skip karein?** → **[PRIORITY.md](../PRIORITY.md)** padho.
> Target = **application/product AI eng** (YC/remote-US). Legend: 🎯 CORE (must) · ⭐ EDGE (recommended) · ⏭️ OPTIONAL (skip for job — internals/niche; har optional module ke header pe badge hai).
> **Minimum job-ready path:** 00a–00d + 01–07 + 09–13 + 20. Track 3 (16–22) mostly ⏭️ optional.

## Module list

### Track 0 — Prerequisites

| # | Path | Focus |
|---|------|-------|
| 00a | [00a-dev-environment](./00a-dev-environment/MODULE.md) | Docker, Postgres, Redis |
| 00b | [00b-python-async](./00b-python-async/MODULE.md) | async, Pydantic |
| 00c | [00c-fastapi](./00c-fastapi/MODULE.md) | **Python AI** HTTP layer |
| 00d | [00d-ml-ai-foundations](./00d-ml-ai-foundations/MODULE.md) | ML, embeddings |
| 00e | [00e-go-platform](./00e-go-platform/MODULE.md) | **Go platform** API ⭐ NEW |

### Track 1 — LLM + AI (Python) + Gateway (Go)

| # | Path | Focus |
|---|------|-------|
| 01 | [01-llm-apis](./01-llm-apis/MODULE.md) | Tokens, cost, streaming |
| 02 | [02-llm-infra](./02-llm-infra/MODULE.md) | Cache, breaker, rate limit |
| 03 | [03-project-llm-gateway](./03-project-llm-gateway/MODULE.md) | Patterns → **Go Project C** |
| 04–10 | prompts → evals | Python AI depth |
| 11 | [11-project-agentic-workflow](./11-project-agentic-workflow/MODULE.md) | **Project B** ship |

### Track 2 — Advanced (high-paying-role specializations)

> Core 01–11 ke baad. Yeh topics interview mein alag kar dete hain.

| # | Path | Focus |
|---|------|-------|
| 12 | [12-guardrails-safety](./12-guardrails-safety/MODULE.md) | Guardrails, PII, injection defense, OWASP LLM Top 10 |
| 13 | [13-advanced-retrieval](./13-advanced-retrieval/MODULE.md) | Reranking, hybrid search, RRF, HyDE, retrieval eval |
| 14 | [14-finetuning](./14-finetuning/MODULE.md) | SFT, LoRA, DPO, prompt-vs-RAG-vs-finetune decision |
| 15 | [15-voice-multimodal](./15-voice-multimodal/MODULE.md) | Vision, STT/TTS, voice pipeline, latency, multimodal RAG |

### Track 3 — Deep Foundations & Internals (from-scratch / research-adjacent)

> "AI ko andar se samjho + scratch se banao." Top labs (OpenAI/Anthropic) + Devin/framework-builder roles yeh depth poochhte hain. NumPy-heavy, code-from-scratch.
> ⏭️ **Application/product jobs ke liye mostly OPTIONAL** — sirf **20 (Memory & Context)** recommended. Baaki (16, 17, 18, 19, 21, 22) skip OK; curiosity/lab-prep ke liye. Dekho [PRIORITY.md](../PRIORITY.md).

| # | Path | Focus |
|---|------|-------|
| 16 | [16-dl-foundations](./16-dl-foundations/MODULE.md) | NN, backprop, gradient descent, RNN/LSTM/CNN, road to transformers |
| 17 | [17-transformers-scratch](./17-transformers-scratch/MODULE.md) | Self-attention (Q/K/V), multi-head, positional, KV cache, GQA, MLA ⭐ |
| 18 | [18-huggingface-open-models](./18-huggingface-open-models/MODULE.md) | Hub, pipeline/AutoModel, tokenizers, quantization, vLLM/Ollama |
| 19 | [19-agents-first-principles](./19-agents-first-principles/MODULE.md) | Agent loop + tool registry from scratch (no framework) |
| 20 | [20-memory-context](./20-memory-context/MODULE.md) | Short/long-term memory, summarization, context engineering |
| 21 | [21-computer-use](./21-computer-use/MODULE.md) | Perception-action loop, grounding, browser agents, safety |
| 22 | [22-rl-finetuning](./22-rl-finetuning/MODULE.md) | RLHF, reward models, PPO/DPO/GRPO, reward hacking, RL evals |

Full plan: `@LEARNING-PLAN.md` · Spec: `@Projects.md`

> **Padhai quality:** Har MODULE = textbook (`@MODULE-TEACHING-STANDARD.md`). §0 pehle — syntax (Track 0) ya terms (Track 1). Cheat sheet style banned.
