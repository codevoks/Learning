# Module 00e — Go Platform Backend

> **Padho**: Isi file mein **Theory** — bahar mat jao.  
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`  
> **Nav**: ← [00d ML Foundations](../00d-ml-ai-foundations/MODULE.md) · Next → [Module 01 LLM APIs](../01-llm-apis/MODULE.md)

> **Format note**: Tum **Go pehli baar** likh rahe ho — yeh revision notes nahi. §0 se syntax seekho, phir HTTP, phir middleware, phir proxy. Har section ke baad practice assignment.

> **Role**: **Go = platform** (auth, tenants, billing, public API). **Python = AI** (RAG, agents) — module 00c.

## At a glance

| | |
|---|---|
| Prerequisites | 00a (Docker), 00c (HTTP API mental model) |
| Duration | ~4–6 sessions |
| Project? | No (enables Projects phase 2 + Project C) |
| Exit test | Go syntax explain + middleware + proxy curl se demo |

## Visual map

```
Client
   │
   ▼
┌──────────────────────────────┐
│  GO PLATFORM (:8080)         │  ← tum yahan likhoge
│  auth │ tenant │ proxy       │
└──────────────┬───────────────┘
               │  internal HTTP only
               ▼
┌──────────────────────────────┐
│  PYTHON AI (:8001)           │  ← 00c FastAPI
│  RAG / agents                │
└──────────────────────────────┘
```

**Mental model**: Go = bank branch (customer face). Python = back-office specialist. Customer Python ko directly nahi milta.

---

## Read order (strict)

1. §0 Go syntax → **A1** start  
2. §1–§2 HTTP + Chi → **A1** complete  
3. §3 Middleware → **A2**  
4. §4 Context → **A2** complete  
5. §5 HTTP client proxy → **A3**  
6. §6–§7 architecture story → **A4** NOTES

---

## Theory

### §0. Go pehli baar — TypeScript dev ke liye (15 min)

Tum JS/TS jaante ho. Go alag syntax, same ideas.

**File = package.** Har Go file shuru hoti hai:

```go
package main  // main = executable program (npm start jaisa entry)
```

**Import:**

```go
import (
    "fmt"       // standard library — print
    "net/http"  // HTTP server/client
)
// Single: import "fmt"
```

**Function:**

```go
func add(a int, b int) int {
    return a + b
}

// Multiple return — Go ka signature feature
func divide(a, b float64) (float64, error) {
    if b == 0 {
        return 0, fmt.Errorf("divide by zero")
    }
    return a / b, nil
}
```

**Error handling — kabhi ignore mat karo:**

```go
result, err := divide(10, 0)
if err != nil {
    // handle — log, return 500, etc.
    return
}
// result use karo
```

TS mein `throw` common hai. Go mein **`error` return** — explicit.

**Variables:**

```go
name := "gateway"   // short declare + infer type
var port int = 8080 // explicit type
const DevSecret = "test"
```

**Struct = typed object:**

```go
type Tenant struct {
    ID   string
    Name string
}

t := Tenant{ID: "t1", Name: "Acme"}
fmt.Println(t.ID)
```

**Pointer (abhi itna kaafi):**  
`&x` = address of x. Functions ko mutate karwana ho toh pointer pass karte hain. Middleware mein zyada dikhega nahi — `context` use karenge.

**Run karo:**

```bash
go run .          # current folder ke saare .go files compile + run
go mod tidy       # dependencies sync (npm install jaisa)
```

**`go.mod`** = `package.json` — module name + dependencies:

```go
module github.com/you/platform

go 1.22

require github.com/go-chi/chi/v5 v5.0.12
```

---

### §1. HTTP server Go mein — `net/http` (→ A1)

Express mein: `app.get("/health", handler)`.  
Go stdlib mein: **`http.HandlerFunc`** — function jo request accept karta hai.

**Handler signature (yaad rakho):**

```go
func handler(w http.ResponseWriter, r *http.Request) {
    // w = response likho (headers + body)
    // r = request padho (method, URL, headers, body)
}
```

**Minimal server — har line:**

```go
package main

