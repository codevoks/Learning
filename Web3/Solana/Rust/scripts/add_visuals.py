#!/usr/bin/env python3
"""Inject Visual map sections into MODULE.md and visual-first blocks into practice.md."""

from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MODULES = ROOT / "modules"

# Visual map markdown per module (inserted after objectives, before Theory)
VISUALS: dict[str, str] = {
    "phase-1-rust/01-ownership-borrowing": """
## Visual map

> [!abstract] Draw this first
> Paper pe 3 boxes banao: **Owner** → **Stack** → **Heap**. Move = arrow transfer. Borrow = dotted line, owner box same.

### Ownership — move vs borrow

```mermaid
flowchart TB
  subgraph before["Before move"]
    O1[Owner: variable s]
    S1[Stack: ptr len cap]
    H1[Heap: hello bytes]
    O1 --> S1 --> H1
  end
  subgraph after["After take(s)"]
    O2[Owner: function param]
    S2[Stack: ptr len cap]
    H2[Heap: hello bytes]
    O2 --> S2 --> H2
    X[s INVALID — crossed out]
  end
  before -->|move| after
```

### Borrow rules (one screen)

```mermaid
flowchart LR
  subgraph rules["Borrow checker"]
    A["&T shared"] --- B["many OK if no &mut"]
    C["&mut T"] --- D["only ONE at a time"]
  end
```

| Visual | TS mental model | Rust reality |
|--------|-----------------|--------------|
| Solid arrow move | ref copy | ownership transfer |
| Dotted borrow | shared ref | read lease, owner stays |
| Red X on old name | still usable | compile error |

**Sketch gate:** G01 se pehle move/borrow diagram memory se redraw.
""",
    "phase-1-rust/02-result-option-errors": """
## Visual map

> [!abstract] Draw this first
> Do vertical paths: success green down, error red sideways.

```mermaid
flowchart TD
  Q[operation] --> O{Option}
  O -->|Some| V[value]
  O -->|None| N[handle missing]
  Q --> R{Result}
  R -->|Ok| OK[value]
  R -->|Err| E[propagate or match]
  E -->|?| UP[return early to caller]
```

| Type | Visual shape | Payment analog |
|------|--------------|----------------|
| Option | Y fork missing branch | optional fee_payer |
| Result | Y fork failure branch | PSP success/decline |
| ? | elevator up | bubble to controller |

**Sketch gate:** trace `fetch()?.parse()?` as arrows on paper.
""",
    "phase-1-rust/03-structs-enums-traits": """
## Visual map

> [!abstract] Draw this first
> Enum = tree root with branches. Struct = labeled box.

```mermaid
flowchart TD
  E[StreamEvent enum] --> A[AccountUpdate]
  E --> S[SlotUpdate]
  E --> T[TxUpdate]
  A --> A1[fields box]
  S --> S1[fields box]
  T --> T1[fields box]
  H[handle match] --> E
```

```mermaid
classDiagram
  class EventParser {
    <<trait>>
    +parse(raw) Output
  }
  class AccountParser
  class SlotParser
  EventParser <|.. AccountParser
  EventParser <|.. SlotParser
```

**Sketch gate:** apne G03 event enum ka tree draw karo.
""",
    "phase-1-rust/04-async-tokio-grpc": """
## Visual map

> [!abstract] Draw this first
> 1 thread, many tasks — waiting = dashed, running = solid.

```mermaid
flowchart TB
  RT[Tokio runtime thread pool]
  RT --> T1[task: HTTP poll]
  RT --> T2[task: stream consumer]
  RT --> T3[task: ctrl_c]
  CH[mpsc channel] --> T2
  T1 -.->|await| W1[RPC waiting]
  T2 -.->|await| W2[next message]
```

| Symbol | Meaning |
|--------|---------|
| Solid box | running task |
| Dashed | awaiting I/O |
| Queue | backpressure point |

**Sketch gate:** G04 architecture — 3 boxes + arrows before code.
""",
    "phase-2-solana/01-account-model": """
## Visual map

> [!abstract] Draw this first
> Har cheez ek box. Program box ke andar state NAHI — alag data boxes.

### Account = ek box

```
┌─────────────────────────────────────┐
│ Account pubkey (address)              │
├─────────────────────────────────────┤
│ lamports: 2_500_000_000               │
│ owner: Tokenkeg...  ←── program ID    │
│ executable: false                     │
│ data: [ 165 bytes layout... ]         │
└─────────────────────────────────────┘
```

```mermaid
flowchart LR
  W[Wallet account] -->|owns| TA[Token account]
  TP[Token Program] -->|owner of| TA
  TP -->|executes on| TA
```

❌ Program ke andar balance  
✅ Token account ke **data bytes** mein balance

**Sketch gate:** wallet → token account → mint triangle from memory.
""",
    "phase-2-solana/02-transactions-instructions": """
## Visual map

> [!abstract] Draw this first
> Tx = outer box. Andar instructions stack. Har instruction = program + account list.

```
Transaction
├── recent_blockhash: abc123...  (TTL ~60-90s)
├── fee_payer: SIGNER ✍
├── signatures: [ ... ]
└── instructions[]
    ├── [0] Transfer: System Program
    │       accounts: [from ✍ writable, to writable]
    └── [1] Memo: Memo Program
            accounts: [signer ✍]
```

```mermaid
flowchart TD
  TX[Transaction ATOMIC] --> I1[Instruction 1]
  TX --> I2[Instruction 2]
  TX --> I3[Instruction 3]
  I2 -->|fails| F[ALL rollback]
```

**Sketch gate:** G06 transfer — boxes + ✍/writable flags, no code.
""",
    "phase-2-solana/03-pdas-rent-lamports": """
## Visual map

> [!abstract] Draw this first
> Seeds go in blender → PDA address out. No private key.

```mermaid
flowchart LR
  S1[seed: vault] --> H[hash + bump try]
  S2[user pubkey] --> H
  S3[program id] --> H
  H --> PDA[PDA address off-curve]
  PDA --> ACC[account stores bump byte]
```

```
Rent-exempt deposit (locked SOL)
┌──────────────────┐
│ data_size bytes  │ ──► lamports ≥ rent_min(size)
│ 165 token acct   │     ~0.002 SOL order
└──────────────────┘
```

**Sketch gate:** seed list + arrow to PDA + where bump lives.
""",
    "phase-2-solana/04-commitment-compute": """
## Visual map

> [!abstract] Draw this first
> Horizontal timeline left=fast right=safe.

```mermaid
flowchart LR
  P[processed ~400ms] --> C[confirmed ~1-2s] --> F[finalized ~13s+]
  P -.->|reorg risk| P
  C -.->|lower risk| C
  F -.->|settlement| F
```

```
Compute budget per tx
┌─────────────────────────────┐
│ default ~200_000 CU         │
│ priority fee = micro-lamports/CU │
│ exceed CU → tx FAIL ✗        │
└─────────────────────────────┘
```

| Use case | Mark on timeline |
|----------|------------------|
| UI sparkle | processed |
| Indexer head | confirmed |
| Reconciliation | finalized |

**Sketch gate:** 5 scenarios ko timeline pe dot lagao.
""",
    "phase-3-anchor/01-read-anchor-programs": """
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
""",
    "phase-3-anchor/02-accounts-constraints-idl": """
## Visual map

> [!abstract] Draw this first
> Accounts = nodes. Constraints = edges with labels.

```mermaid
flowchart TD
  U[user SIGNER mut] -->|has_one| P[pda account]
  P -->|seeds + bump| PID[program id]
  PAY[payer SIGNER mut] -->|pays rent| P
```

```
IDL = OpenAPI for chain
┌─────────────┐     ┌──────────────┐
│ instructions│     │ accounts     │
│ types       │ ──► │ TypeScript   │
│ metadata    │     │ Rust client  │
└─────────────┘     └──────────────┘
```

**Sketch gate:** G10 accounts struct as labeled graph.
""",
    "phase-3-anchor/03-write-small-program": """
## Visual map

> [!abstract] Draw this first
> Local → test → devnet pipeline.

```mermaid
flowchart LR
  W[write Rust] --> T[anchor test local validator]
  T --> B[anchor build]
  B --> D[deploy devnet]
  D --> I[IDL generate]
  I --> TS[TS client call]
  TS --> IX[indexer target M14]
```

**Sketch gate:** apne program ke 2 instructions + accounts boxes.
""",
    "phase-4-backend/01-rpc-vs-streaming": """
## Visual map

> [!abstract] Draw this first
> Left = pull ladder. Right = push river.

```mermaid
flowchart TB
  subgraph poll["RPC poll — slow at scale"]
    APP1[indexer] -->|getSlot loop| RPC1[RPC node]
    APP1 -->|getProgramAccounts SCAN| RPC1
  end
  subgraph push["Stream — delta only"]
    G[Geyser / Yellowstone] -->|push updates| APP2[indexer]
  end
```

| Pattern | Visual | Scale |
|---------|--------|-------|
| GPA scan | magnifying glass on ALL rows | O(all accounts) ✗ |
| Stream filter | tap on pipe | O(changes) ✓ |

**Sketch gate:** G12 — two paths diagram for your program.
""",
    "phase-4-backend/02-yellowstone-grpc": """
## Visual map

> [!abstract] Draw this first
> Subscribe box with filters flowing out.

```mermaid
flowchart LR
  Y[Yellowstone gRPC] -->|SubscribeRequest| F[filters]
  F --> A[accounts by owner]
  F --> X[transactions by program]
  F --> SL[slots]
  F --> FS[from_slot replay]
  Y -->|protobuf stream| H[handler deserialize]
```

```
Disconnect recovery
  last_slot=105 → reconnect from_slot=106 → gap fill RPC
```

**Sketch gate:** filter diagram for your M11 program id.
""",
    "phase-4-backend/03-indexer-node": """
## Visual map

> [!abstract] Draw this first
> Pipeline left to right. Gap = broken chain link.

```mermaid
flowchart LR
  Y[Yellowstone] --> P[parse + IDL]
  P --> D[(Postgres)]
  P --> K[Kafka]
  K --> API[REST / WS]
  RPC[RPC backfill] -.->|gap 103 missing| P
```

```
Slot chain (gap-free)
  100 — 101 — [102 MISSING] — 103
              ↑
         backfill worker
```

**Sketch gate:** full pipeline + dedup key label.
""",
    "phase-4-backend/04-indexer-rust": """
## Visual map

> [!abstract] Draw this first
> Split: parser thin, handler fat.

```mermaid
flowchart LR
  IN[stream bytes] --> PR[Parser decode enum]
  PR --> HD[Handler business logic]
  HD --> DB[(sink)]
  subgraph parity["must match Node"]
    N[Node output] --- R[Rust output]
  end
```

**Sketch gate:** boxes + where backpressure goes.
""",
    "phase-4-backend/05-tx-lifecycle": """
## Visual map

> [!abstract] Draw this first
> State circles. Blockhash = timer on submitted.

```mermaid
stateDiagram-v2
  [*] --> queued
  queued --> signed
  signed --> submitted
  submitted --> confirmed
  confirmed --> finalized
  submitted --> failed: blockhash expired
  failed --> signed: rebuild + new blockhash
  submitted --> failed: on-chain error
```

```
Idempotency
  intent_id=pay_123 ──► sig_abc (landed?) ──► retry only if not landed
```

**Sketch gate:** state diagram + blockhash TTL clock.
""",
    "phase-4-backend/06-reconciliation": """
## Visual map

> [!abstract] Draw this first
> Two ledgers side by side. Drift = red highlight.

```mermaid
flowchart TB
  OC[on-chain finalized] --> R[recon worker]
  OFF[off-chain ledger] --> R
  R -->|match| OK[✓ settled]
  R -->|drift| AL[alert + incident row]
  AL --> RB[replay / manual]
```

```
Every 5 min cron
  watermark slot ──► compare balances ──► |diff| > ε ?
```

**Sketch gate:** G17b capstone — all 3 services in one diagram.
""",
}

