# AI SaaS Portfolio — Build Prompt & Spec

Each project here is built as a real SaaS product, not a tech demo. The thesis: a thing people would plausibly pay for is a far stronger hiring signal than a clean notebook, and the infra that makes a SaaS real (multi-tenancy, usage metering, usage-based billing, cost attribution) is exactly the platform-engineering work my target roles do.

Paste this whole file at the start of a build session in Cursor. Then name the project (A, B, or C) and ask for the architecture and file structure first, before any code. Build each project in two phases inside one codebase (see "Phased build" below). Do not restart or fork for the SaaS version.

---

## Who I am (context for the assistant)

- IIT Delhi, B.Tech Mathematics and Computing, 2024. Backend/platform SWE, ~2 years.
- Production stack: TypeScript, Node.js, Next.js, PostgreSQL, Redis, Kafka, Prisma, Docker, Kubernetes, Prometheus.
- Domain depth: payment infrastructure. Multi-stage async flows with savepoints and rollbacks, AR/AP/GL postings, reconciliation and matching engines, ledger consistency under failure, outbox pattern, exactly-once delivery, partial fills.
- Side projects I can extend: Zapier-style workflow automation (Postgres outbox + Kafka + workers), crypto exchange matching engine (Redis pub/sub, WebSockets, partial fills), real-time collaborative canvas, payment wallet.
- Gap I am closing: no AI/LLM work on my CV yet.
- Target: AI Infrastructure / AI Platform Engineer roles. $100k+ remote or 40+ LPA India. Fintech, AI-infra, and YC startups.
- Positioning: I am not competing as an ML or research candidate. I am the engineer who makes LLM systems production-safe using real distributed-systems experience. That is my moat.

## Non-negotiable build standards

1. Everything must be defendable line by line in an interview. No code I cannot explain, no copied tutorial I cannot reason about. Walk me through the why behind each decision.
2. Production signals over toy demos: error handling, retries, idempotency, observability, eval, cost tracking. A notebook with `model.predict()` is worthless.
3. Every project ships with a live demo link and a GitHub README that documents the design decisions and trade-offs.
4. Every resume bullet carries a real measured number: latency, throughput, cost reduction, or an eval metric. Measure before and after.
5. Ground projects in my payment/fintech domain where possible so I can defend both the system and the domain.
6. Struggle-first. Give me the design, let me attempt the code, unblock a single step only when I am stuck. Do not hand me full solutions I have not reasoned through.

## Shared SaaS platform layer (the spine every project plugs into)

This is the part that makes each project a product and also the part that maps directly to my payments background. Build the spine once, reuse it across all three.

- **Multi-tenancy with hard isolation.** Org accounts with members. Every row, namespace, and cache key scoped by tenant. One tenant must never see another's data. For the RAG product this is a security requirement, not a nice-to-have.
- **Usage metering.** Define the billable unit per product and count it reliably. Every billable event is recorded idempotently so a retry never double-counts. This is where my outbox / exactly-once experience is the actual differentiator: billing is only correct if usage events are exactly-once.
- **Usage-based billing.** Stripe metered billing wired to the meter. Idempotent usage reporting, reconciliation between my meter and Stripe's (a job I already know from bank reconciliation).
- **Per-tenant cost attribution, budgets, and quotas.** Soft warn and hard stop. Track real LLM cost per tenant so margin is visible.
- **Admin and observability per tenant.** Usage, cost, latency, error rate. The same Prometheus/OpenTelemetry discipline I already use.

I can defend this whole spine from day one because it is payments and reconciliation with an AI workload on top. That is the narrative: the AI platform engineer who gets billing and metering right.

## Scope guardrail (so I actually ship)

Build the MVP that proves the core value plus the spine above. Do not build a full company. Skip the marketing site, complex onboarding, and deep team-permission matrices. Two real demo tenants with live usage and a working Stripe test-mode invoice is enough to tell the whole story. One project fully, with the spine, before the next.

## Polyglot architecture (deliberate — Go platform + Python AI)

**Decision (locked):** App/platform backend **Go**. AI workloads **Python / FastAPI**. Node optional for real-time UI later.