import (
    "log"
    "net/http"
)

func main() {
    // Route register: pattern + handler function
    http.HandleFunc("/health", func(w http.ResponseWriter, r *http.Request) {
        w.Header().Set("Content-Type", "application/json")
        w.WriteHeader(http.StatusOK)  // 200 — default bhi 200 hai
        w.Write([]byte(`{"ok":true}`))
    })

    log.Println("listening :8080")
    log.Fatal(http.ListenAndServe(":8080", nil))
    // nil = default mux (router). Production mein chi use karenge.
}
```

| Line | Matlab |
|------|--------|
| `http.HandleFunc("/health", fn)` | GET/POST sab methods — method check khud karo |
| `w.Header().Set(...)` | Response header |
| `w.WriteHeader(200)` | Status code |
| `w.Write([]byte(...))` | Response body — bytes chahiye, string nahi |
| `ListenAndServe(":8080", nil)` | Port 8080 pe suno — block karta hai |

**Test:**

```bash
curl http://localhost:8080/health
```

**Method check (sirf GET allow):**

```go
if r.Method != http.MethodGet {
    http.Error(w, "method not allowed", http.StatusMethodNotAllowed)
    return
}
```

---

### §2. Chi router — clean routes (→ A1)

Stdlib `HandleFunc` chhota demo ke liye OK. **chi** = Express jaisa router — methods, groups, middleware.

**Install** (already in `go.mod`):

```bash
go get github.com/go-chi/chi/v5
```

**`main.go` pattern:**

```go
package main

import (
    "log"
    "net/http"

    "github.com/go-chi/chi/v5"
)

func main() {
    r := chi.NewRouter()

    r.Get("/health", func(w http.ResponseWriter, r *http.Request) {
        w.Header().Set("Content-Type", "application/json")
        w.Write([]byte(`{"ok":true}`))
    })

    r.Post("/v1/query", func(w http.ResponseWriter, r *http.Request) {
        // A3 mein proxyToRAG yahan lagega
        http.Error(w, "not implemented", http.StatusNotImplemented)
    })

    log.Println("listening :8080")
    log.Fatal(http.ListenAndServe(":8080", r))
    //                                      ↑ router pass karo — nil nahi
}
```

| Chi | Express |
|-----|---------|
| `r.Get("/health", fn)` | `app.get("/health", fn)` |
| `r.Post("/v1/query", fn)` | `app.post("/v1/query", fn)` |
| `r.Route("/v1", func(r chi.Router) { ... })` | `router = express.Router(); app.use('/v1', router)` |
| `r.Use(middleware)` | `app.use(middleware)` |

**Route groups — auth sirf `/v1` pe:**

```go
r.Route("/v1", func(r chi.Router) {
    r.Use(tenantAuthMiddleware)  // sab /v1/* pe lagega
    r.Post("/query", proxyToRAG)
})
```

**Practice A1 pass:** `curl localhost:8080/health` → `{"ok":true}`

---

### §3. Middleware — `http.Handler` chain (→ A2)

**Idea:** Middleware = function jo **next handler** ko wrap kare.

Go type:

```go
type Handler interface {
    ServeHTTP(w http.ResponseWriter, r *http.Request)
}
```

Middleware signature:

```go
func myMiddleware(next http.Handler) http.Handler {
    return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
        // BEFORE request hits route
        next.ServeHTTP(w, r)  // andar bhejo
        // AFTER response (agar wrap kiya)
    })
}
```

**Request ID middleware — line by line** (`middleware.go`):

```go
import (
    "context"
    "net/http"
    "github.com/google/uuid"  // ya fmt.Sprintf + random — practice mein uuid package optional
)

func requestIDMiddleware(next http.Handler) http.Handler {
    return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
        requestID := r.Header.Get("X-Request-ID")
        if requestID == "" {
            requestID = uuid.New().String()
        }
        // response header set karo BEFORE next — ya after, dono OK
        w.Header().Set("X-Request-ID", requestID)
        next.ServeHTTP(w, r)
    })
}
```

**Register in main:**

```go
r := chi.NewRouter()
r.Use(requestIDMiddleware)
r.Use(tenantAuthMiddleware)  // order: upar wala pehle chalega (outer)
```

**Flow:**

```
Request
  → requestIDMiddleware (outer)
    → tenantAuthMiddleware
      → route handler
    ← back
  ← back
