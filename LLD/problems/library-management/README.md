# Library Management System

## Problem
Design a library: catalog, members, borrow/return, fines, reservations.

## Functional requirements
- Books with multiple copies; members
- Borrow (limit per member), return, due dates
- Fine on late return (per-day)
- Reserve a book that is out; notify on availability (bonus)
- Search by title/author

## Core entities (suggested)
`Library`, `Book`, `BookCopy`, `Member`, `Loan`, `FineStrategy`

## Patterns to consider
- Strategy (fine)
- SOLID: SRP/OCP
- Observer (reservation notify)

## Your job
1. Clarify requirements with the coach.
2. Draw the class diagram (UML) in NOTES.
3. Complete the `TODO`s in `solution.py`.
4. Run `python solution.py` — the demo asserts must pass.
5. Defend extensibility: what changes if a new requirement arrives?

## Passing criteria
See the bottom of `solution.py`. Code must run, asserts pass, and adding a new variant should not require editing existing classes (OCP).
