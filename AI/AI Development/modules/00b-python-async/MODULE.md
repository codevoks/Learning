# Module 00b — Python Async & Pydantic

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 00a](../00a-dev-environment/MODULE.md) · Next → [Module 00c](../00c-fastapi/MODULE.md)

> **Format**: Textbook — §0 Python syntax pehle (prose), phir async/Pydantic samjhaунga. Voice: `@MODULE-TEACHING-STANDARD.md`

## At a glance

| | |
|---|---|
| Prerequisites | Module 00a |
| Duration | ~3–4 sessions |
| Project? | No |
| Exit test | Async function + Pydantic model apne shabdon mein samjhao, Zod se compare karke |

## Yeh module kis baare mein hai

Aage tum FastAPI mein LLM gateway banaoge jahan ek request ke andar Redis check hoga, OpenAI ko call jaayega, phir result cache hoga. In sab mein tumhara code zyadातar **wait** kar raha hota hai — network ka, DB ka. Agar tum is wait ko galat handle karoge, ek slow LLM call poore server ko jam kar degi. Iska ilaaj **async** hai, aur yeh module wahi sikhata hai — saath mein **Pydantic**, jo aane wale data ko validate karta hai (Zod ka Python cousin).

Tum JS/TS jaante ho, isliye dimaag to ready hai — bas Python ki grammar nayi hai. §0 mein wo grammar zero se de raha hoon; use skip mat karna jab tak atak na jao.

## Visual map

```
SYNC timeline:   [====A====][====B====][====C====]   ← ek thread, ek-ek karke wait
ASYNC timeline:  [==A==]
                 [==B==]   ← jab A I/O pe wait, loop B chala deta hai
                 [==C==]

Pydantic:  raw JSON dict → validate fields → Model instance (ya ValidationError)
```

**Mental model**: Sync = ek kaam poora, phir doosra; async = jab koi kaam I/O pe wait kare, loop doosra chalा le; Pydantic = runtime pe Zod jaisा schema-guard.

**Redraw challenge**: Sync vs async timeline (3 tasks) aur JSON → Pydantic → Model/Error flow bina dekhe banao.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Python syntax — terminal try | `python3` snippets §0.9 |
| 2 | §1 Sync vs async | Paper pe timeline draw |
| 3 | §2 Event loop + `await` | **A2** prep — `asyncio.gather` samjho |
| 4 | §3 Blocking mistakes + §4 Pydantic | **A1**, **A3** |
| 5 | §5 httpx + §6 gateway model | **A2**, **A4** NOTES |

**Unlocks**: Module 00c FastAPI

---

## Learning hooks (tera parallel)

Pydantic `BaseModel` ≈ Zod schema + `.parse()`; `async def` route handler ≈ non-blocking I/O; `await httpx.get()` ≈ `fetch` jo thread block nahi karta; `Optional`/`list[str]` ≈ TS generics; aur Pydantic ka validation error → HTTP 422 ≈ Zod error → 400.

---

## Theory

### §0. Python syntax — pehli baar (30 min, terminal pe try karo)

Tum JavaScript/TypeScript jaante ho, par Python ki grammar alag hai — sabse bada farak yeh ki Python mein blocks **curly braces se nahi, indentation se** bante hain. Is section ke baad har Python file padhi-padhi lagegi.

**Blocks aur colon.** Jahan JS mein `{ }` hota, Python mein 4-space indent hota hai, aur block shuru karne se pehle `:` colon zaroori hai. Semicolon mostly nahi lag ते.

```python
def greet():
    print("hi")    # 4-space indent = block ke andar

if True:
    print("yes")   # if ke baad bhi colon
```

`def greet()` bina colon likha to seedha `SyntaxError`. (Yeh wo galti hai jo har JS dev pehle hafte 10 baar karta hai — koi baat nahi.)

**Values aur f-strings.** `=` assign karta hai, `==` compare. Booleans capital se — `True`/`False`, aur null ki jagah `None`. String interpolation ko Python **f-string** kehta hai (template literal jaisा):

```python
count = 42
ok = True
nothing = None
msg = f"count={count}"   # "count=42"
```

**dict aur list** — JS ke object aur array:

```python
user = {"id": 1, "name": "Vansh"}   # dict (object jaisा)
user["name"]                         # "Vansh"
nums = [1, 2, 3]                     # list (array jaisा)
```

