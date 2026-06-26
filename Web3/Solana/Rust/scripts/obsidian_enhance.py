#!/usr/bin/env python3
"""Add Obsidian frontmatter + nav bars to curriculum markdown files."""

from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MODULES = ROOT / "modules"

MODULES_META = [
    ("M01", "phase-1-rust/01-ownership-borrowing", "Ownership & Borrowing", 1, ["rust", "ownership"]),
    ("M02", "phase-1-rust/02-result-option-errors", "Result & Option", 1, ["rust", "errors"]),
    ("M03", "phase-1-rust/03-structs-enums-traits", "Structs Enums Traits", 1, ["rust", "types"]),
    ("M04", "phase-1-rust/04-async-tokio-grpc", "Async Tokio gRPC", 1, ["rust", "async"]),
    ("M05", "phase-2-solana/01-account-model", "Account Model", 2, ["solana", "accounts"]),
    ("M06", "phase-2-solana/02-transactions-instructions", "Transactions", 2, ["solana", "transactions"]),
    ("M07", "phase-2-solana/03-pdas-rent-lamports", "PDAs Rent Lamports", 2, ["solana", "pda"]),
    ("M08", "phase-2-solana/04-commitment-compute", "Commitment Compute", 2, ["solana", "commitment"]),
    ("M09", "phase-3-anchor/01-read-anchor-programs", "Read Anchor", 3, ["anchor", "read"]),
    ("M10", "phase-3-anchor/02-accounts-constraints-idl", "Constraints IDL", 3, ["anchor", "idl"]),
    ("M11", "phase-3-anchor/03-write-small-program", "Write Program", 3, ["anchor", "deploy"]),
    ("M12", "phase-4-backend/01-rpc-vs-streaming", "RPC vs Streaming", 4, ["backend", "rpc"]),
    ("M13", "phase-4-backend/02-yellowstone-grpc", "Yellowstone gRPC", 4, ["backend", "yellowstone"]),
    ("M14", "phase-4-backend/03-indexer-node", "Indexer Node", 4, ["backend", "indexer"]),
    ("M15", "phase-4-backend/04-indexer-rust", "Indexer Rust", 4, ["backend", "rust"]),
    ("M16", "phase-4-backend/05-tx-lifecycle", "Tx Lifecycle", 4, ["backend", "transactions"]),
    ("M17", "phase-4-backend/06-reconciliation", "Reconciliation", 4, ["backend", "reconciliation"]),
]

PATH_TO_META = {m[1]: m for m in MODULES_META}


def has_frontmatter(text: str) -> bool:
    return text.startswith("---\n")


def strip_frontmatter(text: str) -> str:
    if not has_frontmatter(text):
        return text
    parts = text.split("---\n", 2)
    if len(parts) < 3:
        return text
    return parts[2].lstrip("\n")


def nav_bar(mid: str, folder: str, note_type: str) -> str:
    hub = f"modules/{folder}/Hub"
    labels = {
        "theory": "Theory",
        "practice": "Practice",
        "assignments": "Assignments",
        "agent": "Agent",
    }
    label = labels.get(note_type, note_type.title())
    return (
        f"> [!nav] Navigation\n"
        f"> **[[{hub}|{mid} Hub]]** · "
        f"[[HOME|Home]] · "
        f"[[learning-progress|Progress]] · "
        f"[[modules/Index|All modules]] · "
        f"_you are here: {label}_\n\n"
    )


def build_frontmatter(mid: str, title: str, phase: int, note_type: str, extra_tags: list[str]) -> str:
    tags = ["solana-curriculum", f"phase-{phase}", mid.lower(), *extra_tags]
    tag_yaml = "\n".join(f"  - {t}" for t in tags)
    return (
        f"---\n"
        f"title: \"{mid} {title}\"\n"
        f"module: {mid}\n"
        f"phase: {phase}\n"
        f"type: {note_type}\n"
        f"tags:\n{tag_yaml}\n"
        f"aliases: [{mid}]\n"
        f"---\n\n"
    )


def enhance_module_file(path: Path, note_type: str) -> None:
    rel = path.relative_to(MODULES).parent.as_posix()
    if rel not in PATH_TO_META:
        return
    mid, folder, title, phase, extra_tags = PATH_TO_META[rel]
    body = path.read_text(encoding="utf-8")
    body = strip_frontmatter(body)
    # Remove existing nav block if re-running
    body = re.sub(r"> \[!nav\] Navigation\n(?:> .*\n)+\n", "", body)
    content = (
        build_frontmatter(mid, title, phase, note_type, extra_tags)
        + nav_bar(mid, folder, note_type)
        + body
    )
    path.write_text(content, encoding="utf-8")


