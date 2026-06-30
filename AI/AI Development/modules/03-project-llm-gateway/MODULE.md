# Module 03 — LLM Gateway (concepts → Project C)

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 02](../02-llm-infra/MODULE.md) · Next → [Module 04](../04-prompt-engineering/MODULE.md)

> **Format**: Textbook — §0 terms pehle (gateway, BFF, router), prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`
> **Ship spec**: `@Projects.md` **Project C** (Go). Yeh module patterns sikhata hai; production ship Go mein.

## At a glance

| | |
|---|---|
| Prerequisites | Modules 01–02 · `@Projects.md` · 00a Redis · 00e Go (Phase 2 ship) |
| Duration | ~2–3 weeks (7 milestones) |
| Project? | Yes — learning sandbox Python; ship Project C Go |
| Exit test | Gateway architecture + "40% cost cut" claim bina notes ke defend karo |

## Yeh module kis baare mein hai

Module 01 ne provider call sikhaya, 02 ne protective patterns (rate limit, cache, breaker). Ab in sab ko **ek product** mein bundle karte hain — **LLM Gateway**. Yeh wahi single service hai jisko saari client apps call karti hain, aur jo andar se routing, caching, budgets, fallback, aur billing sambhalti hai. Yeh tumhara flagship Project C hai (Go mein ship hoga); yeh module uske patterns Python sandbox mein wire karwata hai.

Mental model: gateway ek **bank ka branch counter** hai — client ko ek hi address milta hai, andar ka routing/limits/audit/billing sab chhupa rehta hai. Sabse important — provider keys client ke paas kabhi nahi hoti, sirf gateway ke paas. §0 mein gateway, BFF, router jaise shabd zero se.

```
Clients (web, mobile, internal) → LLM GATEWAY (single front door)
   auth │ rate limit │ cache │ router │ budget │ breaker │ OTEL
                          ▼
                  Provider A → (fail) → Provider B
```

**Redraw challenge**: Poora gateway — router, cache, budgets, fallback chain, OTEL — sab boxes ke saath bina dekhe banao.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms | `@Projects.md` Project C overview |
| 2 | §1 Thesis + §2 Lifecycle | **M1** gateway skeleton |
| 3 | §3 Model router | **M3** complexity router |
| 4 | §4 Cache + §5 Budgets | **M4**, **M5** |
| 5 | §6 Fallback | **M2** fallback router |
| 6 | §7 Tracing | **M6** tracing stub |
| 7 | §8 Milestones + SSE | **M7** stream passthrough + interview NOTES |

---

## Learning hooks (fintech parallels)

Gateway ≈ central OMS (orders ek pipe se); complexity router ≈ matching-engine price tiers (simple vs complex order alag venue); per-tenant budget ≈ account credit limit/margin; token metering ≈ per-fill commission → invoice; outbox billing events ≈ usage event → Stripe.

---

## Theory

### §0. Terms pehli baar — gateway vocabulary (40 min)

**Gateway.** Ek HTTP service jisko saari client apps call karti hain, aur jo andar se OpenAI/Anthropic/etc. ko forward karti hai. Client gateway ke public URL + gateway-issued API key se baat karta hai; provider keys sirf gateway ke paas. Ek gateway kai backends (multi-provider) sambhal sakti hai, aur har customer org ek **tenant** hota hai (`org_42`) jiska billing aur cache alag rehta hai. Tumhara app seedhe NYSE ko order nahi bhejta — broker gateway se; LLM gateway ka role bilkul wahi hai.

**BFF (Backend-for-Frontend).** Ek related idea — client-type-specific API layer (mobile ke liye alag shape, web ke liye alag). Project C gateway BFF-jaisा hai par AI domain ke liye, jiska focus routing/cache/cost hai, na ki UI shaping. (Yeh distinction interview mein poochha ja sakta hai — gateway sirf proxy nahi, balki proxy + cache + limits + billing + observability hai.)

**Router.** Gateway ka decision engine: incoming query dekhkar **model tier** aur **provider** chunता hai — simple FAQ Haiku pe (sasta), summarize Sonnet pe (balanced), 200-line code Opus pe (mehenga, smart). Matching-engine parallel: chhota retail order internalize, bada block trade specialized venue pe — complexity ke hisaab se routing.

**Metering aur budget.** Metering matlab har request ke tokens ginकar accumulate karna. **Soft budget** ek warning hai (abhi allow, par header se bata do), **hard budget** ek stop (402 Payment Required ya 429). `402 Payment Required` quota khatam hone ka SaaS-common pattern hai.

> **Ruko, socho:** Client ke perspective se, seedhe OpenAI call karne ke bajaye gateway ke through jaane ke do faayde kya hain? (Jawab: (1) ek hi gateway key — provider keys app mein leak nahi hote; (2) automatic cost savings + cost visibility — router/cache + per-request billing data, jo seedhe call mein milta hi nahi.)

#### §0 common galatfehmiyaan

| Galat soch | Sach |
|-----------|------|
| "Gateway = bas proxy" | Proxy + cache + limits + billing + observability |
| "Ek global cache" | Tenant-scoped mandatory |
| "Router = sirf load balancer" | Model quality/cost routing bhi |

---

### §1. Gateway kya hai — Project C ki thesis

Problem yeh hai: dev teams alag-alag OpenAI keys use kar rahi hain, alag retry, alag cost tracking — company FinOps-blind hai aur security risk hai. Product thesis simple hai: **LLM Gateway as a Service** — har team ko ek gateway key do, andar se cost bachao (router + cache), usage dashboard + Stripe billing do, aur observability (trace_id, cost per request) do.

Do phases mein banta hai: pehle yeh module (Python FastAPI sandbox) jahan tum M1–M7 patterns wire karte ho, phir Project C (Go platform, 00e) jahan yeh multi-tenant SaaS ban jaata hai. Sabse zaroori security shape:

```
❌ Mobile app ──sk-openai──► OpenAI        (key app mein = leak)
✅ Mobile app ──gw_key──► LLM Gateway ──provider_key──► OpenAI
                              ├── Redis (cache, limits, budget)
                              └── OTEL / billing outbox
