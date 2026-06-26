# AI Development — Shared Memory

> Har module ke liye alag agent banao. Naya agent start karte waqt `@Memory.md` + `@modules/XX-.../MODULE.md` + apni `@modules/XX-.../NOTES.md` do.

## Learner profile

| Field | Detail |
|-------|--------|
| Name | Vansh Kumar Singh |
| Education | B.Tech Mathematics & Computing, IIT Delhi (2024) |
| Current role | SDE @ Rootstock (Jun 2024–present) |
| AI/LLM baseline | **Zero** — pehli baar seekh rahe ho |
| Strength | Distributed systems, async chains, matching engines, outbox/Kafka, savepoints, Postgres, Redis, observability |
| Goal | 2026 YC-level AI + backend skills → remote US / high-paying roles |
| Timeline | Tight — speed matters, depth bhi chhodna nahi |
| **Learning style** | **Strong visual learner** — diagrams pehle, text baad; redraw se recall |
| **Content preference** | **Sab ek jagah** — MODULE.md = poori theory; practice/ = code; **bahar links nahi**; chat = doubt + code review only |

## Learning model (Vansh ne choose kiya)

```
MODULE.md (theory, Hinglish, diagrams)  →  practice/ (stubs, tum complete)
         ↓ doubt / code check
    Cursor chat (teacher — recall, review, explain)
```

- **Links optional appendix** — primary padhai MODULE mein
- **Cursor fayda** = likhwaye, check kare, samjhaye — link list nahi
- Coach **kabhi** "jaake doc padho" primary answer mat do — pehle MODULE + explain in chat

## Visual learning rules (coach + self-study)

0. **Ek jagah**: Theory MODULE · Practice `practice/` · Chat = doubt only. `@HOW-TO-STUDY.md`
1. **Har concept = diagram pehle** — mermaid/ASCII/architecture, phir explanation
2. **Har MODULE.md** mein `## Visual map` section hai — **wahan se shuru karo**
3. **Session end ritual**: diagram bina dekhe redraw karo (paper / Excalidraw / NOTES.md)
4. **Coach responses**: Concept Breakdown mein kam se kam **1 diagram** (mermaid ya ASCII)
5. **Compare visually**: Node/Express vs FastAPI, sync vs async, training vs inference — side-by-side
6. **Master visual index**: `@VISUAL-STUDY-GUIDE.md` — poori journey ek page pe

**Obsidian**: Reading view (`Cmd+E`) → mermaid render. NOTES mein section: `## My diagrams`  
**Excalidraw**: Installed (`obsidian-excalidraw-plugin` v2.24.2) — redraw challenges ke liye `diagrams/` folder. `Cmd+P` → "Excalidraw: Create new drawing"

## Coaching rules (non-negotiable)

1. **Hinglish** — concepts simple Hindi+English mix mein
2. **MODULE.md = textbook** — poori theory wahan honi chahiye; chat mein dubara textbook mat likh unless doubt
3. **No full solutions** — practice stubs complete karwao, review karo
4. **Vansh code likhega** — tum check, hint, passing criteria
5. **Har doubt answer**: diagram + trade-off + "practice mein try karo"
6. **Real engineer mindset** — production, cost, reliability

## Tool split

| Tool | Role |
|------|------|
| Claude / learning agent | Seekhna, recall, exercises, architecture thinking |
| Cursor | Build, ship, implement projects |

## Stack (learning + projects) — polyglot locked

| Layer | Language | Modules |
|-------|----------|---------|
| **Platform / app API** | **Go** (chi, pgx, Redis) | **00e**, 03 patterns → Project C + phase 2 spine |
| **AI services** | **Python / FastAPI** | 00c, 04–11 → Projects A/B AI cores |
| **Data** | Postgres (+ pgvector), Redis, Kafka | 00a |
| **Obs** | OpenTelemetry, Langfuse, Prometheus | 02, 10 |
| **Frontend** (optional) | Next.js | existing skill |

```
Client → Go platform API → Python AI service → LLM providers
```

**Go nahi aati** — module **00e-go-platform** pehle Project phase 2 se pehle. Phase 1 AI demos Python-only OK.

## CV anchors → AI learning hooks

Use these jab bhi naya concept samjhana ho — Vansh ka existing brain yahi se connect karta hai:

