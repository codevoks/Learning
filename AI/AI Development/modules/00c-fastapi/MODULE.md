# Module 00c — FastAPI

> **Padho**: Isi file mein **Theory** — bahar mat jao.  
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`  
> **Nav**: ← [Module 00b](../00b-python-async/MODULE.md) · Next → [Module 00d](../00d-ml-ai-foundations/MODULE.md)

> **Kaun ke liye:** Pehli baar Python + FastAPI. **§0 syntax pehle** — high-level baad mein. Standard: `@MODULE-TEACHING-STANDARD.md`

## At a glance

| | |
|---|---|
| Prerequisites | 00a (venv/Docker). 00b recommended (async + Pydantic) — skip kiya toh §0–§1 yahan se cover ho jayega |
| Duration | ~5–7 sessions (Python naya hai toh zyada time normal hai) |
| Project? | No (Project A/B Python stack yahi hai) |
| Exit test | Khud se `/health` + `/chat` route likho, curl se demo, middleware/Depends explain karo |

## Visual map

```
Browser / curl
      │  HTTP (GET, POST, headers, JSON body)
      ▼
┌─────────────────────────────────────┐
│  uvicorn  ← yeh process HTTP sunta hai
│    └── FastAPI app  ← routes + validation
│          ├── middleware  (har request)
│          ├── Depends     (sirf kuch routes)
│          └── handler     (tumhara code)
└─────────────────────────────────────┘
      │
      ▼
   JSON response
```

**Redraw challenge**: Client → uvicorn → FastAPI → middleware → route → response draw karo.

---

## Read order (strict — mat chhodna)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Python syntax | Terminal pe chhote snippets try karo |
| 2 | §1 Setup + §2 Pehla server | **A1** start — `/health` chalao |
| 3 | §3 Decorator + §4 POST/Pydantic | **A1** complete — `/chat` echo |
| 4 | §5 Routers | **A2** |
| 5 | §6 Errors + §7 Depends | **A4** |
| 6 | §8 Middleware + §9 SSE | **A3, A5** |
| 7 | §10 Wire-up + active recall | **A6** NOTES |

---

## Theory

### §0. Python pehli baar — FastAPI se pehle yeh (20 min)

Tum TypeScript jaante ho. Python **alag syntax**, same ideas. FastAPI padhne se pehle yeh 8 cheezein **samajh lo** — baad mein har line recognizable lagegi.

#### 0.1 Indentation = brackets

Python mein `{ }` nahi — **indentation (usually 4 spaces)** block batata hai:

```python
# ✅ Sahi
def greet():
    print("hello")      # andar wala block — indent zaroori
    print("world")

# ❌ Galat — IndentationError
def greet():
print("hello")
```

TS: `{` `}` ke andar code. Python: **tab/space se andar**.

#### 0.2 Variables, strings, dict

```python
name = "Vansh"                    # str
count = 42                        # int
ok = True                         # bool — capital T

# dict = JS object jaisa
user = {"id": 1, "name": "Vansh"}
print(user["name"])               # Vansh

# f-string = template literal
msg = f"Hello {name}, count={count}"
```

FastAPI response mein tum **dict return** karte ho → JSON ban jata hai:

```python
return {"status": "ok", "count": count}
# ≈ res.json({ status: "ok", count })
```

#### 0.3 Function — `def` aur `async def`

```python
def add(a: int, b: int) -> int:
    return a + b

async def fetch_data():
    # async = "baad mein wait kar sakta hoon, doosra kaam chalu rakho"
    # Module 00b detail — abhi: route handlers mein async def use karo
    return {"data": "ok"}
```

| | `def` | `async def` |
|---|-------|-------------|
| Matlab | Normal function | Coroutine — `await` use kar sakta hai |
| FastAPI route | Chalega | **Recommended** (DB/API wait) |
| TS parallel | sync function | `async function` |

#### 0.4 Import — dusri file / library se code lao

```python
import json                          # poori library
from fastapi import FastAPI          # sirf FastAPI class
from app.models import ChatRequest   # apni file se
```

| Python | Node/TS |
|--------|---------|
| `import x` | `import x from 'x'` |
| `from app.models import ChatRequest` | `import { ChatRequest } from './models'` |
| `pip install fastapi` | `npm install fastapi` |

#### 0.5 Class — Pydantic ke liye zaroori

Pydantic models **class** hain:

```python
class ChatRequest:
    message: str          # type hint — is field ka type

