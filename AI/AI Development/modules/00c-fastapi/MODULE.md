# Module 00c — FastAPI

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 00b](../00b-python-async/MODULE.md) · Next → [Module 00d](../00d-ml-ai-foundations/MODULE.md)

> **Format**: Textbook — §0 Python/FastAPI syntax pehle (prose), phir concepts. Voice: `@MODULE-TEACHING-STANDARD.md`

## At a glance

| | |
|---|---|
| Prerequisites | 00a (venv/Docker). 00b recommended (async + Pydantic) — skip kiya to §0 yahan cover ho jaata hai |
| Duration | ~5–7 sessions (Python naya hai to zyada time normal) |
| Project? | No (par Project A/B ka Python stack yahi hai) |
| Exit test | Khud se `/health` + `/chat` route likho, curl se demo, middleware/Depends samjhao |

## Yeh module kis baare mein hai

FastAPI wo framework hai jisme tum apna **LLM gateway** banaoge — wo server jo client se request leta hai, validate karta hai, OpenAI ko call karta hai, aur jawab wapas bhejta hai. Tum Express jaante ho, to mental model already ready hai: routes, middleware, JSON in/out. Bas yahan Python ki grammar nayi hai aur FastAPI kuch cheezein (validation, docs) automatic de deta hai jo Express mein tum haath se likhte the.

Yeh module thoda lamba hai (10 sections) kyunki yeh tumhare Python backend ki neev hai. §0 mein Python ki wo 8 cheezein samjhaunga jo FastAPI padhne se pehle chahiye — phir ek-ek karke server, routes, validation, auth, middleware, streaming.

## Visual map

```
Browser / curl
      │  HTTP (GET/POST, headers, JSON body)
      ▼
┌────────────────────────────────────────┐
│  uvicorn  ← yeh process HTTP sunta hai   │
│    └── FastAPI app  ← routes + validation│
│          ├── middleware  (har request)   │
│          ├── Depends     (kuch routes)   │
│          └── handler     (tumhara code)  │
└────────────────────────────────────────┘
      │
      ▼
   JSON response
```

Ek baat abhi note kar lo jo log gadbada dete hain: **FastAPI khud server nahi hai.** Tum FastAPI mein routes likhte ho, par HTTP actually **uvicorn** sunta hai (Node mein `node server.js`, yahan `uvicorn app.main:app`).

**Redraw challenge**: Client → uvicorn → FastAPI → middleware → route → response bina dekhe banao.

---

## Read order (strict — mat chhodna)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Python syntax | Terminal pe chhote snippets try |
| 2 | §1 Setup + §2 Pehla server | **A1** start — `/health` chalao |
| 3 | §3 Decorator + §4 POST/Pydantic | **A1** complete — `/chat` echo |
| 4 | §5 Routers | **A2** |
| 5 | §6 Errors + §7 Depends | **A4** |
| 6 | §8 Middleware + §9 SSE | **A3, A5** |
| 7 | §10 Wire-up + active recall | **A6** NOTES |

---

## Theory

### §0. Python pehli baar — FastAPI se pehle yeh (20 min)

Tum TypeScript jaante ho. Python wahi ideas, alag grammar. Yeh 8 cheezein ek baar samajh lo, phir har FastAPI line padhi-padhi lagegi.

**1. Indentation = brackets.** Python mein `{}` nahi — block indentation se banta hai (4 spaces). Galat indent = `IndentationError`.

```python
def greet():
    print("hello")    # 4-space indent = block ke andar
```

**2. Values aur dict.** `name = "Vansh"` (str), `count = 42` (int), `ok = True` (bool, capital). dict = JS object: `user = {"id": 1, "name": "Vansh"}`, access `user["name"]`. f-string interpolation ke liye: `f"Hello {name}"`. FastAPI mein `return {"status": "ok"}` ka matlab — dict return kiya, wo JSON ban jaata hai (`res.json({...})` jaisा).

**3. Function aur `async def`.** `def add(a: int, b: int) -> int` — normal function. `async def fetch_data()` — coroutine, jo `await` use kar sakta hai. FastAPI routes ke liye `async def` recommended hai (kyunki wo DB/API ka wait karte hain — 00b waali baat). TS parallel: `function` vs `async function`.

