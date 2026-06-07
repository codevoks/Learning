# Ethereum (EVM) — prerequisites and project order

Read root [`CONTEXT.md`](../CONTEXT.md) first. This file is the **EVM-specific** ladder: **easy → difficult projects** and what you must **understand and practice** before each.

---

## Prerequisite tiers (build these before “serious” projects)

Work **roughly top to bottom**. Higher tiers unlock harder projects.

### Tier 0 — Baseline (any Web3 work)

| Lens | What “good enough” looks like |
|------|-------------------------------|
| **Web3** | EOAs vs contracts; tx = nonce + gas + calldata; **events/logs** for off-chain indexing; EIP-1559 intuition (base vs priority fee). |
| **Engineering** | TypeScript comfort; typed boundaries; deterministic builds; formatter + linter on the repo. |
| **Production** | `.env.example`, never commit keys; **testnet vs mainnet** discipline; basic secrets hygiene. |
| **System design** | Stateless API mindset; pagination; API keys / rate limiting as a concept. |

**Practice (short):** Deploy a trivial contract on a testnet; emit events; fetch logs with a script.

---

### Tier 1 — Contracts as engineering artifacts

| Lens | What to internalize |
|------|---------------------|
| **Web3** | Solidity basics; **reentrancy** and checks-effects-interactions; `transfer`/`call` pitfalls; approvals (ERC20); proxy patterns **at headline level** only until you need them. |
| **Engineering** | **Foundry**: unit tests, fuzz, **invariants** (even on toy contracts); gas awareness as a habit—not premature golf. |
| **Production** | Upgrade story (if proxies): who can upgrade, migrations; **multicall/read** patterns for UX. |
| **System design** | Contract boundaries: oracle vs treasury vs pausable toggles—and **explicit trust assumptions**. |

**Indirect / may not ship in v1:** formal verification tooling, full audit playbook, mempool deep dives.

---

### Tier 2 — Indexing and “read-heavy” systems

| Lens | What to internalize |
|------|---------------------|
| **Web3** | **Event-driven truth**: what is canonical on-chain vs what your DB believes; **reorgs** (why indexers rewind or checkpoint); **decode** ABI logs reliably. |
| **Engineering** | Idempotent ingest; schema migrations; versioning; deterministic replays from a block height. |
| **Production** | Backfills; lag metrics; alerting on stall; graceful degradation read paths. |
| **System design** | **CQRS-ish split**: ingestion → normalized store → API; caching and consistency tradeoffs; rate limits per user/key. |

**Practice:** Pick **one** public protocol subgraph-style dataset or indexer tutorial, then pivot to **your own** thin indexer (Ponder / subsquid / The Graph Hosted—pick one stack and specialize).

---

### Tier 3 — Applications touching money movement

| Lens | What to internalize |
|------|---------------------|
| **Web3** | EIP-712 typed data; Permit/Permit2 patterns at user level; slippage; MEV/frontrunning **awareness** for UX469 patterns; bridging finality intuition. |
| **Engineering** | Simulation (`eth_call`); failure classification; retries that do **not** double-submit dangerously. |
| **Production** | RPC provider strategy (fallbacks, timeouts); mempool policy differences; telemetry on failed txs. |
| **System design** | Job queues for async confirmation; webhook/poll models; reconciliation jobs. |

---

### Tier 4 — Account abstraction (4337) and policy-heavy flows

| Lens | What to internalize |
|------|---------------------|
| **Web3** | **ERC-4337** vocabulary: UserOp, bundler, paymaster, entry point; deployment of counterfactual factories; sponsorship limits **as product + security**. |
| **Engineering** | Simulate UserOps; structured error surfaces; versioning entry point / contracts. |
| **Production** | Abuse prevention on sponsored gas; quotas; anomaly detection basics; KPIs on bundle inclusion. |
| **System design** | Policy engine separation (rules vs signing); KMS/HSM realities if you pretend “production”. |

