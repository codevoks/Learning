# Module 02 — LLM Infra Patterns

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 01](../01-llm-apis/MODULE.md) · Next → [Module 03](../03-project-llm-gateway/MODULE.md)

> **Format**: Textbook — §0 terms pehle (rate limit, cache, circuit breaker), prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`

## At a glance

| | |
|---|---|
| Prerequisites | Module 01 · 00a Redis (`docker compose up -d`) |
| Duration | ~4–6 sessions |
| Project? | No |
| Exit test | Cache + circuit breaker design bina notes ke whiteboard karo |

## Yeh module kis baare mein hai

Module 01 mein tumne ek route se seedha OpenAI ko call kiya — seekhne ke liye perfect, par production mein **kabhi** aisा nahi karte. Kyun? Kyunki seedhа call mein na rate-limiting hai, na caching, na koi protection jab provider down ho. Yeh module wo **protective layer** sikhata hai jo har real LLM product mein hota hai — woh patterns jinke bina ek galat tenant tumhara poora bill aur sabke users uda dega.

Mental model: har request seedhа provider ko nahi jaati, balki ek **gate** se guzarti hai. Pehle "ruko, zyada to nahi bhej rahe?" (rate limit), phir "yeh jawab pehle se paas hai kya?" (cache), phir "provider zinda hai kya?" (circuit breaker), tab jaake provider. §0 mein in saare shabdon ko zero se samjhaunga.

```
request → [rate limit] → [cache hit?] ──yes──► response (fast, sasta)
                            │ miss
                            ▼
                       [circuit breaker closed?] → LLM provider → cache store + respond
