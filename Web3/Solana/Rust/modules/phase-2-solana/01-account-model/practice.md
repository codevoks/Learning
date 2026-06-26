---
title: "M05 Account Model"
module: M05
phase: 2
type: practice
tags:
  - solana-curriculum
  - phase-2
  - m05
  - solana
  - accounts
aliases: [M05]
---

> [!nav] Navigation
> **[[modules/phase-2-solana/01-account-model/Hub|M05 Hub]]** · [[HOME|Home]] · [[learning-progress|Progress]] · [[modules/Index|All modules]] · _you are here: Practice_


> [!seealso] Visual learner
> **Sketch first** — practice answer se pehle diagram banao (paper/Canvas).  
> Guide: [[modules/_shared/VISUAL-LEARNING|Visual learning]] · Module diagram: [[modules/phase-2-solana/01-account-model/Hub|Visual map in Theory]]

# M05 — Practice

## P1 — Who owns the data?
Scenario: USDC balance change. Which account bytes mutate? Which program is owner?

## P2 — Lamports math
Account has 2_500_000 lamports. Send 1_000_000 lamports. New balance?

## P3 — Executable flag
`executable = true` account pe kya run hota hai vs false?

## P4 — Rent
Account below rent-exempt minimum — long term kya hota hai? (epoch garbage collect concept)

## G05 — GATE
Agent gives 3 devnet pubkeys (or descriptions):
1. System wallet
2. SPL token account  
3. Token program

Learner: table with lamports/data/owner/executable for each — CLI or explorer OK, **explain** why.