```
┌─────────────────────────────────────────────────────────┐
│  GO — Platform API (public, multi-tenant SaaS spine)     │
│  auth · API keys · tenants · metering · Stripe · quotas  │
│  proxies to Python · Project C gateway lives here too      │
└───────────────────────────┬─────────────────────────────┘
                            │ internal HTTP (Docker network)
┌───────────────────────────▼─────────────────────────────┐
│  PYTHON — AI microservices (not public-facing)           │
│  Project A: RAG + agentic retrieval + eval               │
│  Project B: LangGraph agents + MCP + trajectory eval     │
└─────────────────────────────────────────────────────────┘
```

- **Go** for performance-critical infra and **everything customers hit**: LLM Gateway (Project C), billing, metering, tenant isolation. Plays to distributed-systems strength; learn via module **00e** then ship.
- **Python / FastAPI** for AI services only: RAG, agents, eval, where LangGraph / ragas / pgvector live. Learn via **00c** + modules **04–11**.
- **Node / TypeScript** optional for existing real-time / WebSocket layer — not the AI spine.

**Phased build per project:**

| Phase | Go | Python |
|-------|-----|--------|
| **Phase 1** (core value) | Skip or minimal `/health` | Full AI core — learn + ship working demo |
| **Phase 2** (SaaS spine) | **Platform wrap** — auth, metering, Stripe, tenant isolation | Same Python services, called internally |

This mirrors the dominant 2026 production pattern. Interview line: *"Right tool per workload — platform in Go, agents in Python, contract via internal API."*

## Build order (do not parallelize)

1. **Track 0 + 00e Go** + FastAPI fundamentals (~2 weeks). Unlocks polyglot projects.
2. **Project A — Financial Document Intelligence** — Phase 1 Python RAG → Phase 2 Go platform spine (build spine here first; reuse in B and C).
3. **Project B — AI Workflow Automation** — Python agents + existing outbox/Kafka; Go platform from A reused.
4. **Project C — LLM Gateway** — **Go** (routing, cache, budgets) — concepts from module 03, ship in `platform/` or `services/gateway/`.

Ship one project fully before starting the next.

## Zero topic left behind (`@TOPIC-COVERAGE.md`)

**Rule:** Everything in `@Prompt.md` hot topics must ship in **A + B + C combined** — RAG, LangGraph, agents, function calling, structured outputs, pgvector, MCP, prompt engineering, memory, tools, multi-agent, LLMOps, evals, multimodal basics, plus Postgres/Redis/Kafka/observability/cost control.

Before calling portfolio “done”: walk the master checklist in `TOPIC-COVERAGE.md` — **no empty rows**.

## Monorepo layout (Turborepo + pnpm + polyglot)

One repo. All topics. One spine.

```
portfolio/
├── apps/
│   └── web/                    # Next.js — dashboard, HITL UI, tenant admin, demo
├── platform/                   # GO — auth, tenants, metering, Stripe, BFF
├── services/
│   ├── rag/                    # PYTHON — Project A
│   ├── agent/                  # PYTHON — Project B (LangGraph, MCP)
│   └── gateway/                # GO — Project C
├── packages/
│   └── shared-types/           # OpenAPI / JSON schemas (Go ↔ Python contract)
├── docker-compose.yml
├── turbo.json
├── pnpm-workspace.yaml
└── TOPIC-COVERAGE.md           # checkbox master — don't ship until green
```

**Turborepo**: `pnpm turbo dev` runs web + services. **Prompt.md stack** = covered.

Each project is built in two phases inside the same repo. Do not write a throwaway learning version and then restart for the SaaS version. The learning version is literally phase 1 of the SaaS version.

- **Phase 1 (core, single-user).** Build the core value working end to end for one user, no tenancy, no billing. This is where I learn the new concept (RAG, agents, Go gateway). Get it to "it works and I understand every line," then stop. Do not over-polish, because phase 2 will change this code anyway.
- **Phase 2 (SaaS).** Wrap the shared platform spine around the same core: multi-tenancy and isolation, usage metering, Stripe usage-based billing, per-tenant cost attribution, per-tenant observability. This is what goes on the CV and in the live demo.

When I name a project, build phase 1 first. Only move to phase 2 once phase 1 works and I can explain it. The spine code from the first project's phase 2 is reused in later projects, not rewritten.

