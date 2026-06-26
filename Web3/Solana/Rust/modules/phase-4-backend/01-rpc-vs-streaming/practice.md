---
title: "M12 RPC vs Streaming"
module: M12
phase: 4
type: practice
tags:
  - solana-curriculum
  - phase-4
  - m12
  - backend
  - rpc
aliases: [M12]
---

> [!nav] Navigation
> **[[modules/phase-4-backend/01-rpc-vs-streaming/Hub|M12 Hub]]** · [[HOME|Home]] · [[learning-progress|Progress]] · [[modules/Index|All modules]] · _you are here: Practice_


> [!seealso] Visual learner
> **Sketch first** — practice answer se pehle diagram banao (paper/Canvas).  
> Guide: [[modules/_shared/VISUAL-LEARNING|Visual learning]] · Module diagram: [[modules/phase-4-backend/01-rpc-vs-streaming/Hub|Visual map in Theory]]

# M12 — Practice

## P1 — Rate limit math
1M accounts, 100 RPS RPC — full refresh time order of magnitude?

## P2 — Head lag
Poll `getSlot` every 1s vs stream — missed slots scenario?

## P3 — GPA filter
`memcmp` offset filter — still why not scale at 1M accounts?

## G12 — GATE
Design doc (1 page):
- Indexer live path
- Backfill path  
- Tx submit path  
For your M11 program — which RPC, which stream, why.
