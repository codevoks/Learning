# AI Engineering Portfolio — Build Prompt & Spec

Paste this whole file at the start of a build session. Then name the project (A, B, or C) and ask for the architecture and file structure first, before any code.

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

## Polyglot architecture (deliberate, not keyword collecting)

- **Go** for performance-critical infra: the LLM Gateway and future microservices. Plays to my infra strength and is the right tool for a high-throughput proxy.
- **Python / FastAPI** for AI services: RAG, agents, eval, where the LangGraph / ragas / pgvector ecosystem lives.
- **Node / TypeScript** for the existing real-time and WebSocket layer.

This mirrors the dominant 2026 production pattern. I sell it as "right tool per workload," never as "I know three languages."

## Build order (do not parallelize)

1. FastAPI fundamentals, about one week. This unlocks the AI projects, which is my actual CV gap.
2. **Project A — Agentic RAG + eval** (FastAPI).
3. **Project B — Agentic Workflow Engine** (FastAPI, extends my Zapier clone).
4. **Project C — LLM Gateway** (Go). Learn Go through this build. Goroutines and channels are the only genuinely new part, and my Kafka/async background covers the concurrency mental model.

Ship one project fully before starting the next.

---

## Project A — Agentic RAG over Financial Documents (+ eval harness)

**Goal:** Production RAG question-answering over financial documents (invoices, bank statements, GL entries, reconciliation reports). My domain.

**Build:**

- Ingestion with a chunking strategy tuned for tabular and financial documents.
- Hybrid retrieval: dense embeddings plus BM25 keyword search.
- Cross-encoder reranking on the retrieved set.
- Pluggable vector store behind one interface, with two backends: pgvector (Postgres extension, my strength) and Pinecone (managed). Run the same retrieval against both, benchmark recall and latency, and document when each wins. Default to pgvector, keep Pinecone swappable by config.
- Agentic RAG: query planning, adaptive retrieval, self-correction. Not naive chunk-stuffing.
- Guardrails: indirect prompt-injection defense from retrieved content, structured outputs.
- Eval pipeline: groundedness, answer relevance, hallucination rate via ragas or DeepEval. Offline set of about 200 cases plus LLM-as-judge on production traces. Alarm on regression, not on absolute thresholds.

**Stack:** FastAPI, pgvector + Pinecone (pluggable), BM25, cross-encoder reranker, Anthropic + OpenAI APIs, ragas/DeepEval, Langfuse.

**What I must be able to defend:** why hybrid retrieval over dense-only, the chunking choice, eval design, the injection mitigations, and the managed vs self-hosted vector store tradeoff (when pgvector is enough vs when Pinecone earns its cost: scale, ops burden, filtering, hybrid search, latency).

**Bullet shape:** "Built RAG over [N] financial docs with hybrid retrieval (dense + BM25) and cross-encoder reranking; benchmarked pgvector vs Pinecone (recall@k [X] vs [Y], p95 [A]ms vs [B]ms); nightly ragas evals cut hallucination rate from A% to B%."

## Project B — Agentic Workflow Engine (extends my Zapier clone)

**Goal:** Natural-language-driven workflow automation agent on top of my existing outbox + Kafka Zapier clone, with production safety controls.

**Build:**

- Multi-agent orchestration with LangGraph or the OpenAI Agents SDK.
- Tool-calling with Pydantic structured outputs.
- MCP integration for connecting tools.
- Human-in-the-loop checkpoints before any irreversible action (leverages my savepoint/rollback experience).
- Idempotency and exactly-once execution via my existing outbox pattern.
- Trajectory evaluation plus cost-per-task tracking.
- Least-privilege tool design and a kill switch. This is the OWASP LLM06 "Excessive Agency" mitigation.

**Stack:** FastAPI, LangGraph or OpenAI Agents SDK, MCP, my Postgres outbox/Kafka, DeepEval/Langfuse.

**What I must be able to defend:** why exactly-once matters for agents, how the outbox guarantees it, where the human-in-loop checkpoint sits and why, and the excessive-agency mitigations.

**Bullet shape:** "Built an NL-driven agent workflow engine on a Postgres outbox + Kafka backbone with exactly-once execution, human-in-the-loop checkpoints, and least-privilege tools; tracked cost-per-task and trajectory eval across [N] runs."

## Project C — LLM Gateway (Go)

**Goal:** High-throughput proxy in front of OpenAI and Anthropic.

**Build:**

- Model routing by query complexity (Haiku to Sonnet to Opus).
- Semantic and exact caching in Redis.
- Rate limiting and per-user token budgets.
- Circuit breakers and provider fallback.
- Streaming (SSE) token passthrough.
- Per-request cost tracking, OpenTelemetry tracing, Prometheus metrics.

**Stack:** Go, Redis, OpenTelemetry, Prometheus, provider SDKs.

**What I must be able to defend:** the routing policy, cache invalidation, circuit-breaker thresholds, and the cost model (estimate the per-conversation cost of an N-turn loop with given input/output tokens).

**Bullet shape:** "Built an LLM gateway in Go routing across Haiku/Sonnet/Opus by complexity with Redis semantic caching, circuit breakers, and OpenTelemetry tracing; cut per-query cost [X]% and held p99 under [Y] ms at [Z] RPS."

---

## CV skills to surface (only after each is real and defendable)

RAG, hybrid retrieval, reranking, vector databases (pgvector, Pinecone), agent orchestration, LangGraph, MCP, tool-calling, eval (ragas/DeepEval), LLM observability (OpenTelemetry/Langfuse), cost optimization, model routing, guardrails, prompt-injection defense, FastAPI, Go, Anthropic + OpenAI APIs.

## Writing standards for README and CV text (I publish this)

Clean English. No AI-slop tells. No em dashes, minimal commas, short punchy sentences, no formulaic openers or closers. Avoid: ensure, utilize, leverage, crucial, delve, unlock, "it's worth noting", "this is where X comes in". Write like a sharp engineer typing a real message.

Do not put any employer's internal implementation details in a public repo. Keep the domain framing generic (financial documents, reconciliation), never company-specific.
