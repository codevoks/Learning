# Module 06 — Tools & Function Calling

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 05](../05-rag-pgvector/MODULE.md) · Next → [Module 07](../07-agents-langgraph/MODULE.md)

> **Format**: Textbook — §0 terms pehle (tool, function calling, JSON schema), prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`

## At a glance

| | |
|---|---|
| Prerequisites | Module 05 (optional). 00c (Pydantic). 01 (messages API) |
| Duration | ~4–6 sessions |
| Project? | No |
| Exit test | Tool schema design + tool loop flow bina notes ke whiteboard karo |

## Yeh module kis baare mein hai

Ab tak LLM sirf *baat* kar sakta tha — text in, text out. Par asli products ko **action** chahiye: DB mein search karo, weather laao, email bhejo. Tools (function calling) wahi pul hai. Aur yahan ek bahut important — aur security-critical — baat samajhni hai: **model tool khud nahi chalata.** Model sirf *plan* karta hai ("mujhe `get_weather` chahiye `city=Berlin` ke saath"), aur **tumhara code** us request ko validate karke actually run karta hai.

Manager-worker socho: LLM manager hai jo memo likhta hai "warehouse se item #42 lao"; tumhara code worker hai jo actually warehouse jaata hai. Manager ke paas warehouse ki chaabi nahi hoti. Yeh separation hi tumhe safe rakhta hai — model galat ya malicious instruction de bhi de, action sirf tumhare validated code ke through hoti hai.

```
User query → LLM + tool definitions → tool_call {name, args} → [validate] → execute → result → LLM final answer
```

**Redraw challenge:** User → LLM → tool_call → executor → result → final answer bina dekhe banao.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + §1 Tools concept | Ek JSON schema haath se likho |
| 2 | §2 Tool schemas | **A1** — `tool_schemas.py` |
| 3 | §3 Tool call loop | **A1** complete — 10/10 tool pick |
| 4 | §4 Structured vs tools + §5 Pydantic | **A2** — `pydantic_tools.py` |
| 5 | §6 Idempotency + end-to-end | **A3** — `multi_step_loop.py` |

---

## Theory

### §0. Terms pehli baar — tools, function calling, JSON schema (20 min)

**Tool (function).** LLM ke liye ek **named capability** jo tum define karte ho — jaise `get_weather(city)` ya `search_docs(query)`. Phir se: model tool **nahi chalata**, sirf maangता hai; tumhara Python run karta hai.

**Function calling.** Provider ka wo feature jisse model plain text ke bajaye ek **structured tool request** de sakta hai:

```json
{ "tool_calls": [{ "id": "call_abc", "type": "function",
    "function": { "name": "get_weather", "arguments": "{\"city\": \"Berlin\"}" } }] }
```

Ek baat jo bug deti hai naye logon ko — `arguments` ek JSON **string** hai (object nahi), to use `json.loads` se parse karke phir validate karna padta hai. (OpenAI ise `tool_calls` kehta hai, Anthropic `tool_use` blocks — loop same hai, §3.)

**JSON Schema.** Tool ke parameters ka **shape** — types, required fields, descriptions:

```json
{ "type": "object",
  "properties": { "city": { "type": "string", "description": "City name in English" } },
  "required": ["city"] }
```

HTML form socho — `city` required text field, `limit` optional number. LLM is schema ko padhkar decide karta hai **kab** tool call karna hai aur **kya** args bhejne hain — isliye `description` likhna optional nahi, wahi model ka guide hai.

**Tool result message.** Tool chalने ke baad tum result ko ek naye message ke roop mein wapas LLM ko bhejte ho:

```python
{"role": "tool", "tool_call_id": "call_abc", "content": '{"temp_c": 18, "condition": "cloudy"}'}
```

Phir LLM us result se final natural-language jawab banata hai.

> **Ruko, socho:** Jab model `tool_calls` return karta hai, kya wo database already query kar chuka hai? (Jawab: nahi — usne sirf *request* di hai. Koi side-effect nahi hua jab tak tumhara code execute na kare. Yahi reason hai ki control tumhare paas rehta hai.)

**§0 checkpoint:** (1) Model khud DB query karta hai ya request return karta hai? (2) `arguments` string hai ya object? (3) Schema mein `description` kyun?

---

### §1. Tools = LLM ko APIs dena, execution tumhara

User poochhta hai "Berlin ka weather kaisa hai aur docs mein refund policy dhoondo." Model ke paas na live weather hai na tumhare docs — par agar tum tools de do, model *plan* karega kaunsa tool pehle, kaunsa baad. Division of labour saaf hai: **LLM (probabilistic) decide karta hai** kaunsa tool aur kya arguments; **tum (deterministic) validate, auth, rate-limit, aur actual I/O** karte ho.

Isse ek security rule nikalta hai jo har agentic system ka core hai: **model ke bole bina koi write-action mat chalao, aur sirf registered (allowlisted) tools hi available rakho.** Model jo bhi suggest kare, wo tabhi hoga jab tumhara code use validate karke explicitly execute kare.

---

### §2. Tool schemas — JSON Schema shape

Galat schema ka seedha natija — model galat tool pick karega ya args todega. Ek poora tool definition:

```python
TOOLS = [{
    "type": "function",
    "function": {
        "name": "search_docs",
        "description": "Search internal company documentation by keyword. Use when the user asks about policies, refunds, or product docs.",
        "parameters": {
            "type": "object",
            "properties": {
                "query": {"type": "string", "description": "Search terms, e.g. 'refund policy'"},
                "limit": {"type": "integer", "description": "Max results, default 5"},
            },
            "required": ["query"],
        },
    },
}]
```

Is poore definition mein sabse important field `description` hai — naye log isे bhar dete hain bina soche, par **model mostly isi se decide karta hai kaunsा tool kab use karna hai.** "Searches docs" bekaar hai; "Use when the user asks about policies, refunds, or product docs" achha hai kyunki yeh weather tool se clearly distinguish karta hai. `required` array bhi critical — usse missing arg execute se *pehle* fail ho jaata hai.

Practice mein stubs use karo (fake data, par shape real rakho):

```python
def search_docs(query: str, limit: int = 5) -> dict:
    fake_db = [{"id": "doc1", "title": "Refund Policy", "snippet": "30 day returns..."}]
    return {"results": [d for d in fake_db if query.lower() in d["title"].lower()][:limit]}