```

**Redraw challenge**: Request → rate limiter → cache → circuit breaker → provider — bina dekhe banao.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms | `redis-cli PING` se Redis check |
| 2 | §1 Proxy layer + §2 Rate limiting | **A1** rate limiter |
| 3 | §3 Semantic cache + exact cache | **A2** exact cache |
| 4 | §4 Circuit breaker | **A3** breaker wrapper |
| 5 | §5 Fallback + §6 Cost tracking | NOTES — cost JSON schema |
| 6 | §7 Observability + recall | **A4** request middleware |

---

## Learning hooks (fintech parallels)

Yeh saare patterns tumhare trading background mein already maujood hain, bas alag naam se: token-bucket rate limit ≈ per-client order throttle; exact cache ≈ idempotent order replay; semantic cache ≈ bank reconciliation ka fuzzy match; circuit breaker ≈ venue down hone pe orders rokna; fallback provider ≈ secondary liquidity source; per-tenant budget ≈ account trading limits; structured cost log ≈ har fill ka billing event.

---

## Theory

### §0. Terms pehli baar — infra words (35 min)

**Rate limiting.** Yeh ek fixed window mein zyada-se-zyada N requests allow karta hai; uske baad reject (aam taur pe HTTP **429 Too Many Requests**), taaki client backoff kare. Tumhare exchange waale din se seedha — HFT client ek second mein 1000 orders nahi bhej sakta; yahan ek tenant ek second mein 60 LLM calls. Tum yeh limit alag levels pe laga sakte ho: IP pe (anonymous abuse), API key/user pe (fair use per customer), ya tenant pe (SaaS multi-tenant). Sabse common algorithm **token bucket** hai (§2 mein detail).

**Cache.** Pehle compute kiya hua jawab store karna, taaki agli baar provider call **skip** ho jaaye. Key mil gayi = **cache hit** (stored response wapas), nahi mili = **cache miss** (provider call karo, phir store). Har entry ki ek **TTL** (time-to-live) hoti hai. Do tarah ka cache hota hai: **exact** (bilkul same string prompt → hit) aur **semantic** (similar *matlab* waला prompt → hit, embeddings se, §3). Semantic zyada powerful hai par khatarnak bhi — galat match (**false positive**) galat jawab serve kar dega.

**Circuit breaker.** Ek wrapper jo provider ki failures ginता hai; bahut fail ho jaayein to **OPEN** ho jaata hai aur requests turant reject karne lagta hai (provider ko call hi nahi karta). Teen states hain: **CLOSED** (normal, requests jaa rahi hain), **OPEN** (fail fast — sick provider ko hammer mat karo, latency aur paisa bachao), aur **HALF-OPEN** (ek test "probe" request — success hua to wapas CLOSED, fail hua to wapas OPEN). Yeh bilkul matching-engine connectivity monitor jaisा hai: venue down → routing roko, beech-beech mein ek probe order se check karo recover hua ya nahi.

**Fallback.** Primary provider fail kare (5xx ya breaker OPEN) to secondary provider/model try karna — jaise Anthropic fail to OpenAI, dono fail to stale cache ya graceful 503. Ek **bahut zaroori rule**: `400` (bad request) pe fallback **mat** karo — wo user/prompt ki galti hai, doosra provider bhi fail karega, bas tum do baar paisa jala doge.

**Observability terms.** `trace_id` ek request ki poori journey ko jodne wali UUID hai; **span** ek operation ka timed slice (cache lookup, provider call); **OTEL** (OpenTelemetry) vendor-neutral tracing standard; aur **structured log** matlab JSON fields (grep/aggregate-friendly), na ki ek lambi string.

> **Ruko, socho:** Rate limit aur budget limit — dono "roko" karte hain, par farak kya hai? (Jawab: rate limit *speed* control karta hai — per second/minute kitni requests. Budget limit *total kharcha* control karta hai — is mahine $X se zyada nahi. Ek tez burst rokта hai, doosra mahine ka bill.)

#### §0 common galatfehmiyaan

| Galat soch | Sach |
|-----------|------|
| "Cache hamesha safe" | Stale data / galat semantic match ka risk |
| "429 = bug" | Load pe expected — backoff design karo |
| "Breaker = retry" | Breaker calls **roकता** hai; retry alag policy hai |

---

### §1. Proxy layer kyun chahiye — seedhа API call production mein nahi

Module 01 mein ek FastAPI route OpenAI ko call kar raha tha. Ab socho jab 10 microservices hain, har ek apni key, apna retry, apna logging copy-paste kar raha hai. Result: keys 10 jagah (leak risk), cost data har jagah alag-alag (CFO ko jawab nahi de paoge), aur koi central throttle nahi (ek service pagal ho jaaye to sab affected). Yeh operational chaos hai.

```
❌ 10 services × (API key + retry + logging + cache)
✅ 10 services → 1 LLM proxy/gateway → providers
```

Tumhare trading parallel mein: har desk ka apna direct-market-access vs bank ka central OMS — compliance, limits, aur audit ek jagah. Proxy layer wahi central OMS hai: rate limit, cache, circuit breaker, cost log, aur traces — sab ek jagah, sabके liye consistent. Request ka flow ban jaata hai: service proxy ko call karta hai → proxy auth + rate limit → cache lookup → breaker check → provider call → cost log + cache store + return. Yahi poora module is flow ke ek-ek tukde ko bharta hai.

Ek galti jo product ko maar deti hai: provider key kabhi **frontend** mein mat daalo — wo chori hui to koi tumhare paise se model chala lega. Key hamesha server-side proxy mein.

---

### §2. Rate limiting — token bucket

Maan lo ek tenant galti se (ya jaanboojh ke) ek loop mein 10,000 LLM calls bhej deta hai. Do cheezein hongi: tumhara bill spike, aur provider 429 dene lagega — jisse **sabके** users affected. Isliye per-tenant throttle Redis pe chahiye.

Sabse common algorithm **token bucket** hai, jo ek simple intuition pe khada hai. Ek bucket socho jisme tokens hain. Har request ek token kharch karti hai. Bucket time ke saath dheere-dheere refill hota hai. Bucket khaali = 429.

```
Bucket capacity = 60 tokens       (max burst — ek baar mein 60 OK)
Refill rate     = 1 token/second  (sustained rate)
Har request     = 1 token kharch

