---
title: Curriculum Index
aliases: [modules, curriculum, index]
tags: [solana-curriculum, meta, index]
---

> [!nav] Navigation
> [[HOME|Home]] · [[learning-progress|Progress]] · [[OBSIDIAN-SETUP|Obsidian setup]]

# All modules

17 modules · 4 phases · gate before skip

> [!tip] Kaise use karein
> Har module ka **Hub** kholo — wahan se theory, practice, assignments, agent sab linked hai.
> Cursor: `@modules/phase-X/.../agent.md`

---

## Phase 1 — Rust essentials

| ID | Title | Hub | Prereq | Sessions |
|----|-------|-----|--------|----------|
| M01 | Ownership & Borrowing | [[modules/phase-1-rust/01-ownership-borrowing/Hub\|Hub]] | — | 2–3 |
| M02 | Result & Option | [[modules/phase-1-rust/02-result-option-errors/Hub\|Hub]] | M01 | 2 |
| M03 | Structs, Enums & Traits | [[modules/phase-1-rust/03-structs-enums-traits/Hub\|Hub]] | M01, M02 | 2 |
| M04 | Async, Tokio & gRPC | [[modules/phase-1-rust/04-async-tokio-grpc/Hub\|Hub]] | M01–M03 | 3 |

**P1 gate:** M04 G04 — tokio HTTP client + ownership explain-back

---

## Phase 2 — Solana mental model

| ID | Title | Hub | Prereq | Sessions |
|----|-------|-----|--------|----------|
| M05 | Account model | [[modules/phase-2-solana/01-account-model/Hub\|Hub]] | P1 | 2 |
| M06 | Transactions & instructions | [[modules/phase-2-solana/02-transactions-instructions/Hub\|Hub]] | M05 | 2–3 |
| M07 | PDAs, rent & lamports | [[modules/phase-2-solana/03-pdas-rent-lamports/Hub\|Hub]] | M05, M06 | 2–3 |
| M08 | Commitment & compute | [[modules/phase-2-solana/04-commitment-compute/Hub\|Hub]] | M06 | 2 |

**P2 gate:** M08 G08 — tx/account diagram + commitment numbers

---

## Phase 3 — Anchor

| ID | Title | Hub | Prereq | Sessions |
|----|-------|-----|--------|----------|
| M09 | Read Anchor programs | [[modules/phase-3-anchor/01-read-anchor-programs/Hub\|Hub]] | P2 + toolchain | 2 |
| M10 | Constraints & IDL | [[modules/phase-3-anchor/02-accounts-constraints-idl/Hub\|Hub]] | M09 | 2–3 |
| M11 | Write small program | [[modules/phase-3-anchor/03-write-small-program/Hub\|Hub]] | M10 | 3–4 |

**P3 gate:** M11 G11 — devnet deploy + IDL + TS client

---

## Phase 4 — Backend

| ID | Title | Hub | Prereq | Sessions |
|----|-------|-----|--------|----------|
| M12 | RPC vs streaming | [[modules/phase-4-backend/01-rpc-vs-streaming/Hub\|Hub]] | P3 | 2 |
| M13 | Yellowstone gRPC | [[modules/phase-4-backend/02-yellowstone-grpc/Hub\|Hub]] | M12 | 3 |
| M14 | Indexer (Node) | [[modules/phase-4-backend/03-indexer-node/Hub\|Hub]] | M13 | 4–5 |
| M15 | Indexer (Rust) | [[modules/phase-4-backend/04-indexer-rust/Hub\|Hub]] | M14 | 4–5 |
| M16 | Tx lifecycle | [[modules/phase-4-backend/05-tx-lifecycle/Hub\|Hub]] | M08, M12 | 3–4 |
| M17 | Reconciliation | [[modules/phase-4-backend/06-reconciliation/Hub\|Hub]] | M14, M16 | 3–4 |

**P4 gate:** M17 G17 + G17b — full capstone

---

## Shared resources

| Note | Link |
|------|------|
| Learning system | [[modules/_shared/LEARNING-SYSTEM\|LEARNING-SYSTEM]] |
| Anti-overfitting | [[modules/_shared/ANTI-OVERFITTING\|ANTI-OVERFITTING]] |
| Agent protocol | [[modules/_shared/AGENT-PROTOCOL\|AGENT-PROTOCOL]] |
| Recall bank | [[modules/_shared/RECALL-BANK\|RECALL-BANK]] |

---

## Target projects

- **Indexer** — M12 → M15
- **Tx service** — M08, M16
- **Reconciliation** — M14, M17

[[HOME|← Back to Home]]
