---
title: "M16 Tx Lifecycle"
module: M16
phase: 4
type: practice
tags:
  - solana-curriculum
  - phase-4
  - m16
  - backend
  - transactions
aliases: [M16]
---

> [!nav] Navigation
> **[[modules/phase-4-backend/05-tx-lifecycle/Hub|M16 Hub]]** · [[HOME|Home]] · [[learning-progress|Progress]] · [[modules/Index|All modules]] · _you are here: Practice_


> [!seealso] Visual learner
> **Sketch first** — practice answer se pehle diagram banao (paper/Canvas).  
> Guide: [[modules/_shared/VISUAL-LEARNING|Visual learning]] · Module diagram: [[modules/phase-4-backend/05-tx-lifecycle/Hub|Visual map in Theory]]

# M16 — Practice

## P1 — State machine
Draw states + transitions for tx service.

## P2 — Double submit
Two workers same `intent_id` — DB + on-chain check order?

## P3 — Simulate first
When skip simulate? (latency tradeoff)

## P4 — Finalized wait
User wants receipt — wait confirmed or finalized?

## G16 — GATE
Working service (Node or Rust):
- POST `/tx` with `intent_id`
- retries blockhash expiry once (test hook)
- GET `/tx/:intent_id` status
