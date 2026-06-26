# Module 10 — Deploy & Capstone 🔥

> **Agent**: `@Memory.md` + `@Prompt.md` + this + `@NOTES.md` · ← [09](../09-observability/MODULE.md)

## Visual map
```
cargo build --release           // optimized binary
multi-stage Docker: build (rust:slim) -> runtime (distroless/scratch + musl static)
graceful: axum::serve(...).with_graceful_shutdown(shutdown_signal())
perf: release profile, tokio worker threads, flamegraph/criterion
```
```mermaid
flowchart LR
    LB --> S[axum/hyper] --> Tok[Tokio worker threads] --> H[handlers]
```
**Mental model**: Release binary = blazing + tiny (musl static → scratch image, MBs, no GC). Capstone = perf-critical service (e.g. high-throughput rate-limiter/proxy ya embeddings-cache) with State+pool, auth, sqlx, tracing, graceful shutdown.

**Redraw**: serve → Tokio workers → handlers.

## Objectives
1. release build + tiny Docker
2. graceful shutdown
3. perf (workers, flamegraph)
4. Capstone service

## Topics
- `cargo build --release`; multi-stage Docker; musl static; distroless/scratch
- env config; `with_graceful_shutdown`
- perf: release profile, Tokio worker threads, flamegraph/criterion
- **Capstone**: high-perf service (rate-limiter/proxy or embeddings-cache) hitting all modules

## Assignments
| # | Task | Passing criteria |
|---|------|------------------|
| A1 | Release multi-stage Docker | Tiny image, runs |
| A2 | Capstone service all-modules | Defendable, measured perf |

## Active recall
1. release build kyun + musl static ka faayda?
2. graceful shutdown kaise?
3. Rust over Go — kab?

## Checklist
- [ ] Deploy from memory · [ ] A1,A2 · [ ] **Rust spaced-rep checklist** full pass · [ ] NOTES updated