---

## Project A — Financial Document Intelligence (Agentic RAG SaaS)

**Goal:** A SaaS where finance and ops teams upload their documents (invoices, bank statements, GL entries, reconciliation reports) and get grounded Q&A plus reconciliation help. My domain.

**Product thesis (who pays, for what):** Small finance teams, bookkeepers, and fractional CFOs drown in statements and invoices. They pay to ask plain-language questions across their own documents and get answers they can trust with a citation. Billable unit: documents ingested plus queries run. Tiers by document volume and query volume.

**Build:**

- Ingestion with a chunking strategy tuned for tabular and financial documents.
- Hybrid retrieval: dense embeddings plus BM25 keyword search.
- Cross-encoder reranking on the retrieved set.
- Pluggable vector store behind one interface, with two backends: pgvector (Postgres extension, my strength) and Pinecone (managed). Run the same retrieval against both, benchmark recall and latency, and document when each wins. Default to pgvector, keep Pinecone swappable by config.
- Per-tenant isolation in the vector layer: pgvector scoped by tenant_id with enforced row-level checks, Pinecone via per-tenant namespaces. Cross-tenant leakage is a first-class eval case, not an afterthought.
- Agentic RAG: query planning, adaptive retrieval, self-correction. Not naive chunk-stuffing.
- **LangChain**: document loaders + text splitters for ingest; **LangGraph** for agentic retrieval loop (query plan → retrieve → grade → rewrite).
- **Function calling + structured outputs**: agent tools (`search_docs`, `get_line_items`) return Pydantic schemas with citations.
- **Memory**: per-tenant conversation threads (Postgres or Redis) — follow-up questions without re-upload.
- **Multimodal basics**: scanned invoices / PDF images via vision API (GPT-4o or Claude) → OCR text → same RAG pipeline.
- Guardrails: indirect prompt-injection defense from retrieved content, structured outputs with citations.
- Eval pipeline: groundedness, answer relevance, hallucination rate via ragas or DeepEval. Offline set of about 200 cases plus LLM-as-judge on production traces. Alarm on regression, not on absolute thresholds. Cross-tenant leakage test must always pass.
- Spine: meter documents and queries per tenant, attribute LLM cost per tenant, Stripe metered billing.

**Stack:** **Python** — FastAPI, pgvector + Pinecone, BM25, cross-encoder, Anthropic + OpenAI, ragas/DeepEval, Langfuse. **Go** (phase 2) — platform API, metering, Stripe, tenant isolation, proxy to RAG service.

**What I must be able to defend:** why hybrid retrieval over dense-only, the chunking choice, eval design, the injection mitigations, the managed vs self-hosted vector store tradeoff (when pgvector is enough vs when Pinecone earns its cost: scale, ops burden, filtering, hybrid search, latency), and how tenant isolation is enforced and tested.

**Bullet shape:** "Built a multi-tenant RAG product over financial docs with hybrid retrieval (dense + BM25) and cross-encoder reranking; benchmarked pgvector vs Pinecone (recall@k [X] vs [Y], p95 [A]ms vs [B]ms); enforced per-tenant isolation with a zero-leakage eval gate; nightly ragas evals cut hallucination rate from A% to B%; metered usage billed via Stripe."

## Project B — AI Workflow Automation (Agentic SaaS, extends my Zapier clone)

**Goal:** A SaaS where users describe automations in natural language and an agent plans, connects tools, and runs them safely. The Zapier/Lindy/Gumloop category, AI-native, on top of my existing outbox + Kafka backbone.

**Product thesis (who pays, for what):** Ops teams and solo founders pay to automate manual multi-step work without writing code. Billable unit: task runs (executions). Tiers by monthly run volume. The pitch is reliability: runs are billed and executed exactly once, never dropped, never doubled.

**Build:**