| Past experience | AI concept hook |
|-----------------|-----------------|
| 5-stage async refund chain + savepoints | Agent step graphs, rollback, HITL checkpoints |
| Two-pointer credit matching | Multi-step tool routing, partial fills = partial agent plans |
| Outbox + Kafka workers (Zapier clone) | Exactly-once agent execution, idempotent tool calls |
| Matching engine (LIMIT/MARKET, Redis) | Model router by complexity (Haiku/Sonnet/Opus) |
| Redis Pub/Sub → WebSockets | SSE streaming token-by-token |
| Prometheus /metrics | Cost + latency tracing per LLM request |
| Zod validation | Pydantic structured outputs + tool schemas |
| Bank recon 4-strategy cascade | Fallback chains when LLM provider fails |
| CSV import + chunked writes | Batch embedding / RAG ingestion pipelines |

## Portfolio projects (ship order — `@Projects.md`)

Har project = **real SaaS** (multi-tenancy, usage metering, Stripe billing, per-tenant cost). **Phased build**: phase 1 = core single-user, phase 2 = SaaS spine wrap. Ek codebase, do phases — throwaway demo nahi.

| Order | Project | Go (platform) | Python (AI) | Modules |
|-------|---------|---------------|-------------|---------|
| 1 | **A — Financial Document Intelligence** | Phase 2: spine | Phase 1+2: RAG/agents | 04, 05, 10, **00e** |
| 2 | **B — AI Workflow Automation** | Reuse A platform | LangGraph, MCP, eval | 06–11 |
| 3 | **C — LLM Gateway as a Service** | **Full gateway** | N/A (proxy only) | 01–03, **00e** |

**Ship one fully before the next.** Shared SaaS spine reuse across A → B → C.

**Topic coverage**: `@TOPIC-COVERAGE.md` — **Prompt.md ke saare hot topics; kuch chhodna nahi.**

**Build session prompt**: paste `@Projects.md` at start, name project A/B/C, architecture first then code.

**Coach persona** (Hinglish, no full code): `@Prompt.md`  
**Full SaaS spec + bullet shapes**: `@Projects.md`

## Module map & agent routing

### Track 0 — Prerequisites (pehle yeh, phir LLM)

| # | Folder | Agent focus | Unlocks |
|---|--------|-------------|---------|
| 00a | `modules/00a-dev-environment` | Docker, Postgres, Redis, Python venv | 00b |
| 00b | `modules/00b-python-async` | async/await, Pydantic (= Zod) | 00c |
| 00c | `modules/00c-fastapi` | Routes, Depends, middleware, SSE stub | 00d, Project 1 |
| 00d | `modules/00d-ml-ai-foundations` | ML basics, embeddings, **TensorFlow intro** | 00e, 01 |
| 00e | `modules/00e-go-platform` | **Go platform API**, proxy to Python, metering mindset | 01, Project phase 2 |

### Track 1 — LLM & AI (Python services)

| # | Folder | Agent focus | Unlocks |
|---|--------|-------------|---------|
| 01 | `modules/01-llm-apis` | Tokens, messages, streaming, cost math | Everything LLM |
| 02 | `modules/02-llm-infra` | Rate limits, semantic cache, circuit breakers | 03, Project C |
| 03 | `modules/03-project-llm-gateway` | Gateway patterns — **ship in Go** (Project C) | Project C |
| 04 | `modules/04-prompt-engineering` | System prompts, few-shot, JSON mode | Project A |
| 05 | `modules/05-rag-pgvector` | RAG pipeline — **Python service** | Project A phase 1 |
| 06 | `modules/06-tools-function-calling` | Tool schemas, structured outputs | Agents |
| 07 | `modules/07-agents-langgraph` | State machines, loops, memory | Project B AI |
| 08 | `modules/08-mcp` | Model Context Protocol, tool servers | Interop |
| 09 | `modules/09-multi-agent-hitl` | Orchestration, approval gates | Safe agents |
| 10 | `modules/10-evals-llmops` | DeepEval, Langfuse, regression | Production agents |
| 11 | `modules/11-project-agentic-workflow` | **Project B** — Python agents + Go platform | Portfolio |

## Prerequisites honesty

