# Module 00 — Go + Gin Foundations

> **Agent**: `@Memory.md` + `@Prompt.md` + this + `@NOTES.md` · Next → [01 Routing](../01-routing-handlers/MODULE.md)

## Visual map
```
net/http (stdlib)            Gin (built on net/http)
http.HandleFunc("/", h)  ->  r := gin.Default(); r.GET("/", h); r.Run()
type error interface { Error() string }   // errors are values
struct + method + small interface (implicit satisfy) = Go "OOP"
layout: cmd/server/main.go, internal/{handler,service,repo}
```
```mermaid
flowchart LR
    C[Client] --> NH[net/http Server] --> G[gin.Engine] --> H[handler]
```
**Mental model**: Gin = ergonomic layer over net/http. Go mein classes nahi — structs + methods + chhote interfaces (implicitly satisfied). Errors = return values, exceptions nahi.

**Redraw**: net/http → gin engine → handler.

## Objectives
1. Go basics (structs, interfaces, error, defer)
2. net/http server foundation
3. Gin setup
4. Project layout

## Topics
- `go mod`; types, structs, methods, **implicit interfaces**, slices/maps, `defer`
- `error` interface; `(val, err)` returns
- net/http: `HandlerFunc`, `ServeMux`; then `gin.Default()`
- Layout: `cmd/`, `internal/` (handler/service/repo)

## Assignments
| # | Task | Passing criteria |
|---|------|------------------|
| A1 | net/http hello server, then same in Gin | Both serve, `go run` works |
| A2 | struct + interface + method | Interface satisfied implicitly |

## Active recall
1. interfaces Go mein kaise satisfy hote (implicit)?
2. net/http vs Gin?
3. error value vs exception?

## Checklist
- [ ] net/http→gin from memory · [ ] A1,A2 · [ ] NOTES updated