```

> **→ Practice M1** (pass: health + single provider passthrough curl).

---

### §2. Architecture — request lifecycle

Yeh module ka dil hai, aur interview mein tumhe yeh whiteboard karna aayega. Bina ek **ordered pipeline** ke middleware random order mein chalegा — budget check cache ke baad ho gaya to galat. Isliye lifecycle pehle define karo. Har request in steps se guzarti hai:

```
1  → API key authenticate → tenant_id resolve
2  → Rate limit (Redis) — over → 429
3  → Budget check — hard over → 402
4  → Cache lookup (exact phir semantic)
   4a → HIT → return + X-Cache-Hit: true (steps 5–7 skip)
5  → Router → model + provider pick
6  → Circuit breaker wrap — OPEN → fallback (§6)
7  → Provider call (stream ho to SSE passthrough)
8  → usage parse → cost_usd
9  → Redis budget update + cache store
10 → OTEL span + structured log emit
11 → Response + trace_id header return
```

Order pe gaur karo — **rate limit aur budget step 7 (provider call) se pehle** hain. Yeh jaanboojhke hai: agar budget check provider call ke *baad* karo, to tum paisa already kharch kar chuke ho, stop ka koi matlab nahi raha. Pehle gate, phir kharcha. Aur cache hit (4a) seedhe return karta hai — provider ko chhuता hi nahi, yahi sabse sasta path hai. Client ko response headers se transparency milti hai: `X-Trace-Id` (debug), `X-Cache-Hit`, `X-Model-Used` (kaunsा model actually chala), `X-Budget-Warning`.

> **Ruko, socho:** Agar tum budget check ko step 9 pe (provider call ke baad) le jao, to product mein kya tootega? (Jawab: budget kabhi enforce nahi hoga effectively — tenant pehle hi tokens kharch kar chuka hoga jab tak tum "stop" karte ho. Hard stop ko kharche se pehle hona zaroori hai.)

> **→ Practice M1, M7** (skeleton + SSE end-to-end).

---

### §3. Model router — complexity-based routing

Agar har query Opus pe bhejoge, margin zero (Opus mehenga). Har query Haiku pe bhejoge, complex code fail ho jaayega (Haiku weak). Isliye **automatic tier-pick** chahiye — query ki complexity dekhkar sahi model.

Teen buckets: **simple** (short, FAQ, classify — "What are your hours?"), **medium** (summarize, multi-step — "Summarize this email"), **complex** (code, reasoning, long context — "Debug this 200-line function"). Classify karne ke kai tareeke hain: rules (`len`, keywords — free aur fast par brittle), ek chhota LLM call (flexible par extra cost), ya embedding-vs-exemplars (tunable par setup chahiye). Starter ke liye simple rules kaafi hain:

```python
def classify(query: str) -> str:
    if len(query) < 50:
        return "simple"      # → haiku tier
    if "```" in query or len(query) > 500:
        return "complex"     # → opus tier
    return "medium"          # → sonnet tier