def enhance_shared(path: Path, title: str, note_type: str, tags: list[str]) -> None:
    body = path.read_text(encoding="utf-8")
    body = strip_frontmatter(body)
    body = re.sub(r"> \[!nav\] Navigation\n(?:> .*\n)+\n", "", body)
    tag_yaml = "\n".join(f"  - {t}" for t in tags)
    fm = (
        f"---\n"
        f"title: {title}\n"
        f"type: {note_type}\n"
        f"tags:\n{tag_yaml}\n"
        f"---\n\n"
    )
    nav = (
        f"> [!nav] Navigation\n"
        f"> [[HOME|Home]] · [[modules/Index|All modules]] · [[learning-progress|Progress]]\n\n"
    )
    path.write_text(fm + nav + body, encoding="utf-8")


def write_hub(mid: str, folder: str, title: str, phase: int, extra_tags: list[str], prev_hub: str | None, next_hub: str | None) -> None:
    base = f"modules/{folder}"
    tag_yaml = "\n".join(
        f"  - {t}" for t in ["solana-curriculum", f"phase-{phase}", mid.lower(), "hub", *extra_tags]
    )
    prev_link = f"[[{prev_hub}|← Previous]]" if prev_hub else "_start of path_"
    next_link = f"[[{next_hub}|Next →]]" if next_hub else "_capstone ahead_"

    content = f"""---
title: "{mid} Hub"
module: {mid}
phase: {phase}
type: hub
tags:
{tag_yaml}
aliases: [{mid}, "{mid} Hub"]
---

> [!nav] Navigation
> {prev_link} · **{mid}** · {next_link}
> [[HOME|Home]] · [[learning-progress|Progress]] · [[modules/Index|All modules]]

# {mid} — {title}

> [!tip] Is module mein kya hai
> Ek topic master karo → gate pass → next module. Cursor agent ke liye **Agent** note kholo.

## Module contents

| Step | Note | Kya karein |
|------|------|------------|
| 1 | [[{base}/MODULE\\|📖 Theory + Visual map]] | Diagram copy karo, phir ek theory section |
| 2 | [[{base}/practice\\|✏️ Practice]] | Socratic problems — hints se pehle khud try |
| 3 | [[{base}/assignments\\|📋 Assignments]] | Deeper work + spaced re-solve |
| 4 | [[{base}/agent\\|🤖 Agent]] | Cursor mein yeh file `@` ya paste karo |

## Session checklist

- [ ] **Redraw** — prior module diagram from memory
- [ ] [[modules/_shared/RECALL-BANK\\|Recall]] — due items quiz
- [ ] [[{base}/MODULE#Visual map\\|Visual map]] — copy + label khud se
- [ ] Theory section padho / agent se seekho
- [ ] Practice — **sketch first**, then answer
- [ ] Assignment progress
- [ ] Visual explain-back (ungli se diagram point karo)
- [ ] [[learning-progress\\|Progress]] + sketch photo link

## Visual map

Primary diagram: [[{base}/MODULE#Visual map\\|Theory → Visual map]]

Guide: [[modules/_shared/VISUAL-LEARNING\\|Visual learning]] · Sketches: `attachments/sketches/`

## Gate

Gate criteria detail: [[{base}/MODULE#Gate criteria\\|Theory → Gate section]]

## Also see

- [[modules/_shared/LEARNING-SYSTEM\\|Learning system]]
- [[modules/_shared/AGENT-PROTOCOL\\|Agent protocol]]
"""
    hub_path = MODULES / folder / "Hub.md"
    hub_path.write_text(content, encoding="utf-8")


def main() -> None:
    file_map = {
        "MODULE.md": "theory",
        "practice.md": "practice",
        "assignments.md": "assignments",
        "agent.md": "agent",
    }
    for rel, note_type in file_map.items():
        for path in MODULES.rglob(rel):
            if "_shared" in path.parts:
                continue
            enhance_module_file(path, note_type)

    shared = {
        "AGENT-PROTOCOL.md": ("Agent Protocol", "meta", ["meta", "agent"]),
        "LEARNING-SYSTEM.md": ("Learning System", "meta", ["meta", "learning"]),
        "RECALL-BANK.md": ("Recall Bank", "recall", ["meta", "recall"]),
    }
    for name, (title, ntype, tags) in shared.items():
        p = MODULES / "_shared" / name
        if p.exists():
            enhance_shared(p, title, ntype, ["solana-curriculum", *tags])

    hubs = []
    for i, (mid, folder, title, phase, extra) in enumerate(MODULES_META):
        prev_h = f"modules/{MODULES_META[i-1][1]}/Hub" if i > 0 else None
        next_h = f"modules/{MODULES_META[i+1][1]}/Hub" if i < len(MODULES_META) - 1 else None
        write_hub(mid, folder, title, phase, extra, prev_h, next_h)
        hubs.append((mid, folder, title))

    print(f"Enhanced module files + wrote {len(hubs)} Hub notes")


if __name__ == "__main__":
    main()
