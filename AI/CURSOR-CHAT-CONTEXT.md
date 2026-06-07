# AI Learning — Cursor chat context (continue from here)

**Workspace:** `/Users/vansh/Desktop/Code/Learning/AI`  
**Goal:** Engineer-level AI application work (production mindset, rigor, system design) — not demo / vibe-only coding.  
**Starting point:** “AI ka abhi kuch nahi aata” — is document mein **easy → difficult** order + **har pillar ke prerequisites** hain.  
**Monorepo template (target stack):** `https://github.com/codevoks/turborepo-template` (agar README load na ho to local clone / visibility check karna)

---

## 1. North star (kya “sell” karega)

Target portfolio projects (high signal for strong roles):

| Order | Project | Ek line mein signal |
|------|---------|---------------------|
| 1 | **RAG + eval harness** | Retrieval + quality measurement, citations |
| 2 | **Structured extraction** | Messy docs → validated JSON + human review queue |
| 3 | **LLM gateway** | Routing, budgets, tracing, fallbacks |
| 4 | **Bounded agent** | Tools + allowlists + escalation, not infinite autonomy |

Har project ke liye chaar pillars apply hote hain: **production**, **engineering rigor**, **system design**, **AI/ML product sense**.

---

## 2. Global order: easy → difficult (pehle yeh sequence)

Ye sequence **skills build** karta hai; neeche Phase 0–5 mein detail hai.

1. **Foundations** — HTTP APIs, JSON, auth basics, env/secrets, one DB, Git, TypeScript comfort (ya Python fastAPI + types).
2. **“Dumb” reliable backend** — CRUD + validation + errors + logging; **bina LLM** ke bhi deployable service.
3. **First LLM integration** — single provider, sync calls, timeouts/retries, cost awareness (token counting mental model).
4. **Prompt + structured output** — schemas (Zod/Pydantic), parse/repair loop, no loose string guessing in app code.
5. **Embeddings + vector store** — chunking, metadata, top-k retrieval; measure “did we fetch the right chunks?”
6. **RAG product slice** — ingest → index → chat UI with **citations** + “refuse if insufficient context”.
7. **Evals & regression** — golden set, automated checks, prompt/model version pinning.
8. **Async & scale** — queues/workers, idempotency, rate limits, observability (traces/metrics).
9. **Agents (last)** — tool allowlists, max steps, human-in-the-loop, audit trail.

**Rule:** Agent / multi-agent tab jab 3–8 solid ho. Warna demo flashy, foundation weak lagti hai.

---

## 3. Prerequisites by pillar (matrix)

Legend: **Must** = almost always needed · **Should** = frequent · **Niche** = sometimes / specific roles · **Indirect** = matlab badhiya engineer banne ke liye useful, har AI project mein line-by-line use nahi hoga

### A. Production lens

| Topic | Tier | Notes |
|-------|------|--------|
| Environment config & secrets | Must | 12-factor; never commit keys |
| Logging (structured) | Must | request id, user/tenant id where safe |
| Errors & HTTP status semantics | Must | retryable vs fatal |
| Timeouts, retries, backoff | Must | LLM APIs = flaky |
| Rate limiting / quotas | Should | per user or per API key |
| Basic security | Must | OWASP top-10 awareness, SSRF when calling tools |
| CI (lint/test on PR) | Should | |
| Docker / one deploy path | Should | |
| K8s, multi-region | Niche | senior/staff depth later |
| **Indirect:** SLA thinking, incident postmortems | Indirect | interview stories |

### B. Engineering rigor

| Topic | Tier | Notes |
|-------|------|--------|
| Version control, small PRs | Must | |
| Types + validation at boundaries | Must | schemas for API + LLM outputs |
| Testing (unit + a few integration) | Should | especially parsing and business rules |
| Data migrations discipline | Should | when you have real DB |
| Prompt / model versioning | Should | git tag or table: which prompt hash in prod |
| Eval datasets & regression | Must·later | defines “engineering” vs “vibes” for AI |
| **Indirect:** DSA for interviews | Indirect | often interviewed; not daily on job |

### C. System design

| Topic | Tier | Notes |
|-------|------|--------|
| Client → API → DB mental model | Must | |
| Stateless API servers | Should | |
| Background jobs / queues | Should | ingestion, batch embed, email |
| Caching (HTTP / Redis) | Should | gateway / repeated prompts |
| Idempotency | Should | webhooks, job retries |
| Multi-tenant boundaries | Should | data isolation story |
| Event-driven, CQRS | Niche | bigger systems |
| **Indirect:** CAP, strong consistency debates | Indirect | interviews + rare features |