# Pydantic wala (asli use):
from pydantic import BaseModel

class ChatRequest(BaseModel):
    message: str
```

**Line-by-line:**

| Line | Matlab |
|------|--------|
| `class ChatRequest(BaseModel):` | `ChatRequest` naam ki class, `BaseModel` se extend — validation inherit |
| `message: str` | Field — string honi chahiye |
| Colon `:` ke baad indent | Class ke andar fields |

TS parallel:

```typescript
// Zod
const ChatRequest = z.object({ message: z.string() });

// Python Pydantic
class ChatRequest(BaseModel):
    message: str
```

#### 0.6 `@decorator` — FastAPI ka core (pehle simple example)

**Decorator** = function ke upar `@something` — us function ko **wrap/register** karta hai.

Pehle **FastAPI ke bina** samjho:

```python
def loud(fn):
    def wrapper():
        print("BEFORE")
        fn()
        print("AFTER")
    return wrapper

@loud
def hello():
    print("hello")

hello()
# BEFORE
# hello
# AFTER
```

`@loud` ka matlab: `hello = loud(hello)` — automatically.

**FastAPI mein:**

```python
@app.get("/health")
async def health():
    return {"status": "ok"}
```

Iska matlab: FastAPI ko register karo — **"jab GET /health aaye, `health` function chalao"**.

Express mein alag likhte ho:

```javascript
app.get("/health", health);  // register alag line pe

# Python mein decorator = register + function ek saath
@app.get("/health")
async def health(): ...
```

Yeh **`@`** dekh kar mat darro — bas "route register" samjho.

#### 0.7 `None` aur optional

```python
q: str | None = None    # query optional — Python 3.10+
# purana style: Optional[str] = None
```

FastAPI: default `None` = query param optional.

#### 0.8 Abhi try karo (terminal)

```bash
python3
>>> name = "test"
>>> {"status": "ok", "name": name}
{'status': 'ok', 'name': 'test'}
>>> exit()
```

Python samajh aa gaya basics — ab FastAPI.

---

### §1. Project setup — folder, venv, install (→ A1 se pehle)

#### 1.1 Folder structure — kya kahan hai

```
modules/00c-fastapi/practice/     ← yahan se commands chalenge
├── .venv/                        ← virtual env (gitignore)
└── app/                          ← Python PACKAGE (code yahan)
    ├── __init__.py               ← khali file — "yeh folder package hai"
    ├── main.py                   ← FastAPI app + uvicorn entry
    ├── models.py                 ← Pydantic schemas
    ├── deps.py                   ← auth helpers
    ├── middleware.py
    └── routes/
        ├── __init__.py
        ├── health.py
        ├── chat.py
        └── events.py
```

**`__init__.py` kyun?**  
Python ko batata hai `app` ek **package** hai — `from app.models import X` kaam kare. Khali file OK.

**Important:** Commands **`practice/`** folder se:

```bash
cd modules/00c-fastapi/practice
```

Warna `ModuleNotFoundError: No module named 'app'`.

#### 1.2 Virtual environment — alag `node_modules` jaisa

System Python ganda mat karo — har project apna venv:

```bash
python3 -m venv .venv          # ek baar
source .venv/bin/activate      # har nayi terminal mein
# prompt mein (.venv) dikhega
```

Deactivate: `deactivate`

#### 1.3 Dependencies install

```bash
pip install fastapi uvicorn httpx pydantic
```

| Package | Kyun |
|---------|------|
| `fastapi` | Web framework |
| `uvicorn` | **ASGI server** — HTTP actually sunta hai |
| `httpx` | HTTP client (baad mein) |
| `pydantic` | Validation (00b se aata hai) |

**FastAPI ≠ server.** Tum likhte ho `app = FastAPI()`. Chalane ke liye **uvicorn** alag process:

```bash
uvicorn app.main:app --reload --port 8000
```

| Part | Matlab |
|------|--------|
| `app.main` | File `app/main.py` (folder `app`, file `main.py`) |
| `:app` | Us file mein variable `app = FastAPI(...)` |
| `--reload` | Code change → auto restart (dev only) |
| `--port 8000` | `localhost:8000` |

Node parallel: `node server.js` — yahan `uvicorn app.main:app`.

---

### §2. Pehla server — `GET /health` (→ A1 part 1)

**File:** `app/main.py`

Poora file — har line:

```python
from fastapi import FastAPI

