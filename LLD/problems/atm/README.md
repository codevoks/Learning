# ATM

## Problem
Design an ATM using the State pattern.

## Functional requirements
- States: IDLE, CARD_INSERTED, AUTHENTICATED, DISPENSING
- Insert card, enter PIN (auth), select op (balance/withdraw)
- Withdraw: check balance + cash availability + dispense algorithm (note denominations)
- Eject card; invalid actions rejected per state
- Account balance updated atomically

## Core entities (suggested)
`ATM`, `State`, `Account`, `CashDispenser`

## Patterns to consider
- State pattern
- SOLID: SRP

## Your job
1. Clarify requirements with the coach.
2. Draw the class diagram (UML) in NOTES.
3. Complete the `TODO`s in `solution.cpp`.
4. Run `g++ -std=c++17 solution.cpp -o sol && ./sol` — the demo asserts must pass.
5. Defend extensibility: what changes if a new requirement arrives?

## Passing criteria
See the bottom of `solution.cpp`. Code must run, asserts pass, and adding a new variant should not require editing existing classes (OCP).
