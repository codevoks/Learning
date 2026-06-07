# Web3 engineer track — master context

This folder is the **single place** you open when continuing this learning plan in another chat. Point the model at:

- This file (`CONTEXT.md`) for goals and priorities
- `ethereum/LEARNING_PATH.md` for EVM ordering, prerequisites, and project ladder
- `solana/LEARNING_PATH.md` for Solana ordering and prerequisites

## Goal

- **Outcome:** Roles that pay for **engineering** (rigor, systems, production), not **vibe-coded** demos.
- **Method:** Understand **prerequisites per tier**, practice them deliberately, **then** build 2–4 deep projects—not many shallow copies.

## How to use this repo

1. Read **Ethereum vs Solana** below and pick a **primary** ecosystem (recommended: start one, add the second later if needed).
2. Open your chosen `LEARNING_PATH.md` and work **top to bottom** through prerequisite tiers before starting the matching project.
3. For each project you attempt, check the four lenses: **production**, **engineering rigor**, **system design**, **Web3 domain**.

## Easy → difficult (project ladder, both ecosystems)

Same *shape* of difficulty; details differ by chain (see per-chain files).

| Order | Difficulty | Project shape | Why this order |
|------|------------|---------------|----------------|
| 1 | Easier | **Read-only index + API + small UI** on an existing protocol | Systems thinking, events/logs, correctness, APIs—without inventing a new protocol. |
| 2 | Medium | **Identity / attestations / permissions** composable as a package | Standards, verification flows, reusable library mindset. |
| 3 | Medium–hard | **Account abstraction (EVM) / fee abstraction patterns (Solana)** | Policy, limits, ops, security boundaries—closer to product engineering. |
| 4 | Hardest | **Custom financial primitive** (pool, vault, lending slice) + **tests + threat model** | Protocol design, invariants, adversarial thinking—closest to protocol/security hiring bars. |

**Note:** “Easier” here does not mean trivial—it means **lower attack-surface responsibility** than writing money-moving logic from scratch.

## Solana vs Ethereum — what to pursue

**Short answer:** For **maximum $100k-style role surface area in 2025–2026** (protocol teams, wallets, L2/infra, DeFi backends), **start with Ethereum (EVM)** as your **primary**: larger job market, more shared tooling (Foundry, subgraphs/Ponder, AA), and most “protocol + backend + security” job posts assume EVM literacy.

**When Solana first makes sense:**

- You already target **Solana-native teams** (consumer apps, trading infra, MEV-adjacent, high-TPS products).
- You love the **account / rent / CU** model and are willing to invest in **Rust + program security** as your main bet.

**Pragmatic path (strong signal):**

1. **Primary: EVM** — Solidity/Foundry, events, indexing, one serious read path + one serious write path (contract + tests).
2. **Secondary (optional):** Solana later as a **second folder of depth** (one program + CPI + realistic tests), not ten half-finished chains.

Neither stack rewards “tutorial tourism.” Both reward **ownership, testing, observability, and clear docs**.

## Stuff you learn that might never “directly” appear

Worth studying at a **survey** level so interviews and production work do not blindside you—you may not use each item in every project:

| Area | Examples |
|------|----------|
| Math / cryptography | ECDSA intuition, hashing, Merkle proofs, basic zk vocabulary (you may not implement circuits). |
| Distributed systems | Consistency vs finality, reorgs, idempotency, retries, backoff, dead-letter patterns. |
| Data stores | Postgres, Redis, OLAP basics; caching and stale reads in indexers. |
| Ops | CI, secrets, alerting, dashboards, structured logging—it matters more than flashy UI. |
| Legal / product | Risks around custody, geography, securities framing (awareness, not legal advice). |

## Vibe code vs engineer (quick checklist)

| Vibe | Engineer |
|------|----------|
| Copy contract, ship video | Property/invariant tests, documented assumptions, deployment notes |
| “It works on my machine” | Reproducible build, env docs, CI |
| One happy path | Failure modes, reorgs, partial indexing, rate limits |
| Anonymous “DeFi clone” | README with threat model, trust boundaries, admin powers |

## Next file to open

- EVM track: [`ethereum/LEARNING_PATH.md`](ethereum/LEARNING_PATH.md)
- Solana track: [`solana/LEARNING_PATH.md`](solana/LEARNING_PATH.md)