app = FastAPI(title="LLM Gateway", version="0.1.0")

@app.get("/health")
async def health():
    return {"status": "ok"}
```

| Line | Kya hota hai |
|------|--------------|
| `from fastapi import FastAPI` | Library se `FastAPI` class import |
| `app = FastAPI(...)` | App object banao — saari routes isi pe chipkenge |
| `@app.get("/health")` | Decorator: GET request `/health` → neeche wala function |
| `async def health():` | Handler function — naam kuch bhi (`health`, `health_check`) |
| `return {"status": "ok"}` | Dict → FastAPI JSON response banata hai |

**Chalao:**

```bash
cd modules/00c-fastapi/practice
source .venv/bin/activate
uvicorn app.main:app --reload --port 8000
```

**Test:**

```bash
curl http://localhost:8000/health
# {"status":"ok"}
```

Browser: http://localhost:8000/docs — **Swagger UI** — bina Postman test karo.

#### HTTP GET recap (30 sec)

```
GET /health HTTP/1.1
Host: localhost:8000

→ Server response:
HTTP/1.1 200 OK
Content-Type: application/json

{"status":"ok"}
```

Tumhara handler sirf body return karta hai — status 200 default.

#### Common errors — padh ke fix karo

| Error | Kyun | Fix |
|-------|------|-----|
| `ModuleNotFoundError: app` | Galat folder se run | `cd practice/` |
| `No module named 'fastapi'` | venv activate nahi / install nahi | `source .venv/bin/activate` + `pip install fastapi uvicorn` |
| `Address already in use` | Port 8000 busy | `--port 8001` ya purana process kill |
| `404 Not Found` on `/health` | Route register nahi / typo URL | `@app.get("/health")` check karo |

**A1 checkpoint 1:** `/health` curl se 200 + JSON.

---

### §3. Routes aur decorator — GET vs POST (→ A1 prep)

#### 3.1 Method + path

```python
@app.get("/items")       # GET  /items
@app.post("/chat")       # POST /chat
@app.delete("/items/5")  # DELETE /items/5
```

Express: `app.get`, `app.post` — same.

#### 3.2 Path parameter

URL mein variable:

```python
@app.get("/users/{user_id}")
async def get_user(user_id: int):
    return {"user_id": user_id}
```

`GET /users/42` → `user_id = 42` (FastAPI string se int convert karta hai).

Galat type: `/users/abc` → **422** validation error.

#### 3.3 Query parameter

`?` ke baad:

```python
@app.get("/search")
async def search(q: str, limit: int = 10):
    return {"q": q, "limit": limit}
```

`GET /search?q=hello&limit=5` → `q="hello"`, `limit=5`  
`GET /search?q=hello` → `limit=10` (default)

**Rule:** Jo path `{braces}` mein nahi, simple type hai → **query param**.

#### 3.4 Body — POST + JSON

GET mein body nahi hoti usually. POST mein JSON body:

```python
# Body ke liye Pydantic class use karo (§4)
@router.post("/chat")
async def chat(body: ChatRequest):
    ...
```

---

### §4. Pydantic — POST body validate (→ A1 part 2)

#### 4.1 Model file — `app/models.py`

```python
from pydantic import BaseModel, Field

class ChatRequest(BaseModel):
    message: str = Field(min_length=1, max_length=4000)

class ChatResponse(BaseModel):
    reply: str
    tokens_used: int
```

| Syntax | Matlab |
|--------|--------|
| `BaseModel` | Pydantic base — auto validation |
| `message: str` | Required string field |
| `Field(min_length=1)` | Khali string reject — 422 |
| `tokens_used: int` | Response mein integer required |

#### 4.2 Route — `app/routes/chat.py`

```python
from fastapi import APIRouter
from app.models import ChatRequest, ChatResponse

