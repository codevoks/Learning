# Logging Framework

## Problem
Design a logging framework using Chain of Responsibility for levels + pluggable appenders.

## Functional requirements
- Levels: DEBUG < INFO < WARN < ERROR
- A logger has a min level; messages below it are ignored
- Chain of handlers by level (CoR) OR level filter
- Appenders: console, file (pluggable, multiple)
- Adding a new appender/level needs no core change

## Core entities (suggested)
`Logger`, `LogLevel`, `Handler (CoR)`, `Appender`

## Patterns to consider
- Chain of Responsibility
- Strategy (appender)
- SOLID: OCP

## Your job
1. Clarify requirements with the coach.
2. Draw the class diagram (UML) in NOTES.
3. Complete the `TODO`s in `solution.py`.
4. Run `python solution.py` — the demo asserts must pass.
5. Defend extensibility: what changes if a new requirement arrives?

## Passing criteria
See the bottom of `solution.py`. Code must run, asserts pass, and adding a new variant should not require editing existing classes (OCP).
