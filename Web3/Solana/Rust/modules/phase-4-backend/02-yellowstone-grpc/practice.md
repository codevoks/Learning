---
title: "M13 Yellowstone gRPC"
module: M13
phase: 4
type: practice
tags:
  - solana-curriculum
  - phase-4
  - m13
  - backend
  - yellowstone
aliases: [M13]
---

> [!nav] Navigation
> **[[modules/phase-4-backend/02-yellowstone-grpc/Hub|M13 Hub]]** · [[HOME|Home]] · [[learning-progress|Progress]] · [[modules/Index|All modules]] · _you are here: Practice_


> [!seealso] Visual learner
> **Sketch first** — practice answer se pehle diagram banao (paper/Canvas).  
> Guide: [[modules/_shared/VISUAL-LEARNING|Visual learning]] · Module diagram: [[modules/phase-4-backend/02-yellowstone-grpc/Hub|Visual map in Theory]]

# M13 — Practice

## P1 — Filter design
Subscribe only your program's txs — filter fields?

## P2 — Commitment in stream
`confirmed` stream + reconciliation — risk?

## P3 — Deserialize
Tx update bytes → which parts for signature, slot, account keys?

## P4 — Disconnect
Network drop 30s — recovery steps ordered?

## G13 — GATE
Working subscriber (Node or Rust):
- filter: your program id
- prints: slot, signature, ix discriminator hex
- handles reconnect with `from_slot` from last seen