t=0: bucket=60 → 60 ka burst allowed
t=1: +1 refill (cap tak)
khaali bucket → HTTP 429 + Retry-After header
```

Yahan capacity short spikes allow karti hai (user ko thoda burst de do), aur refill rate sustained throughput ko cap karti hai. Learning ke liye Redis pe ek simple per-minute counter kaafi hai:

```python
key = f"rl:{tenant_id}:{current_minute}"   # tenant + window scoped
count = redis.incr(key)                     # atomic +1
if count == 1:
    redis.expire(key, 60)                   # pehli baar pe TTL set
if count > LIMIT:
    raise HTTPException(429, "Rate limit exceeded")
```

Do cheezein dhyaan se. Key mein `tenant_id` hona **zaroori** hai — warna sab tenants ek hi counter share karenge aur ek tenant ki burst sabko 429 de degi. Aur `EXPIRE` pehli `INCR` pe set karo — warna window kabhi reset nahi hoga aur tenant hamesha ke liye blocked.

> **Ruko, socho:** Agar tum `redis.expire(key, 60)` har `INCR` pe call karo (sirf `count == 1` pe nahi), to kya bug aa sakta hai? (Jawab: window kabhi expire hi nahi hoga — har naye request pe TTL 60s pe reset ho jaayega, jab tak traffic aata rahega key zinda rahegi. TTL sirf pehli baar set karo.)

#### §2 common errors

| Symptom | Kyun | Fix |
|---------|------|-----|
| Sab ko 429 mil raha | Key sab tenants ke liye same | Key mein `tenant_id` daalo |
| Limit kabhi reset nahi | `EXPIRE` missing | Pehli `INCR` pe TTL set |
| Redis connection refused | 00a compose nahi chal raha | `docker compose up -d` |

> **→ Practice A1** (pass: N requests/min ke baad 429).

---

### §3. Semantic cache — meaning se cache hit

Exact cache ki ek seemा hai: user "refund policy?" aur "Refund policy?" — capital R ke wajah se string alag, cache miss, LLM dobara call (latency + cost). Insaan ke liye dono same sawaal hain. **Semantic cache** isi gap ko bharta hai — meaning similar hua to hit.

Kaise? Query ko embed karke vector banao (Module 00d), phir cache mein paas waale vectors dhoondho. Agar kisi stored query se cosine similarity threshold (jaise 0.92) se upar hai, wo cached jawab return kar do — LLM call hi mat karo:

```
Query A: "What is your refund policy?"
Query B: "How do refunds work?"
cosine(embed(A), embed(B)) ≈ 0.95   → threshold 0.92 → CACHE HIT, LLM skip
```

Exact vs semantic dono Module 03 gateway mein use honge: exact ki key `hash(prompt + model)` hai (byte-identical pe hit), semantic ki "key" embedding ka nearest-neighbor (paraphrase pe hit).

Par yahan **dhyaan se** — semantic cache ke real risks hain. Sabse bada **false positive**: agar threshold bahut neeche rakha, to do alag-alag matlab waले sawaal galti se match ho jaayenge aur tum galat jawab serve kar doge. Tumhare trading parallel mein yeh "galat counterparty se trade match" jaisा catastrophic hai — isliye threshold conservative (0.92+) rakho. Doosra risk: stale data (purani refund policy serve ho jaaye — TTL + cache key mein version daalo). Aur sabse important: **side-effects waale calls kabhi cache mat karo** — "Transfer $100" jaisा action cache karoge to disaster. Cache sirf read-only/idempotent answers ke liye.

#### §3 common errors

| Symptom | Kyun | Fix |
|---------|------|-----|
| Kabhi hit nahi hota | Threshold bahut high | Labeled query pairs pe tune |
| Galat jawab serve | Threshold bahut low | Threshold badhao; A/B measure |
| Cross-tenant leak | Key mein `tenant_id` nahi | Hamesha `tenant_id` prefix |

> **→ Practice A2** (pass: exact duplicate prompt → doosra call LLM skip kare. Semantic version Module 03 M4 mein).

---

### §4. Circuit breaker — closed, open, half-open

Socho provider 503 de raha hai aur tum har request pe 30s timeout wait kar rahe ho. Kya hoga? Requests queue mein pile up, users gussa, aur timeout retries se **bill bhi** badh raha. Circuit breaker isका ilaaj hai — jab provider unhealthy ho, **fail fast** karo.

Teen states ka flow yaad rakho:

```
CLOSED     → Normal. Consecutive failures gino.
OPEN       → Turant reject. Provider ko HTTP call hi nahi.
HALF-OPEN  → Sirf EK probe request allow.
             Success → CLOSED (failure count reset)
             Fail    → wapas OPEN