Response
```

Express: same onion model as `app.use()`.

---

### §4. Context — request ke saath tenant carry karna (→ A2)

**Problem:** Middleware ne API key se tenant nikala — route handler ko kaise do?

**Answer:** Go ka `context.Context` — request ke saath values attach.

**Step 1 — custom key type** (collision avoid):

```go
type contextKey string

const tenantIDKey contextKey = "tenant_id"
```

**Step 2 — auth middleware:**

```go
func tenantAuthMiddleware(next http.Handler) http.Handler {
    return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
        apiKey := r.Header.Get("X-API-Key")
        if apiKey == "" {
            http.Error(w, `{"error":"missing api key"}`, http.StatusUnauthorized)
            return
        }
        // practice: fake mapping — prod mein DB lookup
        tenantID := "tenant-" + apiKey

        // context mein store — NEW request with updated context
        ctx := context.WithValue(r.Context(), tenantIDKey, tenantID)
        r = r.WithContext(ctx)

        next.ServeHTTP(w, r)
    })
}
```

**Step 3 — handler mein read:**

```go
func tenantFromContext(ctx context.Context) string {
    v, ok := ctx.Value(tenantIDKey).(string)
    if !ok {
        return ""
    }
    return v
}

// proxy ya handler mein:
tenantID := tenantFromContext(r.Context())
```

**Test A2:**

```bash
# ❌
curl -i http://localhost:8080/v1/query
# 401

# ✅
curl -i -X POST http://localhost:8080/v1/query \
  -H "X-API-Key: test" \
  -H "Content-Type: application/json" \
  -d '{}'
```

---

### §5. HTTP client — Go se Python call (→ A3)

Platform ka kaam: client ka request lo → Python AI service ko forward karo → response wapas do.

**`proxy_rag.go` — step by step:**

```go
import (
    "io"
    "net/http"
    "os"
)

func ragBaseURL() string {
    if u := os.Getenv("RAG_SERVICE_URL"); u != "" {
        return u
    }
    return "http://localhost:8001"
}

func proxyToRAG(w http.ResponseWriter, r *http.Request) {
    tenantID := tenantFromContext(r.Context())
    if tenantID == "" {
        http.Error(w, "no tenant", http.StatusUnauthorized)
        return
    }

    // 1. Upstream request banao
    upstreamURL := ragBaseURL() + "/internal/query"
    req, err := http.NewRequestWithContext(
        r.Context(),
        http.MethodPost,
        upstreamURL,
        r.Body,  // client body forward — same JSON
    )
    if err != nil {
        http.Error(w, "bad request", http.StatusInternalServerError)
        return
    }

    // 2. Headers copy + tenant inject
    req.Header.Set("Content-Type", "application/json")
    req.Header.Set("X-Tenant-ID", tenantID)

    // 3. Call Python service
    client := &http.Client{Timeout: 30 * time.Second}
    resp, err := client.Do(req)
    if err != nil {
        http.Error(w, "upstream failed", http.StatusBadGateway)
        return
    }
    defer resp.Body.Close()

    // 4. Response client ko wapas
    w.WriteHeader(resp.StatusCode)
    io.Copy(w, resp.Body)
}
```

**Har step kyun:**

| Step | Kyun |
|------|------|
| `NewRequestWithContext` | Client disconnect → upstream cancel (timeout) |
| `r.Body` forward | Client ne jo JSON bheja wahi RAG ko |
| `X-Tenant-ID` | Python ko pata tenant kaun — multi-tenancy |
| `http.Client{Timeout: ...}` | Python hang → Go worker stuck forever na ho |
| `io.Copy(w, resp.Body)` | Stream large response without loading all in memory |

**Python stub (doosri terminal):**

```bash
python3 -c "
from http.server import BaseHTTPRequestHandler, HTTPServer
class H(BaseHTTPRequestHandler):
    def do_POST(self):
        print('Tenant:', self.headers.get('X-Tenant-ID'))
        self.send_response(200)
        self.end_headers()
        self.wfile.write(b'{\"ok\":true}')
