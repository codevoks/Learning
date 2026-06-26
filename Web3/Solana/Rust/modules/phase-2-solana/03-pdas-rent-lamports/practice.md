---
title: "M07 PDAs Rent Lamports"
module: M07
phase: 2
type: practice
tags:
  - solana-curriculum
  - phase-2
  - m07
  - solana
  - pda
aliases: [M07]
---

> [!nav] Navigation
> **[[modules/phase-2-solana/03-pdas-rent-lamports/Hub|M07 Hub]]** · [[HOME|Home]] · [[learning-progress|Progress]] · [[modules/Index|All modules]] · _you are here: Practice_


> [!seealso] Visual learner
> **Sketch first** — practice answer se pehle diagram banao (paper/Canvas).  
> Guide: [[modules/_shared/VISUAL-LEARNING|Visual learning]] · Module diagram: [[modules/phase-2-solana/03-pdas-rent-lamports/Hub|Visual map in Theory]]

# M07 — Practice

## P1 — Why off-curve?
What breaks if PDA had a valid ed25519 secret key?

## P2 — Bump
Why try bumps 255..0? What happens if wrong bump in instruction?

## P3 — Rent calc order
Data size doubles — rent-exempt lamports go up or down? Rough ratio?

## P4 — PDA vs keypair
Escrow holding USDC — which and why?

## G07 — GATE
Program `Vault` seeds: `[b"vault", user_pubkey]`.  
Learner: steps to derive PDA, where bump stored, who signs transfer out.

Use `solana-keygen grind` not required — `@solana/web3.js` or `solana program derive` OK for verify.
