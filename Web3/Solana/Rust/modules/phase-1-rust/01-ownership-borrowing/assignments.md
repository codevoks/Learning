---
title: "M01 Ownership & Borrowing"
module: M01
phase: 1
type: assignments
tags:
  - solana-curriculum
  - phase-1
  - m01
  - rust
  - ownership
aliases: [M01]
---

> [!nav] Navigation
> **[[modules/phase-1-rust/01-ownership-borrowing/Hub|M01 Hub]]** · [[HOME|Home]] · [[learning-progress|Progress]] · [[modules/Index|All modules]] · _you are here: Assignments_

# M01 — Assignments

## A1 — Mini ledger (pattern: explicit ownership transfer)

`cargo new m01-ledger`

- `struct Transfer { from: String, to: String, amount: u64 }`
- `fn apply(mut ledger: HashMap<String, u64>, t: Transfer) -> HashMap<String, u64>`
- **No clone** of `String` keys in `apply` — use references where read-only
- Main: create ledger, one transfer, print balances

**Diagnoses:** cloning keys habit from TS  
**Maps to:** tx intent ownership in tx service (later M16)

**Done when:** compiles + explain-back: kahan move, kahan borrow

---

## A2 — Borrow checker debugger

Agent gives 3 broken snippets (mix of P1, P2, P7 style).  
Learner: error message → one-line root cause → minimal fix.

No running required — reasoning sufficient.

---

## A3 — Cold re-solve (spacing)

Day +3: A1 from blank file, no notes. Target < 25 min.

**Recall link:** R01, R02
