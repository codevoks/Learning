---
title: "M04 Async Tokio gRPC"
module: M04
phase: 1
type: practice
tags:
  - solana-curriculum
  - phase-1
  - m04
  - rust
  - async
aliases: [M04]
---

> [!nav] Navigation
> **[[modules/phase-1-rust/04-async-tokio-grpc/Hub|M04 Hub]]** · [[HOME|Home]] · [[learning-progress|Progress]] · [[modules/Index|All modules]] · _you are here: Practice_


> [!seealso] Visual learner
> **Sketch first** — practice answer se pehle diagram banao (paper/Canvas).  
> Guide: [[modules/_shared/VISUAL-LEARNING|Visual learning]] · Module diagram: [[modules/phase-1-rust/04-async-tokio-grpc/Hub|Visual map in Theory]]

# M04 — Practice

## P1 — async ordering
What prints first?
```rust
async fn a() { println!("a"); }
async fn b() { println!("b"); }
async fn main() {
    let h = tokio::spawn(a());
    b().await;
    h.await.unwrap();
}
```

## P2 — select!
Two futures: RPC poll vs shutdown signal — sketch `tokio::select!` pseudo.

## P3 — mpsc channel
Producer task sends slot numbers, consumer prints — backpressure if consumer slow?

## P4 — reqwest GET
`async fn get_slot(rpc_url: &str) -> Result<u64, ...>` — parse JSON field (manual, no solana crate).

## G04 — GATE
Tokio binary:
- spawn loop: HTTP GET every 5s
- `Result` error log, no panic
- `tokio::signal::ctrl_c()` shutdown
- Explain-back: kahan await, kahan spawn