**4. Import.** `import json` poori library, `from fastapi import FastAPI` sirf ek cheez, `from app.models import ChatRequest` apni file se (`import { ChatRequest } from './models'` jaisा).

**5. Class.** Pydantic models classes hain. `class ChatRequest(BaseModel):` ka matlab — `ChatRequest` naam ki class jo `BaseModel` se extend karti hai (validation inherit karti hai), aur andar `message: str` ek field hai jise string hona chahiye. Zod ka `z.object({ message: z.string() })` hi hai, Python shabdon mein.

**6. `@decorator` — yeh FastAPI ka dil hai.** Decorator ek function ke upar `@something` likhna hai jo us function ko wrap/register karta hai. Pehle FastAPI ke bina samjho:

```python
def loud(fn):
    def wrapper():
        print("BEFORE"); fn(); print("AFTER")
    return wrapper

@loud
def hello():
    print("hello")

hello()   # BEFORE / hello / AFTER
```

`@loud` ka matlab automatically `hello = loud(hello)`. Ab FastAPI mein:

```python
@app.get("/health")
async def health():
    return {"status": "ok"}
```

Iska matlab: "FastAPI, jab `GET /health` aaye to neeche wala `health` function chalao". Express mein tum `app.get("/health", health)` alag likhte the; Python mein decorator register + function ek saath kar deta hai. `@` dekh ke ghabraana mat — bas "route register" samjho.

**7. `None` aur optional.** `q: str | None = None` — query param optional (Python 3.10+). Default `None` matlab "dena zaroori nahi".

**8. Terminal pe try karo:**

```bash
python3
>>> name = "test"
>>> {"status": "ok", "name": name}
{'status': 'ok', 'name': 'test'}
>>> exit()
```

Basics aa gaye — ab FastAPI.

---

### §1. Project setup — folder, venv, install

Pehla folder structure samjho, kyunki Python imports ispe depend karte hain:

```
modules/00c-fastapi/practice/   ← yahan se commands chalao
├── .venv/                      ← virtual env (gitignore)
└── app/                        ← Python package (code yahan)
    ├── __init__.py             ← khali file — "yeh folder ek package hai"
    ├── main.py                 ← FastAPI app + entry
    ├── models.py               ← Pydantic schemas
    ├── deps.py                 ← auth helper
    ├── middleware.py
    └── routes/
        ├── __init__.py
        ├── health.py
        ├── chat.py
        └── events.py
```

Wo `__init__.py` files khaali hain par zaroori — yeh Python ko batati hain ki `app` ek **package** hai, taaki `from app.models import X` kaam kare. Aur ek baat jo naye log ko hamesha kaat-ti hai: commands hamesha **`practice/` folder se** chalao (`cd modules/00c-fastapi/practice`), warna `ModuleNotFoundError: No module named 'app'` milega — kyunki Python `app` package ko current directory se dhoondhता hai.

venv aur dependencies (00a se aata hai):

```bash
python3 -m venv .venv          # ek baar
source .venv/bin/activate      # har nayi terminal
pip install fastapi uvicorn httpx pydantic
```

Yahan `fastapi` framework hai, `uvicorn` wo **ASGI server** jo actually HTTP sunta hai, `httpx` HTTP client (aage), `pydantic` validation. Server chalane ka command:

```bash
uvicorn app.main:app --reload --port 8000
```

Isे todke samjho: `app.main` matlab file `app/main.py`, `:app` matlab us file mein `app = FastAPI(...)` waala variable, `--reload` matlab code badले to auto-restart (dev only), `--port 8000` matlab `localhost:8000`. Dono `app` alag hain — pehla folder/file, doosra variable. (Yeh active-recall mein wapas aayega.)

---

### §2. Pehla server — `GET /health`

`app/main.py`:

```python
from fastapi import FastAPI

app = FastAPI(title="LLM Gateway", version="0.1.0")

@app.get("/health")
async def health():
    return {"status": "ok"}
```

Teen line ka kaam: `app = FastAPI(...)` app object banata hai jispe saari routes chipakti hain; `@app.get("/health")` decorator `GET /health` ko neeche wale function se jodta hai; aur `return {"status": "ok"}` ek dict deta hai jo FastAPI khud JSON response bana deta hai (status 200 default).

Chalao aur test karo:

```bash
cd modules/00c-fastapi/practice
source .venv/bin/activate
uvicorn app.main:app --reload --port 8000
```

