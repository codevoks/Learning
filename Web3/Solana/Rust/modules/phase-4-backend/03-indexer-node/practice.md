---
title: "M14 Indexer Node"
module: M14
phase: 4
type: practice
tags:
  - solana-curriculum
  - phase-4
  - m14
  - backend
  - indexer
aliases: [M14]
---

> [!nav] Navigation
> **[[modules/phase-4-backend/03-indexer-node/Hub|M14 Hub]]** · [[HOME|Home]] · [[learning-progress|Progress]] · [[modules/Index|All modules]] · _you are here: Practice_


> [!seealso] Visual learner
> **Sketch first** — practice answer se pehle diagram banao (paper/Canvas).  
> Guide: [[modules/_shared/VISUAL-LEARNING|Visual learning]] · Module diagram: [[modules/phase-4-backend/03-indexer-node/Hub|Visual map in Theory]]

# M14 — Practice

## P1 — Gap detect
Last slot 100, incoming 103 — immediate actions?

## P2 — Dedup
Same tx in replay and live — SQL constraint?

## P3 — Reorg
Slot 99 fork disappears — which rows update?

## P4 — Kafka key
Partition by `signature` vs `slot` — tradeoff?

## G14 — GATE (multi-session)
Checklist + demo: inject gap (pause consumer), run backfill, show row count consistent.
