# Chess

## Problem
Design a chess game: board, polymorphic pieces, move validation.

## Functional requirements
- 8x8 board, standard pieces
- Each piece validates its own moves (polymorphism)
- Turn alternation; capture; basic legality (path clear for sliders)
- Detect check (bonus); checkmate (bonus)
- Easy to add a fairy piece

## Core entities (suggested)
`Game`, `Board`, `Piece (King, Queen, ...)`, `Player`, `Move`

## Patterns to consider
- polymorphism
- Strategy (move rules)
- SOLID: OCP

## Your job
1. Clarify requirements with the coach.
2. Draw the class diagram (UML) in NOTES.
3. Complete the `TODO`s in `solution.cpp`.
4. Run `g++ -std=c++17 solution.cpp -o sol && ./sol` — the demo asserts must pass.
5. Defend extensibility: what changes if a new requirement arrives?

## Passing criteria
See the bottom of `solution.cpp`. Code must run, asserts pass, and adding a new variant should not require editing existing classes (OCP).
