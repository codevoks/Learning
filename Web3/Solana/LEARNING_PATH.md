# Solana — prerequisites and project order

Read root [`CONTEXT.md`](../CONTEXT.md) first. **Solana is a different paradigm** than EVM (accounts + rent + **programs** owning state). Prerequisites are framed the same four lenses.

---

## Prerequisite tiers

### Tier 0 — Baseline

| Lens | What “good enough” looks like |
|------|-------------------------------|
| **Web3** | **Accounts** model (data vs exe); PDAs; **signers vs non-signers**; transactions + **recent blockhash**; basic fee/CU intuition. |
| **Engineering** | Rust toolchain stable; Anchor **or** raw programs—pick **one main path** early; reproducible builds. |
| **Production** | Keypair hygiene; clusters (`devnet`/`mainnet-beta`/`localnet`) discipline; `.env`/RPC keys not committed. |
| **System design** | Stateless clients polling RPC; backoff; idempotency for off-chain watchers. |

**Practice:** Deploy a noop program variation; derive a PDA; write a client that sends one instruction end-to-end.

---

### Tier 1 — Programs as engineering artifacts

| Lens | What to internalize |
|------|---------------------|
| **Web3** | **CPI** (cross-program invocation) rules; signer seeds; closing accounts (**rent refund** pitfalls); SPL Token basics if you touch assets. |
| **Engineering** | Program tests (`solana-program-test` / Anchor tests); discriminators; bounded account sizes; error codes that map to actionable client behavior. |
| **Production** | Upgrade authority reality; multisig posture for upgradeability; immutable programs as a deliberate choice in portfolio. |
| **System design** | Clear separation: state accounts vs config vs vault PDAs—draw on paper before coding. |

**Indirect:** Full runtime debugging on mainnet outages; SIMD proposals; QUIC transport details.

---

### Tier 2 — Indexing / read-heavy stacks

| Lens | What to internalize |
|------|---------------------|
| **Web3** | Parsing **transactions** vs account snapshots; SPL events where relevant; Geyser / Yellowstone awareness (you might only use polling first). |
| **Engineering** | Deterministic parsers; versioning when instruction layouts change (migrations discipline). |
| **Production** | RPC limits; pinning providers; staleness dashboards; checkpoints for replays. |
| **System design** | Separate ingest worker from HTTP API; backpressure concepts. |

**Practice:** Build a polling indexer for **one program** on devnet → expose JSON → tiny UI filter.

---

### Tier 3 — Applications with real user flows

| Lens | What to internalize |
|------|---------------------|
| **Web3** | Phantom / Backpack / Backpack-style adapter patterns at app level; **compute budget** and transaction size packing; retries without duplicate risk when combined with memo/de-dup patterns. |
| **Engineering** | Simulation-first (`simulateTransaction`) for UX hints; categorize errors (“blockhash/expired/account missing”). |
| **Production** | Commitment commitment levels (`confirmed`/`finalized`) and what you expose to users. |
| **System design** | Session architecture (wallet-connect patterns); queued submission on flaky mobile networks. |

---

### Tier 4 — Advanced program patterns (risk)

| Lens | What to internalize |
|------|---------------------|
| **Web3** | Lending/oracle patterns on Solana; **flash loan** realities in ecosystem; guarding against account substitution attacks; **Arithmetic** pitfalls (rounding, precision). |
| **Engineering** | Property tests where feasible; staged testing with **fuzzed account metas**. |
| **Production** | Authority minimization; time locks in theory (even if not in MVP). |
| **System design** | MEV/Jito awareness at headline level—may affect ordering and UX disclaimers |

---

### Tier 5 — Financial primitive slice

Same spirit as EVM Tier 5: smallest viable pool/vault/perp-lite with **readable invariants**, explicit oracle assumptions, README adversary stories.

---

## Projects — easy → difficult (Solana-shaped)

Naming mirrors EVM so you can compare difficulty shape across [`../ethereum/LEARNING_PATH.md`](../ethereum/LEARNING_PATH.md).

### 1 — Index + API + dashboard for one program (**easiest**)

**Needs:** Tier 0–2.

**Build:** Transaction watcher for a known program (dex pool event style or NFT marketplace style) → store → REST/GraphQL → UI.

---

### 2 — Credential / allowlist primitive (**medium**)

**Needs:** Tier 1–3.

Examples: gated mint or gated instruction based on Merkle proofs or SPL-gated mechanics; reusable client package.

Focus: explicit **privacy** limits (what is visible on-chain) and revocation story.

---

### 3 — “Abstracted fees” UX pattern (**medium–hard**)

Not 1:1 with ERC-4337, but parallel *product complexity*: delegated signing patterns, payer-of-fees workflows, multisig/session-style flows **only if you can articulate threat model**.

**Needs:** Tier 2–4.

---

### 4 — Minimal vault or pool primitive + tests (**hardest**) 

**Needs:** Tier 1–5.

Smaller surface beats “clone entire Drift.** Prove** rounding, donation, CPI reentrancy class issues considered (Solana semantics differ—study **explicit account validation** pitfalls).

---

## Learn but might not ship (Solana)

- Geyser deep plugins
- QUIC / scheduler internals  
- Full Jito auction theory  
- **Move** ecosystems (comparison only unless you pivot)

---

## If your primary is Ethereum

Use Solana docs here as **second track**: after one strong EVM project, optionally add **Project 1 (Solana)** only to prove **cross-paradigm** discipline—prefer depth on one chain over two shallow ladders.