### D. AI / ML product (application AI)

| Topic | Tier | Notes |
|-------|------|--------|
| What is an LLM (tokens, context window) | Must | |
| Chat vs completion APIs | Must | |
| Embeddings + vector similarity (intuition) | Must | RAG |
| Chunking strategies | Should | overlaps, headers, metadata |
| RAG failure modes | Must | wrong chunk, stale doc, hallucination |
| Structured output / tool calling | Should | extraction & agents |
| Evals (precision/recall-ish on retrieval, task success) | Must·for portfolio | |
| Fine-tuning | Niche | many roles never need day 1 |
| Training from scratch | Indirect | almost never for app engineer path |

---

## 4. Phased study plan (practice before “the big project”)

### Phase 0 — Tooling (1–2 weeks realistic part-time)

- TypeScript **or** Python “comfortable”: functions, modules, async/await, errors.
- HTTP: `GET`/`POST`, status codes, JSON.
- One framework: e.g. Express/Fastify **or** Next API routes **or** FastAPI.
- Git: branch, PR, meaningful commits.

**Practice:** Tiny REST service + in-memory store + validation.

### Phase 1 — Reliable service (no AI)

- DB (Postgres recommended): one real resource, migrations.
- Auth optional v1; if absent, document “phase 2”.
- Structured logging + global error handler.

**Practice:** “Notes API” / “task API” with tests on validation layer.

### Phase 2 — First LLM call (minimal surface)

- Provider SDK, env key, **timeout**, **retry once**, log latency and token usage.
- System + user messages; temperature top-p basic intuition.

**Practice:** One endpoint: “summarize this text” with max input length guard.

### Phase 3 — Structured outputs

- Schema for output; parse; on failure, repair prompt **once** then fail visibly.
- No “JSON in prose” without validation.

**Practice:** Extract `{ title, date, parties[] }` from pasted contract-ish text (even synthetic).

### Phase 4 — RAG core

- Chunking + embedding + vector DB (local ok: sqlite+vec, pgvector, etc.).
- Retrieval-only metrics first: for a fixed doc set, do top-k hit the right chunk?

**Practice:** CLI or simple UI: question → show retrieved chunks (before pretty answer).

### Phase 5 — RAG product + evals

- Citation required in answer UI.
- Golden questions file + script: did answer cite correct chunk? (manual or semi-auto at first.)
- Prompt versioning.

**Practice:** This becomes **portfolio project #1**.

### Phase 6 — Gateway / extraction / agent (pick order per energy)

- Gateway: routing, budgets, tracing.
- Extraction: human review queue for low confidence.
- Agent: allowlisted tools only, max steps, transcripts.

**Portfolio:** Projects #2–4 from section 1.

---

## 5. “Seekh liya par direct use nahi hua” — expected

Ye normal hai; ROI interview + long-term growth mein hai:

- Deep DSA, competitive patterns  
- Exact cloud certification trivia  
- Building a transformer from scratch (unless specializing)  
- Heavy K8s before you have one working Docker deploy  
- Math-heavy stats proofs  

**Seekhna chahiye lekin pehle block mat:** agar Phase 0–2 stuck nahi ho to Phase 3+ mein parallel light reading chalao.

---

## 6. Anti–vibe-coding checklist (engineer bar)

Har milestone pe poochho:

- [ ] Kya iska **failure mode** kya hai aur maine handle kiya?
- [ ] Kya **data / prompt / model version** trace kar sakta hoon?
- [ ] Kya **cost + latency** mere paas numbers hain?
- [ ] Kya main **bad output** ko detect karne ke liye **test / eval** rakhta hoon?
- [ ] Kya UX mein **honesty** hai (“source nahi mila” vs fake confidence)?

---

## 7. Repo already yahan: `ai-engineering-from-scratch`

Is folder mein phased material pehle se ho sakta hai. **Is file ka role:** Cursor mein nayi chat kholte waqt yeh file attach/mention karke bola kar sakte ho: *“`CURSOR-CHAT-CONTEXT.md` padh ke aage continue karo — main Phase X par hoon.”*

**Suggested next line for chat:**  
“My current phase: Phase ___. Stack: ___. Blocker: ___.”

---

## 8. Changelog

- **2026-04-30:** Initial context — prerequisites matrix, easy→hard global order, four target projects, anti-vibe checklist.
