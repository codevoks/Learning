---
title: Learning Progress
aliases: [progress, tracker]
tags: [solana-curriculum, meta, progress]
---

> [!nav] Navigation
> [[HOME|Home]] · [[modules/Index|All modules]] · [[modules/phase-1-rust/01-ownership-borrowing/Hub|Active module hub]]

# Learning Progress

## Current position

| Field | Value |
|-------|-------|
| **Active module** | M01 — Ownership & Borrowing |
| **Phase** | P1 — Rust essentials |
| **Open hub** | [[modules/phase-1-rust/01-ownership-borrowing/Hub\|M01 Hub]] |
| **Agent** | [[modules/phase-1-rust/01-ownership-borrowing/agent\|M01 Agent]] |

## Phase gates

| Gate | Status | Evidence |
|------|--------|----------|
| P1 — Rust + tokio | NOT STARTED | [[modules/phase-1-rust/04-async-tokio-grpc/MODULE#Gate\|M04 G04]] |
| P2 — Solana model | LOCKED | [[modules/phase-2-solana/04-commitment-compute/MODULE#P2 gate\|M08 G08]] |
| P3 — Anchor program | LOCKED | [[modules/phase-3-anchor/03-write-small-program/MODULE#P3 gate\|M11 G11]] |
| P4 — Backend capstone | LOCKED | [[modules/phase-4-backend/06-reconciliation/MODULE#Gate (curriculum capstone)\|M17 G17]] |

## Module completion

| Module | Status | Hub | Gate |
|--------|--------|-----|------|
| M01 | IN PROGRESS | [[modules/phase-1-rust/01-ownership-borrowing/Hub\|Hub]] | G01 |
| M02 | LOCKED | [[modules/phase-1-rust/02-result-option-errors/Hub\|Hub]] | G02 |
| M03 | LOCKED | [[modules/phase-1-rust/03-structs-enums-traits/Hub\|Hub]] | G03 |
| M04 | LOCKED | [[modules/phase-1-rust/04-async-tokio-grpc/Hub\|Hub]] | G04 |
| M05 | LOCKED | [[modules/phase-2-solana/01-account-model/Hub\|Hub]] | G05 |
| M06 | LOCKED | [[modules/phase-2-solana/02-transactions-instructions/Hub\|Hub]] | G06 |
| M07 | LOCKED | [[modules/phase-2-solana/03-pdas-rent-lamports/Hub\|Hub]] | G07 |
| M08 | LOCKED | [[modules/phase-2-solana/04-commitment-compute/Hub\|Hub]] | G08 |
| M09 | LOCKED | [[modules/phase-3-anchor/01-read-anchor-programs/Hub\|Hub]] | G09 |
| M10 | LOCKED | [[modules/phase-3-anchor/02-accounts-constraints-idl/Hub\|Hub]] | G10 |
| M11 | LOCKED | [[modules/phase-3-anchor/03-write-small-program/Hub\|Hub]] | G11 |
| M12 | LOCKED | [[modules/phase-4-backend/01-rpc-vs-streaming/Hub\|Hub]] | G12 |
| M13 | LOCKED | [[modules/phase-4-backend/02-yellowstone-grpc/Hub\|Hub]] | G13 |
| M14 | LOCKED | [[modules/phase-4-backend/03-indexer-node/Hub\|Hub]] | G14 |
| M15 | LOCKED | [[modules/phase-4-backend/04-indexer-rust/Hub\|Hub]] | G15 |
| M16 | LOCKED | [[modules/phase-4-backend/05-tx-lifecycle/Hub\|Hub]] | G16 |
| M17 | LOCKED | [[modules/phase-4-backend/06-reconciliation/Hub\|Hub]] | G17 |

## Weakness buckets

| Bucket | Count | Remedial |
|--------|-------|----------|
| **W-overfitting** | 0 | [[modules/_shared/ANTI-OVERFITTING\|transfer drills]] |
| _signature_ | **novel case → blank** | principle-first; surface variation drills |
| W-visual-gap | 0 | [[modules/_shared/VISUAL-LEARNING\|redraw visual 3×]] |
| W-layout | 0 | ASCII numbered drill |
| W-spatial | 0 | box + arrow exercises |
| W-ownership | 0 | [[modules/phase-1-rust/01-ownership-borrowing/practice\|M01 practice]] |
| W-lifetime | 0 | M01 P7 |
| W-error-handling | 0 | [[modules/phase-1-rust/02-result-option-errors/Hub\|M02]] |
| W-types | 0 | [[modules/phase-1-rust/03-structs-enums-traits/Hub\|M03]] |
| W-async | 0 | [[modules/phase-1-rust/04-async-tokio-grpc/Hub\|M04]] |
| W-account-model | 0 | [[modules/phase-2-solana/01-account-model/Hub\|M05]] |
| W-tx-layout | 0 | [[modules/phase-2-solana/02-transactions-instructions/Hub\|M06]] |
| W-pda | 0 | [[modules/phase-2-solana/03-pdas-rent-lamports/Hub\|M07]] |
| W-commitment | 0 | [[modules/phase-2-solana/04-commitment-compute/Hub\|M08]] |
| W-anchor-accounts | 0 | [[modules/phase-3-anchor/02-accounts-constraints-idl/Hub\|M10]] |
| W-streaming | 0 | [[modules/phase-4-backend/01-rpc-vs-streaming/Hub\|M12]] |
| W-indexer | 0 | [[modules/phase-4-backend/03-indexer-node/Hub\|M14]] |
| W-tx-lifecycle | 0 | [[modules/phase-4-backend/05-tx-lifecycle/Hub\|M16]] |

## Pattern tags learned

_None yet — session ke baad yahan add karo._

## Spaced recall

Due items: [[modules/_shared/RECALL-BANK|Recall bank]]

| ID | Level | Next due | Last result |
|----|-------|----------|-------------|
| R01 | L0 | 2026-06-24 | — |
| R02 | L0 | 2026-06-24 | — |
| R03 | L0 | 2026-06-24 | — |
| R04 | L0 | 2026-06-24 | — |

## Visual sketchbook

> [!tip] Har gate pe ek sketch save karo
> Folder: `attachments/sketches/` · embed: `![[attachments/sketches/M01-ownership.png]]`

| Module | Sketch file | Redraw due |
|--------|-------------|------------|
| M01 | `M01-ownership.png` | — |
| _add rows as you pass gates_ | | |

Guide: [[modules/_shared/VISUAL-LEARNING|Visual learning]]

## Toolchain

| Tool | Required | Status |
|------|----------|--------|
| rustc | 1.85+ | OK — 1.88.0 |
| solana | 3.x | Behind — 2.2.21 |
| anchor | 1.0+ | Missing |
| node | M14+ | OK — v22.12.0 |

## Portfolio artifacts

| Artifact | Module | Path |
|----------|--------|------|
| Anchor program | M11 | — |
| Indexer v1 Node | M14 | — |
| Indexer Rust | M15 | — |
| Tx service | M16 | — |
| Reconciliation | M17 | — |

## Session log

### 2026-06-23 — Curriculum + Obsidian setup

- [[HOME|HOME]] dashboard + 17 module [[modules/phase-1-rust/01-ownership-borrowing/Hub|Hub]] notes
- Obsidian vault config: [[OBSIDIAN-SETUP|setup guide]]
- **Open:** M01 ownership baseline question

### Session template

```
### YYYY-MM-DD — M0X session N
- Recall: R__
- Theory: MODULE §__
- Practice: P__
- Weakness: W-__
- Assignment: A__
- Explain-back (1-5):
- Next:
```

## Current assignment

**M01-A1** — ownership baseline → then [[modules/phase-1-rust/01-ownership-borrowing/assignments|ledger assignment]]

**Pattern:** move vs borrow · **Recall:** R01 due +1d after first pass

[[HOME|← Home]]