```

Logic seedha hai: chhote queries aksar FAQ hote hain (haiku), code-block marker ya bahut lambा input heavy model maangता hai (opus), baaki beech mein (sonnet). Yeh return strings config mein actual model IDs se map hote hain.

Ab interview ka classic sawaal — **"40% cost cut" kaise defend karoge?** Jawab measurement se aata hai, dawe se nahi: before/after average cost per request naapo, cache-hit-rate dekho (jitne zyada hits, utne kam provider calls), aur model-mix shift dekho (zyada haiku, kam opus). Ek example math:

```
Before: 100% sonnet-equivalent traffic
After:  50% haiku + 35% sonnet + 15% opus, + 25% cache-hit rate
→ blended cost ~35–45% kam — par YOUR traffic pe measure karo, ratta mat maro
```

> **→ Practice M3** (pass: test set 3 buckets mein sahi route ho).

---

### §4. Cache — exact + semantic, tenant-scoped

Gateway pe traffic repeat hoti hai — "password reset steps?" hazaron baar aata hai. Bina cache provider bill aur latency dono badhte hain. Do tarah ka cache (Module 02 §3 se):

```
Exact:    cache_key = f"{tenant_id}:exact:{sha256(prompt)}:{model}"
Semantic: store {tenant_id, embedding, response, ttl}; lookup nearest where cosine > 0.92
```

Cache key mein teen cheezein critical hain. `tenant_id` prefix **mandatory** hai — bina iske Tenant A ka cached jawab Tenant B ko mil sakta hai (security incident). `sha256(prompt)` exact fingerprint deta hai. Aur `model` key mein hona chahiye — same words par alag model alag jawab dega, to unhe alag cache karo. Invalidation ke rules: default TTL (FAQ ke liye 24h, compliance policy ke liye 1h — kyunki wo badalti hai), prompt version bump pe prefix bust (`tenant:v2:*`), tool side-effects (payments/writes) **kabhi cache nahi**, aur ek admin endpoint jo tenant ka cache purge kar sake.

#### §4 common errors

| Symptom | Kyun | Fix |
|---------|------|-----|
| Stale policy jawab | TTL bahut lamba | Compliance content pe chhota TTL |
| Hamesha cache miss | Model key har route pe badal raha | Routed model ko key mein stabilize karo |
| Cross-tenant leak | Global semantic index | `tenant_id` se partition |

> **→ Practice M4** (pass: near-duplicate prompt → cache hit, LLM skip).

---

### §5. Rate limits + token budgets

Ek tenant ka loop/bug → unlimited tokens → tumhara provider bill + doosre tenants slow. Credit-limit jaisा hard stop chahiye. Teen controls hain alag-alag responses ke saath: requests/min (rate limit → 429), tokens/day soft (warning → 200 + `X-Budget-Warning: 90%`), tokens/day hard (stop → 402 Payment Required). Redis pattern:

```python
used = redis.incrby(f"budget:{tenant_id}:tokens_used", completion_tokens)
limit = int(redis.get(f"budget:{tenant_id}:limit") or DEFAULT_LIMIT)
if used > limit:
    raise HTTPException(402, "Token budget exceeded")     # hard stop
elif used > limit * 0.9:
    response.headers["X-Budget-Warning"] = "90%"          # soft warn
```

Ek subtle bug se bacho: budget sirf **successful (200) calls** pe increment karo — agar failed calls bhi count karein to "budget drift" ho jaayega aur tenant ko galat charge milega. Yeh sab billing spine mein feed karta hai: har response → cost event `{tenant_id, tokens, cost_usd, idempotency_key}` → outbox table → worker → Stripe metered billing (Projects.md).

> **→ Practice M5** (pass: over-budget → 402/429 hard stop).

---

### §6. Fallback chain + circuit breaker

Primary provider outage = product down + revenue loss. Module 02 ke patterns yahan wire hote hain. Flow: primary call breaker mein wrapped → 5xx/timeout pe breaker increment → breaker OPEN ya primary 503 pe secondary provider → span pe `fallback_used=true` log → dono fail to 503 + Retry-After (fake success kabhi nahi).

Decision table yaad rakho — kab fallback, kab nahi:

| Primary result | Action |
|----------------|--------|
| 200 OK | Return; breaker success |
| 503 / timeout | Secondary try; fallback log |
| Breaker OPEN | Primary skip; seedhe secondary |
| 400 bad prompt | **No fallback** — client ko 400 |

```python
try:
    return call_primary_with_breaker(req)
except (ProviderError, CircuitOpen):
    return call_secondary(req)   # alag model OK agar disclose karo