```

#### §2 common errors

| Symptom | Kyun | Fix |
|---------|------|-----|
| 10% baar galat tool | Descriptions overlap karti hain | Har tool ka "Use when..." narrow karo |
| Invalid JSON args | Schema vague | `required` + types explicit |
| Model kabhi tool call nahi karta | Description bahut strict | Description mein examples |

> **→ Practice A1** (`tool_schemas.py`) — 2 tools, 10 prompts, correct tool 10/10.

---

### §3. Tool call loop

Ek single API call kaafi nahi hai — model pehle tool maangega, tum result do, phir wo final jawab banayega. Kabhi-kabhi yeh kai baar repeat hota hai (multi-step), isliye yeh ek **loop** hai:

```python
TOOL_IMPL = {"search_docs": search_docs, "get_weather": get_weather}

def run_with_tools(user_message: str) -> str:
    messages = [{"role": "user", "content": user_message}]
    while True:
        response = client.chat.completions.create(
            model="gpt-4o-mini", messages=messages, tools=TOOLS, tool_choice="auto")
        msg = response.choices[0].message
        messages.append(msg)
        if not msg.tool_calls:
            return msg.content or ""          # koi tool nahi maanga → done
        for tc in msg.tool_calls:
            args = json.loads(tc.function.arguments)   # string → dict
            result = TOOL_IMPL[tc.function.name](**args)
            messages.append({"role": "tool", "tool_call_id": tc.id, "content": json.dumps(result)})
```

Loop ki dhuri yeh hai: har iteration mein model ko messages + tools bhejo. Agar wo `tool_calls` deta hai, to har tool chalao aur uska result `role: tool` message mein wapas append karo, phir loop dobara. Jab model bina tool maange text deta hai, wahi final jawab hai aur loop khatam. `fn(**args)` Python unpacking hai — `{"query": "x"}` ko `search_docs(query="x")` bana deta hai. (Model ek hi turn mein do tools bhi maang sakta hai — "parallel tool calls" — to bas dono chalao, dono results append karo.)

Production mein tool fail ho sakta hai, to crash karne ke bajaye structured error wapas bhejo — model use padhkar user se clarify kar sakta hai:

```python
try:
    result = fn(**args)
except Exception as e:
    result = {"error": str(e), "retry_hint": "Check city spelling"}
```

> **Ruko, socho:** Agar model ne ek turn mein 2 tools maange aur tum sirf pehle ka result append karke turant LLM ko dobara call kar do, to kya hoga? (Jawab: API error ya confusion — har `tool_call` ka ek matching `tool` result hona chahiye agli LLM call se pehle. Saare tools chalao, sab results append karo, *phir* model ko wapas bulao.)

#### §3 common errors

| Error | Kyun | Fix |
|-------|------|-----|
| Infinite loop | Tool result format galat | `content` mein valid JSON string |
| `KeyError` tool name pe | `TOOL_IMPL` mein typo | Names schema se exact match |
| Khaali final answer | `msg.content` None jab tool_calls hai | Normal — agla iteration |

> **→ Practice A3** (`multi_step_loop.py`) — query jisme 2 tools sequence mein chahiye.

---

### §4. Structured outputs vs tool calling

Dono JSON dete hain, isliye log confuse ho jaate hain — par maqsad alag hai. **Structured output** (Module 04 ka `response_format`) tab hai jab tumhe final answer ek fixed shape mein chahiye, bina kisi side-effect ke — jaise `{"bullets": [...]}` report. **Tool calling** tab hai jab external actions ya multi-step kaam ho — DB search, email bhejो.

Same query ko intent se decide karo: "Return sales summary as JSON" → structured output (koi action nahi). "Look up sales in DB then email" → tools (DB + email, side-effects). Yaad rakho: structured output **ek** LLM call hai shape-enforced; tools ek **loop** hai side-effects aur fresh data ke saath.

---

### §5. Pydantic validation — args ko execute se pehle check karo

Model ek probabilistic system hai — wo `limit: "five"` (string) ya `limit: 999` bhej sakta hai. Agar tum yeh seedhe DB ko de doge, crash ya abuse. Isliye **execute se pehle** Pydantic se validate karo (00c se familiar):

```python
class SearchDocsArgs(BaseModel):
    query: str = Field(description="Search terms")
    limit: int = Field(default=5, ge=1, le=20)

