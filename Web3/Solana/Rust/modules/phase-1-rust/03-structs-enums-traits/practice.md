---
title: "M03 Structs Enums Traits"
module: M03
phase: 1
type: practice
tags:
  - solana-curriculum
  - phase-1
  - m03
  - rust
  - types
aliases: [M03]
---

> [!nav] Navigation
> **[[modules/phase-1-rust/03-structs-enums-traits/Hub|M03 Hub]]** · [[HOME|Home]] · [[learning-progress|Progress]] · [[modules/Index|All modules]] · _you are here: Practice_


> [!seealso] Visual learner
> **Sketch first** — practice answer se pehle diagram banao (paper/Canvas).  
> Guide: [[modules/_shared/VISUAL-LEARNING|Visual learning]] · Module diagram: [[modules/phase-1-rust/03-structs-enums-traits/Hub|Visual map in Theory]]

# M03 — Practice

## P1 — Struct vs tuple struct
`struct Pubkey([u8; 32]);` vs `type Pubkey = [u8; 32];` — newtype pattern kyun?

## P2 — Enum exhaustiveness
`match ix { ... }` — missing variant = compile error. Why valuable?

## P3 — impl method
`impl Transfer { fn validate(&self) -> Result<(), ValidationError> }`

## P4 — Trait bound
```rust
fn log<T: std::fmt::Debug>(x: T) { ... }
```

## G03 — GATE
Design `enum StreamEvent { AccountUpdate {...}, SlotUpdate {...}, TxUpdate {...} }`  
+ `fn handle(ev: StreamEvent) -> Result<(), HandlerError>` with match dispatch.

No real Solana types — shapes only.