FastAPI mein `return {"status": "ok"}` ka matlab — ek dict return kiya, wo JSON ban jaayega.

**Functions aur type hints.** `def` se function banta hai. Parameters pe `a: int` likhna ek **type hint** hai — Python ise runtime pe force *nahi* karta, par FastAPI aur Pydantic inhe padhke validation aur docs banate hain. Isliye yeh hints AI backend mein bahut important hain.

```python
def add(a: int, b: int) -> int:   # -> int = return type hint
    return a + b
```

**Class** — Pydantic models classes hain, isliye basic shape jaan lo:

```python
class User:
    name: str
```

**Import** JS ke `import` jaisा hi: `import asyncio`, ya `from pydantic import BaseModel`.

**`async`/`await` ka chhota preview** (poora §1–§2 mein): `async def` ek "coroutine" banata hai, aur `await` sirf `async def` ke andar chal सकta hai. Ek `.py` file mein top-level pe direct `await` nahi likh sakte — `asyncio.run(main())` se entry lete hain.

Abhi terminal pe khud chalा ke dekho:

```bash
python3
>>> x = {"a": 1}
>>> x["a"]
1
>>> def f(n: int) -> int:
...     return n + 1
...
>>> f(5)
6
>>> exit()
```

**§0 done?** Ab §1. Syntax atke to chat mein wo symbol paste karo — theory dubara mat likhwao.

---

### §1. Sync vs async — yeh kyun matter karta hai

Pehle samjho tumhara backend asli mein karta kya hai. Ek LLM gateway mein CPU bahut kam kaam karta hai — wo zyadातar **wait** kar raha hota hai: DB se jawab ka, Redis ka, OpenAI API ka. Yeh "I/O bound" workload hai.

Ab do tareeke hain is wait ko handle karne ke. **Sync** mein ek request poori khatam hone tak thread block rehta hai — agar OpenAI 3 second leta hai, wo thread 3 second tak kuch aur nahi kar sakta, bas baitha rehta hai. **Async** mein jab koi kaam I/O pe wait karta hai, event loop us thread ko free karke doosre kaam pe laga deta hai, aur jab jawab aata hai tab pehle waale pe wapas aata hai.

Iska asli faayda concrete example se feel hota hai. Maan lo tumhe 3 alag API calls karni hain, har ek 1 second:

- Sync mein: 1 + 1 + 1 = **3 second** (ek ke baad ek).
- Async mein (parallel): teeno ek saath shuru, total ≈ **1 second** (sabse slow waale jitna).

```
Sync:   [Req1████████][Req2████████][Req3████████]
Async:  [R1==][R2==][R3==] ... loop switch on each await
```

Tumhare matching-engine/gateway dimaag ke liye: agar har LLM call sync block kare, worker threads jaldi khatam ho jaayenge aur server naye clients ko reject karne lagega. Async se ek hi process hazaron concurrent connections handle kar leta hai — jab tak kaam I/O-bound hai (CPU-heavy ho to alag kahani, §3).

---

### §2. Event loop — `async def`, `await`, `gather`

Python ka **asyncio** ek **event loop** chalata hai: ek single thread jisme kai coroutines schedule hote hain, aur loop unke beech switch karta rehta hai jab bhi koi `await` pe rukta hai.

```python
import asyncio

async def fetch_name():
    await asyncio.sleep(0.5)   # I/O wait simulate (real mein network/httpx)
    return "gateway"

async def main():
    a = await fetch_name()                              # serial
    b = await fetch_name()                              # ~1s total

    a, b = await asyncio.gather(fetch_name(), fetch_name())  # parallel ~0.5s

asyncio.run(main())
```

Yahan dhyaan dene layak teen cheezein hain. `async def fetch_name()` ko call karne se wo *chalti nahi* — bas ek coroutine object banta hai jo schedule hone ka wait karta hai; chalti tabhi hai jab `await` ya `gather` use karo. Doosra, `await asyncio.sleep(0.5)` keh raha hai "yahan 0.5s wait karo, par loop ko free chhod do taaki wo doosra kaam kar sake" — yeh real I/O wait ka stand-in hai. Teesra aur sabse important: `a = await fetch_name()` ke baad `b = await ...` likhna **serial** hai (pehla khatam, phir doosra, ~1s), jabki `asyncio.gather(...)` dono ko **ek saath** start karta hai (~0.5s). Aur `asyncio.run(main())` poora loop start karke entry deta hai.

