# Module 00e — Go Platform Backend

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [00d ML Foundations](../00d-ml-ai-foundations/MODULE.md) · Next → [Module 01 LLM APIs](../01-llm-apis/MODULE.md)

> **Format**: Textbook — §0 Go syntax pehle (`:=`, `err`, pointers), prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`

> **Role**: **Go = platform** (auth, tenants, billing, public API). **Python = AI** (RAG, agents, module 00c).
> ⭐ **EDGE — skip if pure-Python AI roles** — do if platform/polyglot/backend roles target karo. Priority: [PRIORITY.md](../../PRIORITY.md).

## At a glance

| | |
|---|---|
| Prerequisites | 00a (Docker), 00c (HTTP API mental model) |
| Duration | ~4–6 sessions |
| Project? | No (par Projects phase 2 + Project C enable karta hai) |
| Exit test | Go syntax samjhao + middleware + proxy curl se demo |

## Yeh module kis baare mein hai

Tumhare portfolio mein do tarah ka backend hoga. **Python** AI ka kaam karega (RAG, agents) — wo tumne 00c mein dekha. **Go** "platform" layer hoga — wo public-facing API jo auth, tenants, billing, aur rate-limiting sambhalta hai, aur phir andar Python service ko call karta hai. Yeh module Go ka wo zaroori hissa sikhata hai.

Mental model bank jaisा socho: **Go = bank ki branch** (customer-facing, ID check karta hai), **Python = back-office specialist** (asli AI kaam, customer se directly nahi milta). Customer Python ko kabhi directly nahi pahunchta — hamesha Go ke through.

```
Client → GO PLATFORM (:8080)  auth│tenant│proxy  → (internal HTTP) → PYTHON AI (:8001)  RAG/agents
```

Go ki grammar TS se alag hai — `:=`, multiple return values, aur explicit error checks naye honge. §0 mein har symbol zero se dunga; uske bina practice files padhoge to har line pe atकोge.

---

## Read order (strict)

1. §0 Go syntax → **A1** start
2. §1–§2 HTTP + Chi → **A1** complete
3. §3 Middleware → **A2**
4. §4 Context → **A2** complete
5. §5 HTTP client proxy → **A3**
6. §6–§8 architecture story → **A4** NOTES

---

## Theory

### §0. Go syntax — pehli baar, har symbol (45 min + terminal try)

Tum TypeScript jaante ho. Go bhi curly-brace language hai, par kuch cheezein nayi hain. Ek-ek karke karo, jaldbaazi mat.

**File ka shape.** Har `.go` file ek `package` se shuru hoti hai; chal-ne wale program ke liye `package main` + `func main()`:

```go
package main
import "fmt"