```bash
curl http://localhost:8000/health
# {"status":"ok"}
```

Ek bonus jo FastAPI free mein deta hai: browser mein `http://localhost:8000/docs` kholo — **Swagger UI** automatically ban jaati hai, bina Postman ke har endpoint test kar sakte ho. Yeh Express mein nahi milta; FastAPI tumhare type hints se docs bana leta hai.

#### Common errors

| Error | Kyun | Fix |
|-------|------|-----|
| `ModuleNotFoundError: app` | Galat folder se run | `cd practice/` |
| `No module named 'fastapi'` | venv activate nahi / install nahi | `source .venv/bin/activate` + install |
| `Address already in use` | Port 8000 busy | `--port 8001` ya purana process kill |
| `404 Not Found` on `/health` | Route register nahi / URL typo | `@app.get("/health")` check |

**A1 checkpoint 1:** `/health` curl se 200 + JSON.

---

### §3. Routes aur decorator — GET vs POST

Method aur path decorator mein hote hain — `@app.get("/items")`, `@app.post("/chat")`, `@app.delete("/items/5")` — Express ke `app.get`/`app.post` jaisा hi.

FastAPI input ko teen jagah se padhता hai, aur yeh farak samajhna zaroori hai:

**Path parameter** — URL ke andar variable. `@app.get("/users/{user_id}")` mein `user_id: int` likho, to `GET /users/42` pe `user_id = 42` milega (FastAPI string `"42"` ko int bana deta hai). Aur agar `/users/abc` aaya, FastAPI khud `422` validation error de dega — tumhe check nahi likhna padta.

```python
@app.get("/users/{user_id}")
async def get_user(user_id: int):
    return {"user_id": user_id}
```

**Query parameter** — `?` ke baad. `@app.get("/search")` mein `q: str, limit: int = 10` likho, to `?q=hello&limit=5` se dono milte hain, aur `limit` na de to default 10.

```python
@app.get("/search")
async def search(q: str, limit: int = 10):
    return {"q": q, "limit": limit}
```

Rule: jo cheez path ke `{braces}` mein hai → path param; jo simple type bahar hai → query param; aur JSON body ke liye Pydantic class (§4).

> **Ruko, socho:** `@app.get("/users/{user_id}")` mein agar `user_id` ka type hint `int` na do (sirf `user_id`), to `/users/42` pe kya milega — int `42` ya string `"42"`? (Jawab: string. Type hint hi FastAPI ko conversion + validation karne ko kehta hai — isliye hints aise frameworks mein optional nahi hain.)

---

### §4. Pydantic — POST body validate karo

`models.py` mein schemas (00b se Pydantic):

```python
from pydantic import BaseModel, Field

class ChatRequest(BaseModel):
    message: str = Field(min_length=1, max_length=4000)

class ChatResponse(BaseModel):
    reply: str
    tokens_used: int
```

Route mein body ka type `ChatRequest` likhते hi jaadu ho jaata hai — FastAPI request JSON ko us schema se **automatically** validate karta hai:

```python
from fastapi import APIRouter
from app.models import ChatRequest, ChatResponse

router = APIRouter(tags=["chat"])

@router.post("/chat", response_model=ChatResponse)
async def chat(body: ChatRequest) -> ChatResponse:
    return ChatResponse(reply=f"Echo: {body.message}", tokens_used=len(body.message))
```

Request ka poora flow yeh hai, aur step 3 sabse important hai:

```
1. Client: POST /chat {"message":"hi"}
2. FastAPI body parse → ChatRequest.model_validate(...)
3. Fail (empty message) → 422, handler tak pahunchta HI nahi
4. Pass → chat() chalega, body.message guaranteed typed str
5. Return ChatResponse → JSON {"reply":"Echo: hi","tokens_used":2}
```

Iska matlab — tumhare handler ke andar body kabhi invalid nahi hoga, validation pehle ho chuki. `response_model=ChatResponse` ulta direction mein bhi kaam karta hai: response ko validate karke extra fields kaat deta hai, taaki galti se internal data leak na ho.

`main.py` mein router mount karo: `app.include_router(chat_router)`.

curl se khud test karo — pass aur fail dono:

```bash
curl -X POST http://localhost:8000/chat -H "Content-Type: application/json" -d '{"message":"hello"}'   # ✅ 200
curl -X POST http://localhost:8000/chat -H "Content-Type: application/json" -d '{"message":""}'        # ❌ 422 (empty)
curl -X POST http://localhost:8000/chat -H "Content-Type: application/json" -d '{}'                    # ❌ 422 (missing)
```

422 response ke andar ek `detail` array hota hai jo batata hai kaunsi field kyun fail hui — clients ko isi se pata chalta hai kya galat bheja.

**A1 complete:** POST echo + 422 on bad input.

---

### §5. APIRouter — files alag karo

Ek file mein sab kuch seekhne ke liye theek hai, par gateway badhega to ek `main.py` mein 50 routes maintain karna dukh hai. `APIRouter` se har domain (health, chat, events) apni file mein jaata hai, aur `main.py` sabko jodता hai:

```python
# app/routes/health.py
from fastapi import APIRouter
router = APIRouter(tags=["health"])

@router.get("/health")
async def health():
    return {"status": "ok"}
```

```python
# app/main.py
from fastapi import FastAPI
from app.routes.health import router as health_router
from app.routes.chat import router as chat_router

app = FastAPI(title="Practice Gateway")
app.include_router(health_router)
app.include_router(chat_router)
# Version prefix chahiye to: app.include_router(chat_router, prefix="/v1")
```

Yeh Express ke `const r = Router(); app.use(r)` ka exact analog hai. `/docs` pe ab dono endpoints dikhne chahiye.

---

### §6. HTTPException — tum khud error bhejo

Pydantic body-validation ke liye 422 automatic de deta hai, par **business logic** errors tumhe khud throw karne hote hain (jaise "user nahi mila"). Python mein throw karne ka shabd `raise` hai:

```python
from fastapi import HTTPException

@router.get("/users/{user_id}")
async def get_user(user_id: int):
    if user_id < 1:
        raise HTTPException(status_code=400, detail="Invalid user id")
    if user_id == 999:
        raise HTTPException(status_code=404, detail="User not found")
    return {"user_id": user_id}
```

`raise HTTPException(404, detail="...")` Express ke `res.status(404).json({detail:"..."})` jaisा hai — FastAPI ise catch karke sahi HTTP response bana deta hai. Status codes ka quick mental map: `400` tumne reject kiya, `401` auth fail, `404` not found, `422` Pydantic body galat (automatic), `500` koi bug (prod mein log karo, generic message do — internal details leak mat karo).

---

### §7. Depends() — auth ek jagah, har route pe inject

Maan lo har protected route pe tum API key check copy-paste kar rahe ho. Yeh bura code hai — ek jagah badlo to sab jagah badalna padega. FastAPI ka **`Depends`** isका jawab hai: ek dependency function likho, aur use jis bhi route ko chahiye usme inject kar do.

Pehle dependency function (`app/deps.py`):

```python
from fastapi import Header, HTTPException

DEV_SECRET = "dev-secret"

async def verify_api_key(x_api_key: str = Header(..., alias="X-API-Key")):
    if x_api_key != DEV_SECRET:
        raise HTTPException(status_code=401, detail="Invalid or missing API key")
    return x_api_key
```

Yahan `Header(..., alias="X-API-Key")` ka matlab — `X-API-Key` header padho, aur `...` matlab wo required hai. Ab route mein inject:

```python
from fastapi import Depends
from app.deps import verify_api_key

@router.post("/chat")
async def chat(body: ChatRequest, api_key: str = Depends(verify_api_key)):
    return ChatResponse(reply=body.message, tokens_used=1)
```

`Depends(verify_api_key)` FastAPI ko kehta hai "handler chalane se *pehle* yeh function chalao". Flow: `Request → verify_api_key() → (401 ya ok) → chat()`. Express mein yeh ek shared middleware ya `requireAuth` call hoti; FastAPI ise declarative bana deta hai. Test:

```bash
curl -X POST .../chat -H "Content-Type: application/json" -d '{"message":"hi"}'                          # ❌ 401
curl -X POST .../chat -H "Content-Type: application/json" -H "X-API-Key: dev-secret" -d '{"message":"hi"}' # ✅ 200
```

---

### §8. Middleware — har request/response pe