---

### Tier 5 — Protocol primitives (AMM / vault / lending slice)

| Lens | What to internalize |
|------|---------------------|
| **Web3** | LP math at the level you implement; oracle manipulation class of issues; liquidation incentives; rounding direction. |
| **Engineering** | Invariant fuzz; differential testing hooks; staged rollout; bug bounty mindset in README. |
| **Production** | Pausing; guardians; treasury; multisig realities; operational runbooks—even for portfolio. |
| **System design** | Economic adversary stories; composability shocks; dependence on external oracles/DEX liquidity. |

---

## Projects — easy → difficult (recommended names / scope)

For each project, satisfy **all four lenses** in your README (assumptions, limits, failures).

### 1 — Indexed “risk” or activity API + dashboard (**easiest in this ladder**)

**Needs:** Tier 0–2 solid.

**Build:** Events from an existing lending/DEX/perp → normalized DB → API → small Next app (tables, alerts).

| Lens | Bar to clear |
|------|----------------|
| **Production** | Lag metric; reproducible indexer run; backoff on RPC errors; env docs |
| **Rigor** | Typed ABIs; property tests on **your decoding/parsing** if non-trivial |
| **System design** | Separation ingest/API; idempotent processors; pagination |
| **Web3** | Correct handling of **reorg** stance (document if you punt for hackathon—but know the gap) |

---

### 2 — Attestations / composable credential package (**medium**)

**Needs:** Tier 1–3.

**Build:** Ethereum Attestation Service (or minimal custom registry **only if** you document tradeoffs)—shared `packages/credentials`: verify attestations in app(s).

| Lens | Bar to clear |
|------|----------------|
| **Production** | Schema versioning; replay resistance story; revocation/expiration semantics |
| **Rigor** | Tests for verify boundaries; mocked chain state where useful |
| **System design** | Library API that **two demo apps** consume (proves reusability) |
| **Web3** | EIP-712 / attestation standards literacy; privacy tradeoffs called out |

---

### 3 — ERC-4337 smart account flow + capped paymaster (**medium–hard**)

**Needs:** Tier 2–4.

**Build:** Smart account creation, UserOps, sponsorship with **caps/allowlists**; monitor inclusion failures.

| Lens | Bar to clear |
|------|----------------|
| **Production** | Abuse limits; dashboards for sponsor spend; alerting |
| **Rigor** | Simulations; exhaustive failure cases documented |
| **System design** | Policy service vs chain contracts; separation of privileges |
| **Web3** | Clear trust model for upgradeability/session scopes if you add them |

---

### 4 — Minimal vault or single-pool AMM + invariant tests (**hardest**) 

**Needs:** Tier 1–5.

**Build:** Narrow scope (**smaller surface > bigger marketing**). Heavy Foundry invariants/fuzz + explicit threat model.

| Lens | Bar to clear |
|------|----------------|
| **Production** | Admin powers enumerated; pause/migration spelled out—even if mocked |
| **Rigor** | Invariants named in English ↔ code; failed attack stories in README |
| **System design** | Oracle/price feed assumptions; integrations that could compose badly |
| **Web3** | Economic attacks you considered (oracle, rounding, donation, skim) |

---

## “Learn but might not ship” — EVM-flavored

- Deep mempool / PBS / builder etiquette
- ZK rollup internals vs using L2 RPC
- Formal verification beyond properties you can fuzz
- Full smart contract audit methodology (still: read **trail of bits-style** summaries)

---

## Suggested sequencing (timeboxed)

1. Tier 0–1 until Foundry fuzz feels natural on a toy contract  
2. **Project 1** (index/API/UI) — your “systems backbone” demo  
3. Tier 3 depth while iterating Project 1 (better failure handling)  
4. **Project 2** or **Project 4** depending on taste: credentials **or** vault (vault if protocol jobs)  
5. **Project 3** if targeting wallets/account infra  