func main() {
    fmt.Println("hello")
}
```

Run: `cd practice && go run .`

**`:=` — sabse common confusion.** Yeh "naya variable banao aur value do" hai, jisme type right side se infer hota hai. `name := "gateway"` ek string banata hai, `port := 8080` ek int. Pehle se bane variable ko sirf badalna ho to `=` (bina colon). Teen rules gaanth lo: (1) `:=` sirf function ke andar chalta hai, package level pe `var`/`const`; (2) left side pe kam se kam ek variable naya hona chahiye; (3) **declared-but-unused = compile error** — Go bekaar variable allow nahi karta (yeh shuru mein chidhaata hai par baad mein accha lagta hai).

```go
name := "gateway"   // TS ka let name = "gateway"
name = "other"      // reassign — naya nahi, isliye = (no colon)
```

**Multiple return — Go ki signature feature.** Yeh tum har jagah dekhoge. HTTP/DB calls do values lautate hain: actual result aur ek `error`:

```go
resp, err := client.Do(req)
if err != nil {
    return   // handle karo
}
// resp use karo
```

Yahi Go ka error-handling tareeka hai — TS ki tarah `throw`/`try-catch` nahi, balki **explicit `if err != nil` check** har risky call ke baad. Pehle yeh verbose lagega, par yeh tumhe har failure ke baare mein *sochne* pe majboor karta hai — production code mein yeh achhi baat hai. Value ignore karni ho to `_` (blank identifier): `_, err := foo()`.

**Types jo dikhenge.** `string`, `int`, `bool` to clear hain. Naya hai `[]byte` (byte slice) — HTTP bodies bytes mein likhi jaati hain, isliye `w.Write([]byte(...))` dikhega. Aur `nil` Go ka `null` hai (no error, empty pointer). Backtick `` `{"ok":true}` `` raw string hai — escape nahi karni padti, JSON literals ke liye perfect.

**Pointer `*` — abhi bas itna.** Practice mein `func handler(w http.ResponseWriter, r *http.Request)` dikhega. `*http.Request` ka matlab "Request struct ka pointer (reference)" — bada struct copy karne ke bajaye share karte hain. Abhi `*` ko "reference jaisा" socho; itna kaafi hai ki middleware request ko modify kar sake (headers, context).

**Struct — typed object.** TS ke type/object jaisa, ek dhyaan dene layak twist ke saath: field ka naam **capital se shuru** ho to wo exported hai (dusre packages use kar sakte), lowercase ho to package-private:

```go
type Tenant struct {
    ID   string   // capital = exported
    name string   // lowercase = private
}
t := Tenant{ID: "t1", name: "Acme"}
```

**Baaki chhoti cheezein.** Anonymous function `func(w, r) { ... }` Express ke `(req, res) => {}` jaisा inline callback hai. Imports ek block mein, aur unused import bhi compile error (`go mod tidy` se sync). Dependencies ke liye: `go mod tidy` ≈ `npm install`, `go get pkg@ver` ≈ `npm install pkg`, `go run .` compile + run, `go build -o api` binary.

> **Ruko, socho:** Go mein agar tumne `name := "a"` likha aur niche `name` ko kabhi use nahi kiya, to kya hoga? (Jawab: compile error — "declared but not used". Go forces tumhe ya use karo ya hatao.)

#### §0 checkpoint (NOTES mein, bina dekhe)

1. `:=` vs `=` vs `var` ka farak?
2. `resp, err := ...` do values kyun?
3. `if err != nil` har jagah kyun?
4. `[]byte` HTTP body mein kyun?

**Pass?** Ab §1. Atke to chat mein symbol paste karo, theory dubara mat likhwao.

---

### §1. HTTP server Go mein — `net/http`

Express mein `app.get("/health", handler)`. Go stdlib mein handler ek function hota hai jiska signature fixed hai — `w` se response likho, `r` se request padho:

```go
func handler(w http.ResponseWriter, r *http.Request) {
    // w = response (headers + body) likho
    // r = request (method, URL, headers, body) padho
}
```

Minimal server:

```go
package main
import ("log"; "net/http")

func main() {
    http.HandleFunc("/health", func(w http.ResponseWriter, r *http.Request) {
        w.Header().Set("Content-Type", "application/json")
        w.WriteHeader(http.StatusOK)        // 200
        w.Write([]byte(`{"ok":true}`))      // body — bytes, string nahi
    })
    log.Println("listening :8080")
    log.Fatal(http.ListenAndServe(":8080", nil))   // nil = default router
}
```

Do baatein jo Express se alag hain. Ek, response body **bytes** mein likhni padti hai (`[]byte(...)`), seedha string nahi. Do, `http.HandleFunc` saare HTTP methods pe match karta hai — agar sirf GET chahiye to khud check karo: `if r.Method != http.MethodGet { http.Error(w, "...", http.StatusMethodNotAllowed); return }`. (Yeh manual kaam §2 mein chi router solve kar dega.)

---

### §2. Chi router — clean routes

Stdlib `HandleFunc` chhote demo ke liye theek hai par method-matching khud karni padti hai. **chi** ek Express-jaisा router hai — per-method routes, groups, middleware sab deta hai:

```go
import ("log"; "net/http"; "github.com/go-chi/chi/v5")