> **Ruko, socho:** Upar wale code mein agar tum `gather` waali line hatao aur dono `fetch_name()` ko alag-alag `await` karo, to total time kya hoga — 0.5s ya 1s? Aur kyun? (Jawab: 1s — serial await ka matlab pehla poora khatam hone ke baad hi doosra shuru hota hai. `gather` hi parallelism deta hai.)

Type hints yahan bhi kaam aate hain (FastAPI/Pydantic inhi pe khade hain): `name: str`, default value `count: int = 1`, return `-> list[str]`, aur "ho bhi sakta hai None" ke liye `Optional[dict]` (matlab `dict | None`).

> **→ Practice A2** — 3 URLs parallel `gather` se fetch karo; total time ≈ slowest URL, sum nahi.

---

### §3. Sabse badi galti — `async def` ke andar sync blocking

Yeh production killer hai aur isे bahut dhyaan se samjho. Tum ek route ko `async def` bana doge, par andar galti se ek **sync (blocking)** call laga doge — aur poora event loop freeze ho jaayega, kyunki wo single thread us blocking call pe atak gaya:

```python
import time, requests   # dono sync

async def bad_handler():
    time.sleep(2)        # ❌ poora event loop 2s ke liye freeze — saare clients wait
    requests.get(url)    # ❌ blocking — thread atka, concurrency gayi
```

`async def` likh dene se cheez async nahi ho jaati — andar **bhi** async (non-blocking) calls hone chahiye. Sahi version:

```python
import asyncio, httpx

async def good_handler():
    await asyncio.sleep(2)                       # ✅ loop ko yield
    async with httpx.AsyncClient() as client:
        r = await client.get(url, timeout=10.0)  # ✅ non-blocking
```

Rule yaad rakho: async route ke andar `time.sleep` ki jagah `await asyncio.sleep`, `requests` ki jagah `httpx.AsyncClient`. Aur agar koi sach mein CPU-heavy kaam hai (bada loop, image processing), to wo bhi loop block karega — use `run_in_executor` ya alag worker process mein bhejo, async se wo theek nahi hota (async sirf I/O-wait ke liye hai, CPU ke liye nahi).

> **→ Practice A3** — `broken_async.py` mein blocking call dhoondho, fix karo, aur NOTES mein likho kyun woh poore server ko rok raha tha.

---

### §4. Pydantic v2 — Zod, par Python mein

API pe jo data aata hai (raw dict) uspe bharosa nahi kar sakte — galat types, missing fields, extra junk kuch bhi ho sakta hai. Pydantic us dict ko ek **typed, validated** object mein badal deta hai, aur galat hua to clean error deta hai. Yeh bilkul Zod ka kaam hai.

```python
from pydantic import BaseModel, Field

class ChatRequest(BaseModel):
    message: str = Field(min_length=1, max_length=4000)
    model: str = "gpt-4o-mini"   # default value
    stream: bool = False

req = ChatRequest.model_validate({"message": "hello"})   # req.message typed str
ChatRequest.model_validate({"message": ""})              # ❌ ValidationError (min_length)
```

`class ChatRequest(BaseModel)` ek schema declare karta hai; `Field(min_length=1, ...)` constraints lagata hai; aur `model_validate(...)` aane wale dict ko check karke object banata hai (ya error phenkta hai). Agar tum Zod soch rahe ho to mapping seedhi hai: `z.object({...})` ≈ `class X(BaseModel)`, `.parse(data)` ≈ `.model_validate(data)`, aur `.safeParse` ki jagah Python mein `try/except ValidationError`.

Bahar JSON bhejne ke liye ulta direction: `resp.model_dump()` object ko dict banata hai, `resp.model_dump_json()` seedha JSON string. Aur FastAPI ke saath jaadू yeh hai — agar route ka parameter `body: ChatRequest` ho, to FastAPI request body ko **automatically** validate karta hai aur galat input pe khud `422 Unprocessable Entity` return kar deta hai:

```python
@app.post("/chat")
async def chat(body: ChatRequest) -> ChatResponse:
    return ChatResponse(reply=f"Echo: {body.message}", tokens_used=5)
```

> **Ruko, socho:** Python mein `dataclass` bhi types hold karta hai — to Pydantic kyun? (Jawab: `dataclass` sirf types *likhता* hai, runtime pe check nahi karta. Pydantic actually validate + coerce karta hai aur JSON schema deta hai — isliye untrusted API input ke liye Pydantic.)

