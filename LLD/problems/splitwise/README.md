# Splitwise

## Problem
Design an expense-sharing app: add expenses with split strategies, track balances, simplify debts.

## Functional requirements
- Users and groups
- Add expense paid by one, split among many
- Split strategies: EQUAL, EXACT, PERCENT (swappable)
- Maintain who-owes-whom balance
- Simplify debts: minimize number of transactions (bonus)

## Core entities (suggested)
`Splitwise`, `User`, `Expense`, `SplitStrategy`, `BalanceSheet`

## Patterns to consider
- Strategy (split)
- SOLID: OCP
- graph (debt simplify)

## Your job
1. Clarify requirements with the coach.
2. Draw the class diagram (UML) in NOTES.
3. Complete the `TODO`s in `solution.cpp`.
4. Run `g++ -std=c++17 solution.cpp -o sol && ./sol` — the demo asserts must pass.
5. Defend extensibility: what changes if a new requirement arrives?

## Passing criteria
See the bottom of `solution.cpp`. Code must run, asserts pass, and adding a new variant should not require editing existing classes (OCP).
