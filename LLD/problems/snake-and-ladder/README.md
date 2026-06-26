# Snake & Ladder

## Problem
Design a multiplayer Snake & Ladder game.

## Functional requirements
- Board of N cells with snakes (high->low) and ladders (low->high)
- Multiple players, dice roll
- Player moves; snake/ladder applied; exact/over-end rule defined
- First to reach last cell wins
- Configurable board + multiple dice (bonus)

## Core entities (suggested)
`Game`, `Board`, `Player`, `Dice`, `Jump (snake/ladder)`

## Patterns to consider
- composition
- SOLID: SRP

## Your job
1. Clarify requirements with the coach.
2. Draw the class diagram (UML) in NOTES.
3. Complete the `TODO`s in `solution.cpp`.
4. Run `g++ -std=c++17 solution.cpp -o sol && ./sol` — the demo asserts must pass.
5. Defend extensibility: what changes if a new requirement arrives?

## Passing criteria
See the bottom of `solution.cpp`. Code must run, asserts pass, and adding a new variant should not require editing existing classes (OCP).
