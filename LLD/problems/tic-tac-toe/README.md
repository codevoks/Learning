# Tic-Tac-Toe

## Problem
Design an NxN Tic-Tac-Toe with pluggable win-check and two players.

## Functional requirements
- NxN board (default 3)
- Two players alternate placing marks
- Detect win (row/col/diag), draw, invalid move
- Generalize win-check to NxN
- Easy to add a new player type/bot (bonus)

## Core entities (suggested)
`Game`, `Board`, `Player`, `WinStrategy`

## Patterns to consider
- Strategy (win-check)
- SOLID: OCP

## Your job
1. Clarify requirements with the coach.
2. Draw the class diagram (UML) in NOTES.
3. Complete the `TODO`s in `solution.py`.
4. Run `python solution.py` — the demo asserts must pass.
5. Defend extensibility: what changes if a new requirement arrives?

## Passing criteria
See the bottom of `solution.py`. Code must run, asserts pass, and adding a new variant should not require editing existing classes (OCP).