router = APIRouter(tags=["chat"])

@router.post("/chat", response_model=ChatResponse)
async def chat(body: ChatRequest) -> ChatResponse:
    return ChatResponse(
        reply=f"Echo: {body.message}",
        tokens_used=len(body.message),
    )
```

**Request flow:**

```
1. Client: POST /chat  Content-Type: application/json  {"message":"hi"}
2. FastAPI body parse → ChatRequest.model_validate(...)
3. Fail (empty message) → 422, handler tak NAHI pahunchega
4. Pass → chat() chalega, body.message typed str hai
5. Return ChatResponse → JSON {"reply":"Echo: hi","tokens_used":2}
```

**`response_model=ChatResponse`:** Response bhi validate — extra fields kat jaate hain.

#### 4.3 `main.py` mein router mount (abhi simple)

```python
from fastapi import FastAPI
from app.routes.chat import router as chat_router

app = FastAPI()
app.include_router(chat_router)
```

#### 4.4 curl se test — haath se karo

```bash
# ✅ Valid
curl -X POST http://localhost:8000/chat \
  -H "Content-Type: application/json" \
  -d '{"message":"hello"}'

# ❌ Invalid — empty message → 422
curl -X POST http://localhost:8000/chat \
  -H "Content-Type: application/json" \
  -d '{"message":""}'

# ❌ Invalid — missing field → 422
curl -X POST http://localhost:8000/chat \
  -H "Content-Type: application/json" \
  -d '{}'
```

422 response mein **detail** array hota hai — kaunsi field fail hui. `/docs` pe "Try it out" se bhi dekh sakte ho.

**A1 complete:** POST echo + 422 on bad input.

---

### §5. APIRouter — files alag karo (→ A2)

Ek file mein sab OK for learning. Production / gateway = **split**.

**`app/routes/health.py`:**

```python
from fastapi import APIRouter

router = APIRouter(tags=["health"])

@router.get("/health")
async def health():
    return {"status": "ok"}
```

**`app/main.py`:**

```python
from fastapi import FastAPI
from app.routes.health import router as health_router
from app.routes.chat import router as chat_router

app = FastAPI(title="Practice Gateway")
app.include_router(health_router)
app.include_router(chat_router)
# Version prefix: app.include_router(chat_router, prefix="/v1")
```

| Express | FastAPI |
|---------|---------|
| `const r = Router(); app.use(r)` | `router = APIRouter(); app.include_router(router)` |
| `routes/health.js` | `routes/health.py` |

`/docs` pe **dono** endpoints dikhne chahiye.

---

### §6. HTTPException — tum khud error bhejo (→ A2 bonus)

Pydantic auto 422 deta hai. **Business logic** errors tum throw karo:

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

| Python | Express |
|--------|---------|
| `raise HTTPException(404, detail="...")` | `res.status(404).json({detail:"..."})` |

Python mein **`raise`** = exception throw. FastAPI catch karke sahi HTTP response bana deta hai.

| Code | Kab |
|------|-----|
| 400 | Tumne reject kiya |
| 401 | Auth fail |
| 404 | Not found |
| 422 | Pydantic — body galat |
| 500 | Bug — prod mein log + generic message |

---

### §7. Depends() — auth ek jagah (→ A4)

#### 7.1 Problem

Har route pe API key check copy-paste — bura code.

#### 7.2 Header padhna

HTTP headers client bhejta hai:

```bash
curl -H "X-API-Key: dev-secret" http://localhost:8000/chat
```

FastAPI mein:

```python
from fastapi import Header

async def read_key(x_api_key: str = Header(..., alias="X-API-Key")):
    # Header(...) = required
    # alias = actual header name (hyphen wala)
    return x_api_key
```

#### 7.3 Dependency function — `app/deps.py`

```python
from fastapi import Header, HTTPException

DEV_SECRET = "dev-secret"

async def verify_api_key(x_api_key: str = Header(..., alias="X-API-Key")):
    if x_api_key != DEV_SECRET:
        raise HTTPException(status_code=401, detail="Invalid or missing API key")
    return x_api_key