> **→ Practice A1** — `ChatRequest` + `ChatResponse` complete karo; invalid input pe `ValidationError` aaye.

---

### §5. httpx async — external APIs call karna

LLM providers, embedding APIs — sab HTTP pe hain. `httpx` modern `requests` jaisा hai par async support ke saath, isliye gateway mein yahi use hoga.

```python
import httpx, asyncio

async def fetch_json(url: str) -> dict:
    async with httpx.AsyncClient(timeout=10.0) as client:
        response = await client.get(url)
        response.raise_for_status()   # 4xx/5xx pe exception
        return response.json()

async def fetch_all(urls: list[str]) -> list[dict]:
    tasks = [fetch_json(u) for u in urls]
    return await asyncio.gather(*tasks)   # sab parallel
```

Ek baat jo production mein bhoolna mehenga padta hai: **timeout hamesha do.** LLM API kabhi-kabhi hang ho jaati hai, aur bina timeout ke tumhara worker us request pe hamesha ke liye atka reh jaayega. `httpx.Timeout(10.0, connect=5.0)` jaisा explicit timeout connection aur overall dono pe limit lagata hai.

POST karna (jaise OpenAI ko):

```python
await client.post(
    "https://api.openai.com/v1/chat/completions",
    headers={"Authorization": f"Bearer {api_key}"},
    json={"model": "gpt-4o-mini", "messages": [{"role": "user", "content": "hi"}]},
)
```

---

### §6. Sab jod ke — gateway ka mental model

Ab in sab ko ek saath dekho — yahi shape Module 00c aur Project 1 ke gateway mein baar-baar aayega:

```
Client POST /chat
  → FastAPI body ko Pydantic se validate karta hai
  → async handler:
       → await redis.get(cache_key)        # tez, par phir bhi await
       → await httpx.post(openai_url)       # slow — yahan loop free rehta hai
       → await redis.set(cache_key)
  → ChatResponse (Pydantic) → JSON
```

Gaur karo har slow step `await` ke peeche hai — isliye jab ek client ka OpenAI call chal raha hota hai, server doosre clients ko serve karता rehta hai. Yahi async ka poora point hai.

---

## Practice

> **Saare assignments ek jagah**: [practice/README.md](practice/README.md) — problem statements, pass criteria.
> Code **tum** likhoge Cursor mein. Stubs `practice/` mein (`TODO` search).
> Stuck? Chat: `@modules/00b-python-async/MODULE.md` + error paste karo.

| # | File | Kya karna hai | Pass when |
|---|------|---------------|-----------|
| A1 | `practice/chat_models.py` | `ChatRequest` + `ChatResponse` complete | Invalid input → `ValidationError` |
| A2 | `practice/parallel_fetch.py` | 3 URLs parallel `gather` | Total time ≈ slowest, sum nahi |
| A3 | `practice/broken_async.py` | Sync blocking fix karo | Bug + fix NOTES mein explain |
| A4 | `NOTES.md` | Zod schema → Pydantic side-by-side | 1 schema, dono versions |

### A1 hints
- `Field(min_length=1)` message ke liye; `tokens_used: int` response mein required.

### A2 hints
- Test URLs: `https://httpbin.org/delay/1` (3 alag paths). `time.perf_counter()` se before/after measure karo.

### A3 hints
- `time.sleep` → `asyncio.sleep`; `requests` → `httpx.AsyncClient`.

---

## Active recall (khud jawab likho NOTES mein)

1. `async def` ke andar sync blocking call kyun poore server ko rok deti hai?
2. Pydantic vs dataclass — kab Pydantic chahiye aur kyun?
3. LLM API call async kyun honi chahiye — ek line mein.

**Chat drill** (optional): "Module 00b recall — 3 questions mujhse poochh."

---

## Progress checklist

- [ ] §0 syntax try kiya
- [ ] Theory §1–§6 padha
- [ ] Redraw challenge kiya
- [ ] Practice A1–A4 pass
- [ ] Active recall NOTES mein likha
- [ ] NOTES session log updated

---

## Optional appendix (zarurat ho tab)

- [asyncio — Coroutines and Tasks](https://docs.python.org/3/library/asyncio-task.html)
- [Pydantic — Models](https://docs.pydantic.dev/latest/concepts/models/)
- [httpx — AsyncClient](https://www.python-httpx.org/async/)