`Depends` specific routes pe lagta hai. **Middleware** har request pe chalता hai jo app se guzarti hai — logging, request IDs, CORS jaisे cross-cutting kaam ke liye. Ek example jo har response pe ek `X-Request-ID` header lagata hai (production mein ek request ko logs mein trace karne ke liye zaroori):

```python
import uuid
from starlette.middleware.base import BaseHTTPMiddleware

class RequestIDMiddleware(BaseHTTPMiddleware):
    async def dispatch(self, request, call_next):
        request_id = request.headers.get("X-Request-ID") or str(uuid.uuid4())
        response = await call_next(request)   # andar bhejo — routes chalenge
        response.headers["X-Request-ID"] = request_id
        return response
```

Asli cheez `dispatch` method hai: har request yahan aati hai, `await call_next(request)` use andar routes tak bhejta hai aur response wapas laata hai, phir tum response ko modify karke return karte ho. Register `main.py` mein: `app.add_middleware(RequestIDMiddleware)`. Test: `curl -i http://localhost:8000/health` — response headers mein `X-Request-ID` dikhega.

---

### §9. SSE streaming — LLM ka preview

Abhi tak har response poora JSON ek shot mein gaya. LLM mein tokens **stream** honge (Module 01), to FastAPI ka streaming pattern abhi dekh lo. `yield` keyword ek-ek piece bhejता hai (generator), aur SSE format mein har event `data: ...\n\n` (do newline zaroori) hota hai:

```python
from fastapi.responses import StreamingResponse
import asyncio

async def tick_generator():
    for i in range(5):
        yield f"data: tick {i}\n\n"
        await asyncio.sleep(1)

@router.get("/events")
async def events():
    return StreamingResponse(tick_generator(), media_type="text/event-stream")
```

Test `curl -N http://localhost:8000/events` se — `-N` (no-buffer) zaroori hai warna curl sab kuch end tak rok ke ek saath dikhayega. Module 01 mein OpenAI ke tokens bilkul isi pattern se aayenge.

---

### §10. Sab wire — final `main.py`

A1–A5 ho jaayein to `main.py` aisा dikhega:

```python
from fastapi import FastAPI
from app.middleware import RequestIDMiddleware
from app.routes.health import router as health_router
from app.routes.chat import router as chat_router
from app.routes.events import router as events_router

app = FastAPI(title="Practice Gateway")
app.add_middleware(RequestIDMiddleware)   # middleware pehle
app.include_router(health_router)
app.include_router(chat_router)
app.include_router(events_router)
```

Order matter karta hai: middleware routers se pehle register karo, taaki har route us middleware se guzre.

---

## Practice

> [`practice/README.md`](practice/README.md) — har assignment ke pass criteria. Code **tum** likhoge.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §2–§4 | `main.py`, `models.py`, `routes/chat.py` | POST echo + 422 on bad body |
| A2 | §5–§6 | `routes/` split | `/docs` pe health + chat |
| A3 | §8 | `middleware.py` | `curl -i` → `X-Request-ID` |
| A4 | §7 | `deps.py` | No key → 401 |
| A5 | §9 | `routes/events.py` | `curl -N` streams |
| A6 | §0–§1 | `NOTES.md` | Express vs FastAPI table, 5 rows |

### Run (har session start)

```bash
cd modules/00c-fastapi/practice
source .venv/bin/activate
uvicorn app.main:app --reload --port 8000
```

---

## Active recall (NOTES mein khud likho)

1. `@app.get("/health")` decorator actually karta kya hai?
2. Path vs query vs body — FastAPI kaise decide karta hai kaunsa kaunsa?
3. 422 vs 401 — kaun automatic hai, kaun tum `raise` karte ho?
4. `uvicorn app.main:app` mein dono `app` alag kyun hain?

**Chat drill** (optional): "Module 00c recall — 4 questions mujhse poochh."

---

## Progress checklist

- [ ] §0 Python snippets terminal pe try kiye
- [ ] §1 setup + §2 `/health` chala
- [ ] §4 POST `/chat` + 422 samjha
- [ ] A1–A2 pass
- [ ] A3–A5 pass
- [ ] A6 + active recall NOTES
- [ ] Redraw challenge

---

## Optional appendix (sirf stuck pe)

- [FastAPI Tutorial](https://fastapi.tiangolo.com/tutorial/) — MODULE primary hai
