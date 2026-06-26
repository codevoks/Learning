# Elevator System

## Problem
Design an elevator control system: requests, movement, and a pluggable dispatch/scheduling strategy.

## Functional requirements
- Elevator has states: IDLE, MOVING_UP, MOVING_DOWN
- External (floor+direction) and internal (target floor) requests
- A scheduling strategy decides next target (e.g. nearest, SCAN/LOOK)
- Support multiple elevators with a dispatcher choosing which lift serves a request
- Strategy swappable without editing Elevator

## Core entities (suggested)
`ElevatorSystem`, `Elevator`, `Request`, `Direction`, `SchedulingStrategy`

## Patterns to consider
- State (elevator)
- Strategy (scheduling)
- SOLID: OCP

## Your job
1. Clarify requirements with the coach.
2. Draw the class diagram (UML) in NOTES.
3. Complete the `TODO`s in `solution.py`.
4. Run `python solution.py` — the demo asserts must pass.
5. Defend extensibility: what changes if a new requirement arrives?

## Passing criteria
See the bottom of `solution.py`. Code must run, asserts pass, and adding a new variant should not require editing existing classes (OCP).
