---
title: "M03 Structs Enums Traits"
module: M03
phase: 1
type: assignments
tags:
  - solana-curriculum
  - phase-1
  - m03
  - rust
  - types
aliases: [M03]
---

> [!nav] Navigation
> **[[modules/phase-1-rust/03-structs-enums-traits/Hub|M03 Hub]]** · [[HOME|Home]] · [[learning-progress|Progress]] · [[modules/Index|All modules]] · _you are here: Assignments_

# M03 — Assignments

## A1 — Event parser trait
```rust
trait EventParser {
    type Output;
    fn parse(&self, raw: &[u8]) -> Result<Self::Output, ParseError>;
}
```
Two impls: `AccountParser`, `SlotParser` (dummy bytes).

## A2 — Explain-back
"Anchor IDL enum instruction mapping off-chain kaise hoti?" — preview M10, no IDL detail.

## A3 — Spaced +7d: G03 from scratch.
