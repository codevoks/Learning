---
title: "M09 Read Anchor"
module: M09
phase: 3
type: theory
tags:
  - solana-curriculum
  - phase-3
  - m09
  - anchor
  - read
aliases: [M09]
---

> [!nav] Navigation
> **[[modules/phase-3-anchor/01-read-anchor-programs/Hub|M09 Hub]]** · [[HOME|Home]] · [[learning-progress|Progress]] · [[modules/Index|All modules]] · _you are here: Theory_

# M09 — Read Real Anchor Programs

**Phase:** 3 | **Prereq:** P2 gate + Anchor toolchain | **Unlocks:** M10

## Objectives

- Anchor project layout (`programs/`, `Anchor.toml`, `lib.rs`)
- `declare_id!`, `#[program]`, `Context`, `Result`
- Read instruction handlers top-down
- Map Rust types to on-chain account layout

## Visual map

> [!abstract] Draw this first
> Folder tree + arrow flow client → program.

```mermaid
flowchart TB
  subgraph repo["Anchor project"]
    L[lib.rs declare_id]
    P[#[program] mod instructions]
    A[#[derive Accounts] per ix]
  end
  C[Client / IDL] -->|builds tx| P
  P --> A
  A -->|validates| ON[On-chain accounts]
```

```
programs/my_program/src/lib.rs
├── declare_id!(...)
├── #[program] mod { initialize, update, ... }
└── #[derive(Accounts)] structs below
```

**Sketch gate:** ek ix ka path client → handler → accounts trace.

## Theory

### Layout
```
programs/my_program/src/lib.rs  — entry
#[program] mod — instructions
#[derive(Accounts)] — per-ix account validation
```

### declare_id!
On-chain program address — must match `Anchor.toml` + deployed keypair.

### Context<T>
Accounts struct + bumps + remaining_accounts.

**Read strategy:** IDL or `#[program]` → pick one ix → trace `Accounts` struct → constraints.

## Gate

- [ ] G09: walkthrough one open-source program ix (agent picks: e.g. token-2022 sample or counter)
- [ ] R26 L2+

## Toolchain required

```bash
avm install latest && avm use latest
anchor --version  # 1.0+
solana --version  # upgrade to 3.x before deploy
```

## Weakness: preview `W-anchor-accounts`