SCHEMA_MAP = {"search_docs": SearchDocsArgs, "get_weather": GetWeatherArgs}

def safe_execute(name: str, arguments_json: str) -> dict:
    try:
        args = SCHEMA_MAP[name].model_validate_json(arguments_json)
    except ValidationError as e:
        return {"error": "invalid_args", "details": e.errors()}   # DB ko chhua bhi nahi
    return TOOL_IMPL[name](**args.model_dump())
```

`ge=1, le=20` limit ko bound karta hai (999 reject), aur `model_validate_json` JSON string ko typed object banata hai. Asli point yeh hai — galat args pe hum `ValidationError` catch karke ek error wapas dete hain, **DB ko call hi nahi karte**. Yeh security aur stability dono ke liye zaroori hai. Loop mein raw `fn(**args)` ki jagah `safe_execute` use karo.

> **→ Practice A2** (`pydantic_tools.py`) — invalid args execute se pehle reject hon.

---

### §6. Idempotent tools — retries ko safe banao

Yahan ek khatarnak scenario hai. Network retry hota hai, ya model galti se do baar `send_refund` maang leta hai — aur tumne customer ko **do baar refund** kar diya. Read-only tools (jaise `search_docs`) ke liye yeh problem nahi (do baar search = same result). Par **write** tools (charge, refund, email) ke liye yeh disaster hai.

Fix **idempotency key** hai — ek unique key jise tum DB ke UNIQUE constraint se baandhte ho, taaki dusri baar wahi call same result laaye, double-charge nahi:

```python
class RefundArgs(BaseModel):
    order_id: str
    amount: float
    idempotency_key: str   # client-generated UUID; DB pe UNIQUE(idempotency_key)
```

Yeh tumhara outbox/exactly-once (Module 11) waala same dimaag hai. Rule: read-only tools easy hain; write tools ko **must** idempotency key + DB constraint chahiye.

---

### End-to-end (yahi A1+A3 hai)

Sab jodke: `TOOLS` define karo (§2), `run_with_tools` loop banao (§3), loop mein `safe_execute` use karo (§5), phir ek multi-step query chalao jaise "What's the weather in Berlin and search docs for refund policy?" — model dono tools maangega (parallel ya sequence), dono results append honge, aur final answer weather + policy dono combine karega. Quality check ke liye 10 prompts ka regression test banao jo verify kare har prompt sahi tool pe route hua (A1 ka 10/10).

#### end-to-end common errors

| Symptom | Kyun | Fix |
|---------|------|-----|
| Sirf pehla tool chala | Loop jaldi break ho gaya | Agle LLM call se pehle saare results append |
| Final answer mein JSON | Model confused | Tool descriptions clear karo |
| Weather mein galat city | Args validate nahi hue | Pydantic + tests |

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §2, §3 | `tool_schemas.py` | LLM correct tool pick 10/10 |
| A2 | §5 | `pydantic_tools.py` | Invalid args execute se pehle reject |
| A3 | §3, §6 | `multi_step_loop.py` | 2-tool chain wali query complete ho |

---

## Active recall (khud jawab likho NOTES mein)

1. Tool description ki quality output pe kyun matter karti hai?
2. Tool fail ho — LLM ko kya bhejoge, aur kyun structured error?
3. Structured output vs tool calling — same query pe kab alag choose?
4. Idempotency write tools pe kyun zaroori?

**Chat drill** (optional): "Module 06 — tool loop whiteboard karo."

---

## Progress checklist

- [ ] §0 terms (tool, function calling, JSON schema)
- [ ] Theory §1–§6 padha
- [ ] End-to-end chalaya
- [ ] Redraw challenge
- [ ] Practice A1–A3 pass
- [ ] Active recall NOTES mein

---

## Optional appendix

- [OpenAI Function calling](https://platform.openai.com/docs/guides/function-calling)
- [Anthropic Tool use](https://docs.anthropic.com/en/docs/build-with-claude/tool-use)
