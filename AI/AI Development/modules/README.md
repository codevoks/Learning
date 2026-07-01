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

**Naye ho?** **00a → 00b → 00c → 00d → 00e → 01...**

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

Full plan: `@LEARNING-PLAN.md` · Spec: `@Projects.md`

> **Padhai quality:** Har MODULE = textbook (`@MODULE-TEACHING-STANDARD.md`). §0 pehle — syntax (Track 0) ya terms (Track 1). Cheat sheet style banned.