PRACTICE_VISUAL_HEADER = """
> [!seealso] Visual learner
> **Sketch first** — practice answer se pehle diagram banao (paper/Canvas).  
> Guide: [[modules/_shared/VISUAL-LEARNING|Visual learning]] · Module diagram: [[{hub_link}|Visual map in Theory]]

"""


def strip_visual_map(body: str) -> str:
    return re.sub(r"\n## Visual map\n.*?(?=\n## (?:Theory|Objectives|Gate|P1 gate|Toolchain|Weakness))", "\n", body, flags=re.DOTALL)


def inject_visual_module(path: Path, folder: str) -> None:
    if folder not in VISUALS:
        return
    text = path.read_text(encoding="utf-8")
    body = text
    if "## Visual map" in body:
        body = strip_visual_map(body)
    visual = VISUALS[folder].strip()
    # Insert after Learning objectives / Objectives section
    patterns = [
        r"(## Learning objectives\n(?:.*?\n)+?)(?=\n## )",
        r"(## Objectives\n(?:.*?\n)+?)(?=\n## )",
    ]
    inserted = False
    for pat in patterns:
        m = re.search(pat, body, re.DOTALL)
        if m:
            body = body[: m.end()] + "\n" + visual + "\n" + body[m.end() :]
            inserted = True
            break
    if not inserted:
        # fallback: before ## Theory
        body = re.sub(r"\n(## Theory)", "\n" + visual + "\n\\1", body, count=1)
    path.write_text(body, encoding="utf-8")


def inject_practice_visual(path: Path, folder: str) -> None:
    text = path.read_text(encoding="utf-8")
    hub = f"modules/{folder}/Hub"
    header = PRACTICE_VISUAL_HEADER.format(hub_link=hub).strip() + "\n\n"
    text = re.sub(
        r"> \[!seealso\] Visual learner\n.*?\n\n",
        "",
        text,
        flags=re.DOTALL,
    )
    # After nav block
    m = re.search(r"(> \[!nav\] Navigation\n(?:> .*\n)+\n)", text)
    if m:
        insert_at = m.end()
        text = text[:insert_at] + "\n" + header + text[insert_at:]
    else:
        text = header + text
    path.write_text(text, encoding="utf-8")


def main() -> None:
    for folder, _ in VISUALS.items():
        base = MODULES / folder
        mod = base / "MODULE.md"
        prac = base / "practice.md"
        if mod.exists():
            inject_visual_module(mod, folder)
        if prac.exists():
            inject_practice_visual(prac, folder)
    print(f"Injected visuals into {len(VISUALS)} modules")


if __name__ == "__main__":
    main()