```

Teen parameters ise control karte hain: `failure_threshold` (jaise 3 — itni fail pe OPEN), `open_duration_sec` (jaise 30 — kitni der OPEN rahe probe se pehle), aur `success_threshold` (kitne probes close karein). Wrapper ka core logic:

```python
def call_with_breaker(fn):
    if state == OPEN:
        if now - opened_at > open_duration:
            state = HALF_OPEN          # probe ka time aa gaya
        else:
            raise ServiceUnavailable("Circuit open")   # fail fast
    try:
        result = fn()                  # asli provider call
        on_success()                   # failure count reset, maybe CLOSED
        return result
    except ProviderError:
        on_failure()                   # count++, maybe OPEN
        raise
```

**Half-open kyun zaroori hai?** Agar breaker hamesha OPEN rehta, to provider recover hone ke baad bhi tum kabhi try nahi karte — permanently stuck. Probe ek chhota "health-check trade" hai: ek test request bhejo, kaam kiya to poora traffic wapas khol do. Ek aur common galti: breaker tabhi "fail" ginо jab provider ki asli 5xx/timeout ho — agar tum har exception (jaise user ki 400) ko fail gino, breaker galat khulega.

> **Ruko, socho:** Tumhare breaker mein har exception `on_failure()` trigger kar raha hai, aur breaker baar-baar OPEN ho raha hai jabki provider theek hai. Kya galat hai? (Jawab: tum client errors (400/422) ko bhi provider-failure samajh rahe ho. Sirf 5xx aur timeouts gino — wahi provider ki sehat batate hain.)

> **→ Practice A3** (pass: 3 simulated fails → OPEN; half-open retry kaam kare).

---

### §5. Fallback provider chain

Ek provider ka outage tumhara poora product gira de — isliye secondary "liquidity" chahiye. Module 01 ka API knowledge yahan wire hota hai:

```
1 → Primary try karo (jaise Anthropic)
2 → 5xx YA breaker OPEN → secondary (OpenAI)
3 → Dono fail → 503 + Retry-After
4 → Log karo kaunsा path: primary | fallback | failed
```

Sabse important fallback ka **rule**: kab karna hai aur kab **nahi**. Primary 503 ya breaker OPEN pe haan (provider ki problem hai). Par `400` (bad request) ya `401` (key config) pe **nahi** — yeh tumhari/prompt ki galti hai, secondary bhi fail karega, bas double bill. Aur jab fallback ho, response mein ek header (jaise `X-Model-Used`) daalo taaki quality drop silent na ho — user ko pata chale alag model ne jawab diya.

> **→ Practice A3** (breaker + fallback ka integration Module 03 M2 mein).

---

### §6. Cost tracking per request

CFO poochhega "Tenant X ka is mahine ka kitna bill hai?" — aur bina structured log ke tum sirf guess kar paoge. Isliye har LLM call ko ek **billing event** ki tarah record karo — jaise har trade fill ka fee record hota hai. Har request ke baad ek JSON line:

```json
{
  "trace_id": "abc-123",
  "tenant_id": "org_42",
  "model": "gpt-4o-mini",
  "prompt_tokens": 1200,
  "completion_tokens": 340,
  "cost_usd": 0.0041,
  "cache_hit": false,
  "provider": "openai",
  "latency_ms": 842
}
```

Har field ka maqsad hai: `trace_id` logs aur traces ko jodता hai; `tenant_id` batata hai kise bill karna; `prompt_tokens`/`completion_tokens` provider ke `usage` se aate hain; `cost_usd` Module 01 ka formula lagाke; `cache_hit: true` matlab LLM cost bach gaya; `provider` batata hai primary use hua ya fallback. Yeh JSON lines downstream aggregate hoti hain — daily `SUM(cost_usd) GROUP BY tenant_id`, budget cross pe Slack alert, dashboard pe cache-hit-rate aur p99 latency.

Ek precision baat: USD ke liye `float` ki jagah `Decimal` use karo — chhote amounts par float rounding drift jodता jaata hai aur billing galat ho jaati hai.

> **→ Practice A4** (pass: per request JSON log with trace_id + token fields).

---

### §7. Observability — structured logs + OTEL  ⏭️ SKIM-able

> ⏭️ **Skim OK** — structured-logging concept zaroori; deep OTEL/Jaeger setup baad mein (Module 10 mein bhi aata).

"p99 latency 3 second ho gaya" — ab kya? Cache toot gaya? Bade model pe zyada routing ho raha? Provider slow? Bina **spans** ke yeh sab guesswork hai. Observability ka idea: ek request ko uske andar ke har step ke saath measure karo.

```python
logger.info("llm_request_complete", extra={
    "trace_id": trace_id, "tenant_id": tenant_id,
    "latency_ms": 420, "tokens_in": 100, "tokens_out": 50,
    "cache_hit": False, "cost_usd": 0.0023,
})
```

Gaur karo — yahan ek **event name** (`"llm_request_complete"`, grep-friendly) hai aur `extra={...}` mein structured fields, na ki ek lambi concatenated string. Yahi structured logging hai. Aage tool choices hain: plain JSON logs (MVP ke liye — Module 03 M6 yahan se), Langfuse (LLM-specific — prompts + eval scores), ya raw OTEL + Jaeger (custom dashboards). Ek privacy rule: poora prompt log mat karo (PII leak) — uska hash + length log karo.

> **→ Practice A4** (pass: ek request → structured JSON line with trace_id).

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge.
> Stuck? `@modules/02-llm-infra/MODULE.md` + error paste.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §2 | `rate_limiter.py` | 429 after N req/min |
| A2 | §3 | `exact_cache.py` | Cache hit LLM skip kare |
| A3 | §4, §5 | `circuit_breaker.py` | 3 fails pe OPEN, half-open retry |
| A4 | §6, §7 | `request_middleware.py` | trace_id + token JSON logs |

### Setup

```bash
cd modules/02-llm-infra/practice
python3 -m venv .venv && source .venv/bin/activate
pip install redis httpx fastapi uvicorn python-dotenv
# Redis: 00a/practice → docker compose up -d
```

---

## Active recall (khud jawab likho NOTES mein)

1. Semantic cache false positive ka production impact kya hai?
2. Circuit breaker ko half-open state kyun chahiye?
3. Rate limit user-level vs IP-level — kab kaunsa?
4. Proxy layer seedhe provider call se cost/latency 2 tareeke se kaise behtar karta hai?

**Chat drill** (optional): "Module 02 recall — 4 questions mujhse poochh."

---

## Progress checklist

- [ ] §0 terms + checkpoint NOTES mein
- [ ] Theory §1–§7 padha (section → practice rhythm)
- [ ] Redraw challenge
- [ ] Practice A1–A4 pass
- [ ] Active recall NOTES mein
- [ ] NOTES session log updated

---

## Optional appendix (zarurat ho tab)

- [Martin Fowler — Circuit Breaker](https://martinfowler.com/bliki/CircuitBreaker.html)
- [Redis rate limiting patterns](https://redis.io/glossary/rate-limiting/)
- [OpenTelemetry concepts](https://opentelemetry.io/docs/concepts/)