```

#### 7.4 Route mein inject

```python
from fastapi import Depends
from app.deps import verify_api_key

@router.post("/chat")
async def chat(
    body: ChatRequest,
    api_key: str = Depends(verify_api_key),
):
    return ChatResponse(reply=body.message, tokens_used=1)
```

**`Depends(verify_api_key)`** = "handler se pehle yeh function chalao".

```
Request → verify_api_key() → (401 ya ok) → chat()
```

Express parallel: middleware sirf kuch routes pe — ya shared `requireAuth` function jo har handler call kare. FastAPI **`Depends`** = woh automatic.

#### 7.5 Test

```bash
# ❌ 401
curl -X POST http://localhost:8000/chat \
  -H "Content-Type: application/json" \
  -d '{"message":"hi"}'

# ✅ 200
curl -X POST http://localhost:8000/chat \
  -H "Content-Type: application/json" \
  -H "X-API-Key: dev-secret" \
  -d '{"message":"hi"}'
```

---

### §8. Middleware — har response pe header (→ A3)

**Depends** = specific routes. **Middleware** = **saari** requests jo app se guzrein.

**`app/middleware.py`:**

```python
import uuid
from starlette.middleware.base import BaseHTTPMiddleware

class RequestIDMiddleware(BaseHTTPMiddleware):
    async def dispatch(self, request, call_next):
        request_id = request.headers.get("X-Request-ID") or str(uuid.uuid4())
        response = await call_next(request)
        response.headers["X-Request-ID"] = request_id
        return response
```

| Line | Matlab |
|------|--------|
| `BaseHTTPMiddleware` | Starlette class — FastAPI isi pe built |
| `dispatch(self, request, call_next)` | Har request yahan aati hai |
| `await call_next(request)` | Andar bhejo — routes chalenge |
| `response.headers[...] = ...` | Response modify |

**Register — `main.py`:**

```python
from app.middleware import RequestIDMiddleware

app = FastAPI()
app.add_middleware(RequestIDMiddleware)
```

**Test:**

```bash
curl -i http://localhost:8000/health
# Response headers: X-Request-ID: <uuid>
```

---

### §9. SSE streaming — LLM preview (→ A5)

Normal: poora JSON ek shot mein. LLM: tokens **stream**.

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

| Keyword | Matlab |
|---------|--------|
| `yield` | Ek-ek piece bhejo — generator |
| `data: ...\n\n` | SSE format — do newline zaroori |
| `text/event-stream` | Content-Type |

```bash
curl -N http://localhost:8000/events
```

Module 01: OpenAI tokens isi pattern se aayenge.

---

### §10. Sab wire — final `main.py` checklist

Jab A1–A5 done:

```python
from fastapi import FastAPI
from app.middleware import RequestIDMiddleware
from app.routes.health import router as health_router
from app.routes.chat import router as chat_router
from app.routes.events import router as events_router

app = FastAPI(title="Practice Gateway")
app.add_middleware(RequestIDMiddleware)
app.include_router(health_router)
app.include_router(chat_router)
app.include_router(events_router)
```

**Order matter:** Middleware pehle register → phir routers.

---

## Practice

> [`practice/README.md`](practice/README.md) — har assignment ke pass criteria.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §2–§4 | `main.py`, `models.py`, `routes/chat.py` | POST echo + 422 on bad body |
| A2 | §5–§6 | `routes/` split | `/docs` pe health + chat |
| A3 | §8 | `middleware.py` | `curl -i` → `X-Request-ID` |
| A4 | §7 | `deps.py` | No key → 401 |
| A5 | §9 | `routes/events.py` | `curl -N` streams |
| A6 | §0–§1 | `NOTES.md` | Express vs FastAPI table 5 rows |

### Run (har session start)

```bash
cd modules/00c-fastapi/practice
source .venv/bin/activate
uvicorn app.main:app --reload --port 8000
```

---

## Active recall (NOTES mein khud likho)

1. `@app.get("/health")` — decorator actually kya karta hai?
2. Path vs query vs body param — FastAPI kaise decide karta hai?
3. 422 vs 401 — kaun automatic, kaun tum throw karte ho?
4. `uvicorn app.main:app` — dono `app` alag kyun hain?

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