- **FastAPI**: **00c** — Python **AI services** only (RAG, agents, eval)
- **Go**: **00e** — **platform backend** (auth, billing, metering, gateway) — **nahi aati abhi, is module se seekho**
- **TensorFlow**: **00d** — interview + RAG foundation; inference mostly API
- **Visual learning**: Har module `## Visual map` + `@VISUAL-STUDY-GUIDE.md` — diagram pehle, redraw se recall

Full curriculum + hooks: `@LEARNING-PLAN.md`

## Visual roadmap (Canvas)

**Kya hai**: Live React panel — chat ke saath side-by-side roadmap + **clickable buttons** jo `MODULE.md` editor mein khol dete hain.

**Kaise kholo**: [ai-learning-roadmap.canvas.tsx](/Users/vansh/.cursor/projects/Users-vansh-Desktop-Code-Learning-AI-AI-Development/canvases/ai-learning-roadmap.canvas.tsx) → side panel / Open Canvas

**Kahan stored hai**:

| What | Path |
|------|------|
| Canvas UI (React source) | `~/.cursor/projects/.../canvases/*.canvas.tsx` |
| Canvas saved state | same folder, `*.canvas.data.json` |
| Module knowledge (asli content) | `AI Development/modules/XX/MODULE.md` |

Har module card: **MODULE.md** = syllabus · **NOTES.md** = tumhari learnings · **New agent** = coach chat spawn

## Padhai bina Cursor ke (read anywhere)

**Short answer**: Haan — **asli content sab `.md` files mein hai**, kahin bhi padh sakte ho. **Canvas + AI coach** sirf Cursor ke andar.

| Kya | Cursor chahiye? | Kahan padho |
|-----|-----------------|-------------|
| `MODULE.md`, `LEARNING-PLAN.md`, `Memory.md` | Nahi | GitHub, Obsidian, phone, browser |
| `NOTES.md` (apni learnings) | Edit ke liye kuch bhi | Same — kisi bhi MD editor se |
| Canvas (clickable roadmap) | Haan | Cursor only |
| Coach agent (recall, exercises) | Haan | Cursor chat / Claude app with @files |
| Code likhna | Haan (Cursor) | Tab hi workspace kholo |

**Suggested split**

- **Commute / couch / phone**: `LEARNING-PLAN.md` + current `MODULE.md` — GitHub app ya Obsidian vault (`AI Development` folder open karo)
- **Active recall + drills**: Cursor agent (ya Claude web pe files paste/@ mention)
- **Implementation**: Cursor — assignments + projects

**Obsidian (recommended offline)**: Vault already configured — open folder `AI Development` in Obsidian → start at [[Home]]. Bookmarks: Home, LEARNING-PLAN, Module 01, Memory. Snippet `learning-readable` enabled for couch reading.

**GitHub**: Repo push karo → phone/laptop browser se `modules/01-llm-apis/MODULE.md` directly readable.

Canvas = **navigation convenience inside IDE**. Knowledge = **markdown = portable forever**.

## Per-module agent prompt (copy-paste)

```
Tu Vansh ka AI coach hai — @Memory.md aur @modules/XX-.../MODULE.md follow kar.
Vansh visual learner hai — har Concept Breakdown mein diagram (mermaid/ASCII) do.
Module XX pe focus. MODULE.md ka "Visual map" pehle walk karo.
Pehle active recall, phir exercise. Code mat likh — Vansh likhega.
Hinglish. Har response mein 5 sections (Concept → Recall → Exercise → Guidance → Scale).
Session end: "Redraw challenge" assign karo.
```

## Progress tracking

- Har session ke baad `@modules/XX/NOTES.md` update karo (session log table)
- Module complete = assignments pass + project criteria (if applicable) + recall answers saved

## Open decisions

- [ ] FastAPI monorepo layout finalize
- [ ] Langfuse vs self-hosted OTEL only for Project 1
- [ ] Semantic cache: embedding model choice (cost vs quality)

## Key files

| File | Role |
|------|------|
| `@Prompt.md` | Coach persona — Hinglish, active recall, no full code (renamed from `PROMPT.md`) |
| `@Projects.md` | SaaS portfolio spec — Projects A/B/C, phased build, spine, CV bullets |
| `@Memory.md` | Shared rules, CV hooks, module routing (this file) |
| `@LEARNING-PLAN.md` | Full curriculum syllabus |

## Last updated

2026-06-22 — Polyglot locked: Go platform (00e) + Python AI; Projects A/B/C updated
