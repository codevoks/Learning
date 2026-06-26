---
title: "M02 Result & Option"
module: M02
phase: 1
type: assignments
tags:
  - solana-curriculum
  - phase-1
  - m02
  - rust
  - errors
aliases: [M02]
---

> [!nav] Navigation
> **[[modules/phase-1-rust/02-result-option-errors/Hub|M02 Hub]]** · [[HOME|Home]] · [[learning-progress|Progress]] · [[modules/Index|All modules]] · _you are here: Assignments_

# M02 — Assignments

## A1 — RPC-shaped parser
`fn parse_slot(s: &str) -> Result<u64, ParseError>` — tests: `"12345"`, `"abc"`, `""`

## A2 — Error enum design
```rust
enum IndexerError { Db(...), Rpc(...), Deserialize(...) }
```
Map each to retry vs fail-fast (backend instinct — no deep teach).

## A3 — Spaced: Day +3 rewrite A1 without looking at old code.

**Maps to:** Yellowstone deserialize errors (M13)
