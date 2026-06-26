# Vending Machine

## Problem
Design a vending machine using the State pattern: select item, insert money, dispense, refund.

## Functional requirements
- States: IDLE, ITEM_SELECTED, HAS_MONEY, DISPENSING
- Insert coins; if enough, dispense and return change; else wait
- Cancel returns inserted money
- Inventory tracked per slot; out-of-stock handled
- Invalid actions for a state are rejected (e.g. dispense before payment)

## Core entities (suggested)
`VendingMachine`, `State (IdleState, ...)`, `Item`, `Inventory`

## Patterns to consider
- State pattern
- SOLID: SRP per state

## Your job
1. Clarify requirements with the coach.
2. Draw the class diagram (UML) in NOTES.
3. Complete the `TODO`s in `solution.py`.
4. Run `python solution.py` — the demo asserts must pass.
5. Defend extensibility: what changes if a new requirement arrives?

## Passing criteria
See the bottom of `solution.py`. Code must run, asserts pass, and adding a new variant should not require editing existing classes (OCP).