func main() {
    r := chi.NewRouter()
    r.Get("/health", func(w http.ResponseWriter, r *http.Request) {
        w.Header().Set("Content-Type", "application/json")
        w.Write([]byte(`{"ok":true}`))
    })
    r.Post("/v1/query", func(w http.ResponseWriter, r *http.Request) {
        http.Error(w, "not implemented", http.StatusNotImplemented)   // A3 mein bharega
    })
    log.Fatal(http.ListenAndServe(":8080", r))   // nil ki jagah router pass karo
}
```

Mapping seedha hai: `r.Get(...)` ≈ `app.get(...)`, `r.Use(mw)` ≈ `app.use(mw)`, aur `r.Route("/v1", ...)` ≈ Express ka nested router. Yeh `Route` grouping ek important kaam karta hai — auth sirf `/v1/*` pe lagana:

```go
r.Route("/v1", func(r chi.Router) {
    r.Use(tenantAuthMiddleware)   // sirf /v1/* pe
    r.Post("/query", proxyToRAG)
})
```

**A1 pass:** `curl localhost:8080/health` → `{"ok":true}`.

---

### §3. Middleware — `http.Handler` chain

Go mein middleware ek function hai jo **agle handler ko wrap** karta hai. Signature pehli baar ajeeb lagta hai par pattern yaad ho jaaye to clear hai: ek `http.Handler` lo (`next`), aur ek naya handler return karo jo `next` ko beech mein call kare:

```go
func myMiddleware(next http.Handler) http.Handler {
    return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
        // BEFORE — request route tak pahunchne se pehle
        next.ServeHTTP(w, r)   // andar bhejo
        // AFTER — response wapas aane ke baad
    })
}
```

`next.ServeHTTP(w, r)` hi wo line hai jo request ko chain mein aage bhejti hai — agar tum ise call na karo, request wahin ruk jaayegi (jaise auth fail pe). Ek request-ID middleware:

```go
func requestIDMiddleware(next http.Handler) http.Handler {
    return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
        requestID := r.Header.Get("X-Request-ID")
        if requestID == "" {
            requestID = uuid.New().String()
        }
        w.Header().Set("X-Request-ID", requestID)
        next.ServeHTTP(w, r)
    })
}
```

Register `r.Use(requestIDMiddleware)` se. Order matter karta hai — jo `Use` pehle, wo "outer" (pehle chalता hai). Yeh Express ka same onion model hai: outer middleware → inner middleware → route → wapas inner → wapas outer.

---

### §4. Context — request ke saath tenant carry karna

Yahan ek asli problem hai: auth middleware ne API key se tenant nikal liya — ab wo tenant route handler tak kaise pahunche? Go ka jawab `context.Context` hai, jo request ke saath values attach karta hai.

Pehle ek custom key type banao (string keys collision kar sakti hain, isliye apna type):

```go
type contextKey string
const tenantIDKey contextKey = "tenant_id"
```

Auth middleware mein API key check karke tenant ko context mein daalo:

```go
func tenantAuthMiddleware(next http.Handler) http.Handler {
    return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
        apiKey := r.Header.Get("X-API-Key")
        if apiKey == "" {
            http.Error(w, `{"error":"missing api key"}`, http.StatusUnauthorized)
            return   // next call NAHI — request yahin ruk gayi
        }
        tenantID := "tenant-" + apiKey   // practice: fake; prod mein DB lookup
        ctx := context.WithValue(r.Context(), tenantIDKey, tenantID)
        next.ServeHTTP(w, r.WithContext(ctx))   // naya request, updated context
    })
}
```

Handler mein wapas padhna (`v, ok := ...(string)` Go ka type-assertion idiom hai — `ok` batata hai value mili ya nahi):

```go
func tenantFromContext(ctx context.Context) string {
    v, ok := ctx.Value(tenantIDKey).(string)
    if !ok { return "" }
    return v
}
```

Gaur karo jab API key missing thi, hum ne `http.Error(...)` ke baad `return` kiya aur `next.ServeHTTP` call **nahi** kiya — yahi request ko 401 pe rok deta hai.

> **Ruko, socho:** Agar auth middleware mein `http.Error(...)` ke baad `return` likhna bhool jao, to kya hoga? (Jawab: request fail hone ke *baad bhi* `next.ServeHTTP` chal jaayega — handler bina valid tenant ke chalega, security hole. `return` zaroori hai.)

---

### §5. HTTP client — Go se Python call (proxy)

Platform ka asli kaam: client ka request lo → Python AI service ko forward karo → response wapas do. Yeh poora proxy handler:

```go
func proxyToRAG(w http.ResponseWriter, r *http.Request) {
    tenantID := tenantFromContext(r.Context())
    if tenantID == "" {
        http.Error(w, "no tenant", http.StatusUnauthorized); return
    }
    // 1. Upstream request banao — client ka body aage forward
    req, err := http.NewRequestWithContext(r.Context(), http.MethodPost,
        ragBaseURL()+"/internal/query", r.Body)
    if err != nil {
        http.Error(w, "bad request", http.StatusInternalServerError); return
    }
    // 2. Headers + tenant inject
    req.Header.Set("Content-Type", "application/json")
    req.Header.Set("X-Tenant-ID", tenantID)
    // 3. Python service ko call (timeout ke saath)
    client := &http.Client{Timeout: 30 * time.Second}
    resp, err := client.Do(req)
    if err != nil {
        http.Error(w, "upstream failed", http.StatusBadGateway); return
    }
    defer resp.Body.Close()
    // 4. Response client ko stream karo
    w.WriteHeader(resp.StatusCode)
    io.Copy(w, resp.Body)
}
```

Har step ka kyun samajhna zaroori hai. **`NewRequestWithContext`** client ke context ko upstream se jodता hai — client disconnect kare to upstream call bhi cancel ho jaaye (waste na ho). **`r.Body` forward** karte hain taaki client ne jo JSON bheja wahi Python ko jaaye. **`X-Tenant-ID`** se Python ko pata chalta hai request kis tenant ki hai (multi-tenancy) — Python is header pe bharosa karta hai kyunki wo internal network pe hai. **`Timeout: 30s`** critical hai — bina iske agar Python hang ho jaaye to Go ka worker hamesha ke liye atak jaayega. Aur **`io.Copy`** response ko stream karta hai bina poori cheez memory mein load kiye (bade responses ke liye zaroori). `defer resp.Body.Close()` ka `defer` matlab "yeh function khatam hone pe chalao" — resource leak rokта hai.

Test ke liye doosri terminal mein ek chhota Python stub chalao (practice README mein hai), phir:

```bash
curl -X POST http://localhost:8080/v1/query -H "X-API-Key: test" \
  -H "Content-Type: application/json" -d '{"message":"hello"}'
# Python terminal pe: Tenant: tenant-test
```

`main.go` mein wire karo: `requestIDMiddleware` global, aur `tenantAuthMiddleware` + `proxyToRAG` `/v1` group ke andar.

---

### §6. Goroutines — parallel calls (awareness)  ⏭️ SKIP-able

> ⏭️ **Skip OK** — explicitly awareness; Project C gateway mein aayega. Abhi zaroori nahi.

Kabhi ek request pe do Python calls parallel chahiye (RAG + embed). Go isके liye **goroutines** deta hai — `go func() { ... }` ek lightweight thread shuru karta hai (Kafka consumer jaisा), aur results **channels** se wapas aate hain:

```go
ch := make(chan result, 1)
go func() {
    data, err := callRAG(ctx, q)
    ch <- result{data, err}
}()
r1 := <-ch   // wait for result
```

Ek rule abhi yaad rakho: shared maps ko bina lock ke alag goroutines se mat likho — channels ya mutex use karo, warna race condition. Practice mein abhi zarurat nahi; Project C gateway mein aayega.

---

### §7. Kyun Go platform aur Python AI?

Yeh split jaanboojh ke hai. **Go** platform ke liye perfect hai — fast HTTP, kam memory, simple single-binary deploy, aur billing/metering jaisा precise kaam. **Python** AI ke liye — LangGraph, ragas, OpenAI SDK sab Python mein hain. **Next.js** frontend (tum jaante ho).

Ek security rule: **Python ko kabhi public expose mat karo** — wo sirf Docker internal network pe rehta hai. Go API key check karta hai (zero-trust, customer-facing); Python `X-Tenant-ID` pe bharosa karta hai kyunki usе sirf Go (internal network se) hi call kar sakta hai. Aur metering tumhara real moat hai — har request ke baad ek usage event banाo (outbox pattern se Stripe tak). Galat billing = company dead; yeh tumhari Rootstock/Zapier-clone waali muscle hai.

---

### §8. Repo layout (portfolio ke liye)

```
portfolio/
├── platform/        # GO — cmd/api, internal/auth, metering, proxy
├── services/rag/    # PYTHON — Project A
├── services/agent/  # PYTHON — Project B
└── docker-compose.yml
```

Abhi sirf `modules/00e-go-platform/practice/` — wahi patterns, chhota scale.

---

## Practice

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §1–§2 | `main.go` | `curl /health` → 200 + JSON |
| A2 | §3–§4 | `middleware.go` + wire | No key → 401; `X-Request-ID` header |
| A3 | §5 | `proxy_rag.go` | Python stub prints `X-Tenant-ID` |
| A4 | §7 | `NOTES.md` | FastAPI vs Chi table 5 rows + polyglot diagram |

```bash
cd modules/00e-go-platform/practice
go mod tidy
go run .
```

> Stubs mein `TODO` search karo — theory padhke khud bharo. Solution copy mat karo; stuck pe ek hint chat mein maango.

---

## Active recall (NOTES)

1. Go mein error handle kaise — `try/catch` nahi to kya?
2. Middleware mein `next.ServeHTTP(w, r)` kyun call karte ho, aur na karein to?
3. Python service ko internal kyun rakhte ho — 2 reasons?

---

## Progress checklist

- [ ] §0 syntax — chhota program `go run` se chala
- [ ] §1–§2 + A1 pass
- [ ] §3–§4 + A2 pass
- [ ] §5 + A3 pass
- [ ] A4 NOTES
- [ ] Redraw challenge

---

## Optional appendix

- [Go tour](https://go.dev/tour/) — MODULE primary hai