- Multi-agent orchestration with **LangGraph** (primary — not optional).
- **LangChain** utilities where LangGraph doesn't cover (loaders, parsers) — same Python service.
- Tool-calling with Pydantic structured outputs.
- **MCP** integration for connecting tools (at least 2 MCP servers: read + write).
- **Memory**: workflow run state + user automation history across sessions (Postgres).
- Human-in-the-loop checkpoints before any irreversible action (leverages my savepoint/rollback experience).
- Idempotency and exactly-once execution via my existing outbox pattern. This is also the billing guarantee: each completed run is metered exactly once.
- Per-tenant workflow isolation and execution quotas.
- Tenant-scoped, encrypted credential vault for tool connections.
- Trajectory evaluation plus cost-per-task tracking.
- Least-privilege tool design and a kill switch. This is the OWASP LLM06 "Excessive Agency" mitigation.
- Spine: meter task runs per tenant, attribute LLM cost per run, Stripe metered billing, per-tenant budgets with hard stop.

**Stack:** **Python** — FastAPI, LangGraph or OpenAI Agents SDK, MCP, DeepEval/Langfuse. **Go** — platform API (reuse Project A spine), outbox/Kafka workers can stay Go or existing stack. Postgres outbox/Kafka for exactly-once.

**What I must be able to defend:** why exactly-once matters for both execution and billing, how the outbox guarantees it, where the human-in-loop checkpoint sits and why, the excessive-agency mitigations, and how the credential vault isolates tenants.

**Bullet shape:** "Built a multi-tenant AI workflow SaaS on a Postgres outbox + Kafka backbone with exactly-once execution and billing, human-in-the-loop checkpoints, least-privilege tools, and an encrypted per-tenant credential vault; metered [N] task runs with zero double-billing across [N] runs; usage billed via Stripe."

## Project C — LLM Gateway as a Service (Go)

**Goal:** A SaaS gateway that sits in front of OpenAI and Anthropic and gives dev teams one endpoint with routing, caching, cost control, and observability. The Portkey/Helicone/OpenRouter category.

**Product thesis (who pays, for what):** Dev teams shipping LLM features pay to stop wiring providers, caching, and cost tracking themselves. They get one endpoint, automatic cost savings from routing and caching, and a usage dashboard. Billable unit: requests or tokens with a markup, or a flat tier plus the observability dashboard. This is the most naturally-SaaS of the three because the product is itself a metering and billing problem.

**Build:**

- Per-tenant API keys, with key rotation and scoping.
- Model routing by query complexity (Haiku to Sonnet to Opus).
- Semantic and exact caching in Redis (cache keys scoped per tenant).
- Per-tenant rate limiting, token budgets, and quotas with soft warn and hard stop.
- Circuit breakers and provider fallback.
- Streaming (SSE) token passthrough.
- Per-request and per-tenant cost tracking, OpenTelemetry tracing, Prometheus metrics, per-tenant usage dashboard.
- Spine: meter requests/tokens per tenant, Stripe metered billing, margin visible per tenant (provider cost vs billed amount).

**Stack:** Go, Redis, OpenTelemetry, Prometheus, provider SDKs, Stripe.

**What I must be able to defend:** the routing policy, cache invalidation and per-tenant cache scoping, circuit-breaker thresholds, the cost model (per-conversation cost of an N-turn loop with given input/output tokens), and how metering stays accurate under retries and streaming.

**Bullet shape:** "Built a multi-tenant LLM gateway SaaS in Go routing across Haiku/Sonnet/Opus by complexity with per-tenant API keys, Redis semantic caching, budgets, and circuit breakers; cut per-query cost [X]% and held p99 under [Y] ms at [Z] RPS; metered usage and billed via Stripe with per-tenant margin tracking."

---

## CV skills to surface (only after each is real and defendable)

RAG, hybrid retrieval, reranking, vector databases (pgvector, Pinecone), agent orchestration, LangGraph, MCP, tool-calling, eval (ragas/DeepEval), LLM observability (OpenTelemetry/Langfuse), cost optimization, model routing, guardrails, prompt-injection defense, multi-tenancy, usage metering, usage-based billing (Stripe), FastAPI, Go, Anthropic + OpenAI APIs.

## Writing standards for README and CV text (I publish this)

Clean English. No AI-slop tells. No em dashes, minimal commas, short punchy sentences, no formulaic openers or closers. Avoid: ensure, utilize, leverage, crucial, delve, unlock, "it's worth noting", "this is where X comes in". Write like a sharp engineer typing a real message.

Do not put any employer's internal implementation details in a public repo. Keep the domain framing generic (financial documents, reconciliation), never company-specific.
