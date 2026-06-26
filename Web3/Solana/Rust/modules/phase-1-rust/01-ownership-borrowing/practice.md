---
title: "M01 Ownership & Borrowing"
module: M01
phase: 1
type: practice
tags:
  - solana-curriculum
  - phase-1
  - m01
  - rust
  - ownership
aliases: [M01]
---

> [!nav] Navigation
> **[[modules/phase-1-rust/01-ownership-borrowing/Hub|M01 Hub]]** · [[HOME|Home]] · [[learning-progress|Progress]] · [[modules/Index|All modules]] · _you are here: Practice_


> [!seealso] Visual learner
> **Sketch first** — practice answer se pehle diagram banao (paper/Canvas).  
> Guide: [[modules/_shared/VISUAL-LEARNING|Visual learning]] · Module diagram: [[modules/phase-1-rust/01-ownership-borrowing/Hub|Visual map in Theory]]

# M01 — Practice problems

Agent: pehle attempt, phir hint ladder. Galat answer → weakness tag.

---

## P1 — Move diagnosis (W-ownership)

```rust
fn take(s: String) { println!("{}", s); }
let name = String::from("vansh");
take(name);
println!("{}", name);
```

**Teaches:** move invalidates source  
**Common wrong:** "println copies" — ask: `String` Copy hai?  
**Repair drill:** Same with `i32` — kyun compile hota hai?

---

## P2 — Mutable borrow (W-ownership)

```rust
let mut v = vec![1, 2, 3];
let r1 = &v;
v.push(4);
println!("{:?}", r1);
```

**Teaches:** `&mut` implicit on `push`  
**Common wrong:** "r1 read-only hai to OK" — reallocate?  
**Repair:** Draw timeline: borrows kab start/end

---

## P3 — Shared borrows (W-ownership)

Kitne `let r = &v` ek saath allowed jab `v` not mut?

**Teaches:** multiple `&T`  
**Gate sub-problem:** add one `&mut v` — kya break?

---

## P4 — Function signature choice

Indexer log function — high frequency, read-only:

```rust
fn log_event(??? event: Event)
```

`Event`, `&Event`, `&mut Event` — pick + why in throughput terms?

**Diagnoses:** unnecessary move of large struct

---

## P5 — Clone explicit cost

10_000 byte `Vec<u8>` — `process(data)` vs `process(&data)`.

Rough memory/copy cost compare karo.

---

## P6 — Lifetime smoke (W-lifetime)

```rust
fn first_word(s: &str) -> &str { ... }
```

Isme lifetime kahan tie hoti hai — caller ya callee?

---

## P7 — Dangling repair (W-lifetime) — GATE BUILDING BLOCK

```rust
fn broken() -> &str {
    let s = String::from("hi");
    &s
}
```

Kyun error? **Do not fix yet** — learner explanation first.  
Then: two fix strategies (return `String`, or input lifetime).

---

## G01 — GATE

Implement without clone in hot path:

```rust
struct RawAccount { data: Vec<u8> } // ~500 bytes avg

fn parse_owner(account: ???) -> [u8; 32] { ... }
fn handle_stream(accounts: Vec<RawAccount>) {
    for acc in accounts {
        let owner = parse_owner(???);
        // store owner bytes
    }
}
```

Fill `???` + explain-back move/borrow choices.
