---
title: "M02 Result & Option"
module: M02
phase: 1
type: practice
tags:
  - solana-curriculum
  - phase-1
  - m02
  - rust
  - errors
aliases: [M02]
---

> [!nav] Navigation
> **[[modules/phase-1-rust/02-result-option-errors/Hub|M02 Hub]]** · [[HOME|Home]] · [[learning-progress|Progress]] · [[modules/Index|All modules]] · _you are here: Practice_


> [!seealso] Visual learner
> **Sketch first** — practice answer se pehle diagram banao (paper/Canvas).  
> Guide: [[modules/_shared/VISUAL-LEARNING|Visual learning]] · Module diagram: [[modules/phase-1-rust/02-result-option-errors/Hub|Visual map in Theory]]

# M02 — Practice

## P1 — Option handling
`fn find_user(id: u64) -> Option<String>` — caller must not panic on missing. Write caller with `match`.

**Wrong:** `unwrap()` "testing only" in prod path

## P2 — Result propagation
```rust
fn read_config() -> Result<String, std::io::Error> { ... }
fn load() -> Result<App, std::io::Error> {
    let raw = read_config().unwrap(); // fix this
}
```
Fix with `?` — what changes in signature?

## P3 — Chained failures
Parse slot from string → `u64`. Invalid input = `Err`. No panic.

## P4 — if let / while let
When `match` overkill — one case handle.

## G02 — GATE
```rust
fn fetch_and_parse(url: &str) -> Result<ParsedTx, FetchError> {
    let body = http_get(url).unwrap();
    let tx = parse(body).unwrap();
    Ok(tx)
}
```
Rewrite: `?`, define minimal `FetchError` enum (Network, Parse).