```

Ek detail: fallback model ka rate alag hoga, to `cost_usd` secondary model ki pricing se recalc karo — warna billing galat.

> **→ Practice M2** (pass: primary 5xx simulate → secondary succeed).

---

### §7. Tracing — OpenTelemetry + cost span mein

"p99 2.8s ho gaya" — time kahan gaya? Interview mein yeh breakdown defend karna hai, aur wo tabhi possible hai jab har request ek span emit kare uske cost/timing attributes ke saath:

```json
{
  "name": "gateway.chat",
  "attributes": {
    "tenant_id": "org_42", "model": "claude-3-haiku",
    "tokens_in": 120, "tokens_out": 45, "cost_usd": 0.00012,
    "cache_hit": true, "latency_ms": 8, "fallback_used": false
  }
}
```

In attributes se tum har incident debug kar sakte ho: latency spike? `cache_hit` rate gira hoga. Cost up? `model` distribution mein zyada opus aa gaya. Reliability problem? `fallback_used` dekho. Typical latency budget yaad rakho: cache hit ~5–20ms, haiku miss ~400–900ms, opus miss ~2–5s. Isliye interview line banti hai: "latency spike ka matlab ya cache-miss rate badh gaya, ya complexity router zyada queries opus tier pe bhej raha hai."

> **→ Practice M6** (pass: local trace/log mein cost fields dikhein).

---

### §8. Feature matrix → milestones

Project C bada hai, isliye **incremental** ship karo — har milestone ek skill prove karta hai aur ek baithak mein ek milestone ideal hai:

| Feature | Milestone | Theory § |
|---------|-----------|----------|
| Passthrough + `/health` | M1 | §1, §2 |
| Dual-provider fallback | M2 | §6 |
| Complexity classifier | M3 | §3 |
| Redis semantic cache | M4 | §4 |
| Rate limit + budget | M5 | §5 |
| OTEL + cost span | M6 | §7 |
| SSE streaming E2E | M7 | §2 step 7 |

Dependency: M1 base sab ka neeche; M3 (router) → M4 (cache); M5 (budget) → M6 (tracing); M7 ko sirf M1 base chahiye. Go ship note: Python sandbox logic prove karta hai; Project C wahi pipeline chi router + middleware (00e) mein dobara banayega.

> **→ Practice M1–M7** — ek milestone per session.

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Learning sandbox Python; ship `@Projects.md` Project C (Go).
> Stuck? `@modules/03-project-llm-gateway/MODULE.md @Projects.md`

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| M1 | §1, §2 | `gateway_skeleton.py` | Health + passthrough curl |
| M2 | §6 | `fallback_router.py` | 5xx sim → secondary OK |
| M3 | §3 | `complexity_router.py` | Test set 3 buckets OK |
| M4 | §4 | `semantic_cache.py` | Near-dup → LLM skip |
| M5 | §5 | `budget_middleware.py` | Over-budget → 402/429 |
| M6 | §7 | `tracing_stub.py` | Trace + cost fields visible |
| M7 | §2 | `stream_passthrough.py` | `curl -N` token stream |

### Setup

```bash
cd modules/03-project-llm-gateway/practice
python3 -m venv .venv && source .venv/bin/activate
pip install fastapi uvicorn httpx redis python-dotenv openai
# 00a Redis chalao
```

### Interview prep (NOTES — M3+ ke baad)

- "40% cost cut" — cache-hit % + model-mix before/after numbers
- Cache invalidation strategy (§4)
- Per-tenant key rotation
- Request lifecycle 11 steps whiteboard

---

## Active recall (khud jawab likho NOTES mein)

1. Gateway router matching-engine price tiers se kaise parallel hai?
2. Per-tenant cache scoping kyun mandatory hai?
3. "40% cost cut" claim kaise measure + defend karoge?
4. Lifecycle mein budget check provider call se **pehle** kyun?

**Chat drill** (optional): "Module 03 architecture whiteboard — 11 steps."

---

## Progress checklist

- [ ] §0 terms — gateway vs BFF clear
- [ ] Theory §1–§8 padha
- [ ] Redraw challenge
- [ ] Practice M1–M7 pass
- [ ] Active recall + interview bullets NOTES mein
- [ ] NOTES architecture decisions logged

---

## Optional appendix (zarurat ho tab)

- [`@Projects.md` Project C](../../Projects.md) — full ship spec
- [OpenTelemetry Python](https://opentelemetry.io/docs/languages/python/)
- Module 02 — rate limit, breaker, cache deep dive
