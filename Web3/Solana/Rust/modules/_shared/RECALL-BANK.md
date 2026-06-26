---
title: Recall Bank
type: recall
tags:
  - solana-curriculum
  - meta
  - recall
---

> [!nav] Navigation
> [[HOME|Home]] · [[modules/Index|All modules]] · [[learning-progress|Progress]]

# Recall Bank — spaced repetition items

Agent: session start pe due items quiz karo. Pass → level +1 (see LEARNING-SYSTEM). Fail → level −2.

Format: `| ID | Module | Level | Next due | Prompt |`

---

## M01 — Ownership

| ID | Mod | Lvl | Due | Prompt |
|----|-----|-----|-----|--------|
| R01 | M01 | L0 | +1d | `fn log_name(s: String)` vs `fn log_name(s: &str)` — caller ke paas value ke baad kya bachta hai? |
| R02 | M01 | L0 | +1d | Stack pe 24 bytes struct copy hota hai; 10KB struct pass karte waqt kya hota hai aur kyun? |
| R03 | M01 | L0 | +1d | `&mut` rule in one sentence — kitne live mutable refs? |
| R04 | M01 | L0 | +1d | TS object reference vs Rust move — ek critical difference? |

## M02 — Errors

| ID | Mod | Lvl | Due | Prompt |
|----|-----|-----|-----|--------|
| R05 | M02 | L0 | — | `Option` kab, `Result` kab — payment API analogy se? |
| R06 | M02 | L0 | — | `?` operator caller pe kya force karta hai? |
| R07 | M02 | L0 | — | `unwrap()` production indexer mein kyun dangerous? |

## M03 — Types

| ID | Mod | Lvl | Due | Prompt |
|----|-----|-----|-----|--------|
| R08 | M03 | L0 | — | `enum` vs `struct` — Solana instruction dispatch se map karo |
| R09 | M03 | L0 | — | `trait` — backend mein interface jaisa; ek method example? |
| R10 | M03 | L0 | — | `#[derive(Debug, Clone)]` compile time pe kya karta hai? |

## M04 — Async

| ID | Mod | Lvl | Due | Prompt |
|----|-----|-----|-----|-----|
| R11 | M04 | L0 | — | `async fn` return kya karta hai actually — blocking thread pe kya nahi hota? |
| R12 | M04 | L0 | — | Yellowstone stream = Kafka consumer — backpressure ka risk? |
| R13 | M04 | L0 | — | `tokio::select!` kab use — indexer mein example? |

## M05 — Account model

| ID | Mod | Lvl | Due | Prompt |
|----|-----|-----|-----|--------|
| R14 | M05 | L0 | — | "Program state store karta hai" — kyun galat? |
| R15 | M05 | L0 | — | Account size 165 bytes — kis type ka typical size? (order of magnitude) |
| R16 | M05 | L0 | — | Rent-exempt minimum ~0.002 SOL — kis se decide hota hai? |

## M06 — Transactions

| ID | Mod | Lvl | Due | Prompt |
|----|-----|-----|-----|--------|
| R17 | M06 | L0 | — | 1 tx, 3 instructions — kitne signatures minimum? |
| R18 | M06 | L0 | — | Message header: num_required_signatures ka matlab? |
| R19 | M06 | L0 | — | Failed instruction — poori tx fail? (yes/no + exception) |

## M07 — PDAs

| ID | Mod | Lvl | Due | Prompt |
|----|-----|-----|-----|--------|
| R20 | M07 | L0 | — | PDA ka private key kyun nahi hota? |
| R21 | M07 | L0 | — | Seeds `[b"vault", owner.key()]` — bump kahan store hota hai? |
| R22 | M07 | L0 | — | 1 SOL = kitne lamports? |

## M08 — Commitment

| ID | Mod | Lvl | Due | Prompt |
|----|-----|-----|-----|--------|
| R23 | M08 | L0 | — | Processed ~400ms, finalized ~13s — reconciliation ke liye kaunsa? |
| R24 | M08 | L0 | — | 200k CU default — agar exceed? |
| R25 | M08 | L0 | — | Blockhash expiry ~60–90s — tx service pe impact? |

## M09–M11 — Anchor

| ID | Mod | Lvl | Due | Prompt |
|----|-----|-----|-----|--------|
| R26 | M09 | L0 | — | `declare_id!` kya hai? |
| R27 | M10 | L0 | — | `#[account(mut)]` vs `Signer` constraint? |
| R28 | M11 | L0 | — | IDL file kis ko serve karti hai off-chain? |

## M12–M17 — Backend

| ID | Mod | Lvl | Due | Prompt |
|----|-----|-----|-----|--------|
| R29 | M12 | L0 | — | `getProgramAccounts` 50k accounts — scaling problem in one line? |
| R30 | M13 | L0 | — | Yellowstone `from_slot` replay kyun? |
| R31 | M14 | L0 | — | Gap-free ingestion: slot 100, 101, 103 aaya — kya karna? |
| R32 | M15 | L0 | — | Carbon/Vixen handler vs parser split? |
| R33 | M16 | L0 | — | Idempotent retry: same intent, new blockhash — duplicate payment kaise roko? |
| R34 | M17 | L0 | — | Reorg at finalized — kitna rare, phir bhi kyun handle? |

---

_Update Due column when learner passes/fails. Agent owns this file._