HTTPServer(('',8001), H).serve_forever()
"
```

**Integration test:**

```bash
curl -X POST http://localhost:8080/v1/query \
  -H "X-API-Key: test" \
  -H "Content-Type: application/json" \
  -d '{"message":"hello"}'
# Python terminal: Tenant: tenant-test
```

**Wire in `main.go` (recommended pattern):**

```go
r.Use(requestIDMiddleware)

r.Route("/v1", func(r chi.Router) {
    r.Use(tenantAuthMiddleware)   // sirf /v1/* pe auth
    r.Post("/query", proxyToRAG)  // full path: POST /v1/query
})
```

Chi mein middleware + route alag files mein rakhna cleaner — practice stubs already split hain.

---

### §6. Goroutines — parallel calls (awareness)

Jab ek request pe **do Python calls** parallel chahiye (RAG + embed):

```go
type result struct {
    data string
    err  error
}

ch1 := make(chan result, 1)
go func() {
    data, err := callRAG(ctx, q)
    ch1 <- result{data, err}
}()

r1 := <-ch1  // wait
```

`go func()` = lightweight thread — Kafka consumer jaisa.  
**Rule:** shared maps without lock mat likho — channels ya mutex.

Abhi practice mein zarurat nahi — Project C gateway mein aayega.

---

### §7. Kyun Go platform, Python AI? (architecture)

| Layer | Language | Kyun |
|-------|----------|------|
| Platform | Go | Fast HTTP, low memory, simple deploy, billing/metering |
| AI | Python | LangGraph, ragas, OpenAI SDK |
| Frontend | Next.js | Tum jaante ho |

**Python public expose mat karo** — sirf Docker internal network. Go API key check karta hai; Python trust karta hai `X-Tenant-ID` (internal network pe).

**Metering (future — tumhara moat):**

```
Request done → usage event {tenant_id, units, idempotency_key}
           → outbox INSERT
           → worker → Stripe
```

Billing galat = company dead. Rootstock + Zapier clone story.

**Go mein mat likho:** LangGraph, RAG chunking, ragas — Python mein depth lo.

---

### §8. Repo layout (jab portfolio banoge)

```
portfolio/
├── platform/          # GO — cmd/api, internal/auth, metering, proxy
├── services/rag/      # PYTHON — Project A
├── services/agent/    # PYTHON — Project B
└── docker-compose.yml
```

Abhi sirf `modules/00e-go-platform/practice/` — same patterns, chhota scale.

---

## Practice

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §1–§2 | `main.go` | `curl /health` → 200 + JSON |
| A2 | §3–§4 | `middleware.go` + wire in main | No key → 401; `X-Request-ID` header |
| A3 | §5 | `proxy_rag.go` | Python stub prints `X-Tenant-ID` |
| A4 | §7 | `NOTES.md` | FastAPI vs Chi table 5 rows + polyglot diagram |

```bash
cd modules/00e-go-platform/practice
go mod tidy
go run .
```

> Stubs mein `TODO` search karo — Theory padh ke khud complete karo. Poora solution MODULE mein copy mat karo practice se pehle; stuck pe ek hint pucho chat mein.

---

## Active recall (NOTES)

1. Go mein error handle kaise karte ho — `try/catch` nahi, kya karte ho?
2. Middleware mein `next.ServeHTTP(w, r)` kyun call karte ho?
3. Python service internal kyun rakhte ho — 2 reasons?

---

## Progress checklist

- [ ] §0 syntax — chhota program `go run` se chala
- [ ] §1–§2 + A1 pass
- [ ] §3–§4 + A2 pass
- [ ] §5 + A3 pass (Python stub ke saath)
- [ ] A4 NOTES
- [ ] Redraw challenge

---

## Optional appendix

- [Go tour](https://go.dev/tour/) — extra exercises, MODULE primary hai
