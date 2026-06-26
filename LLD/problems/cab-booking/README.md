# Cab Booking (Uber / Ola)

## Problem
Design a ride-hailing service: rider requests, driver matching, pricing (surge), trip lifecycle.

## Functional requirements
- Riders request a ride from a location
- Match nearest AVAILABLE driver (pluggable matching strategy)
- Fare via pluggable pricing strategy (normal/surge)
- Trip states: REQUESTED -> ASSIGNED -> ONGOING -> COMPLETED
- Free the driver on completion

## Patterns to consider
- Strategy (matching + pricing)
- State (trip)
- SOLID: OCP

## Your job
1. Clarify requirements with the coach.
2. Draw the class diagram (UML) in NOTES.
3. Complete the `// TODO`s in `solution.cpp`.
4. Build + run: `g++ -std=c++17 solution.cpp -o sol && ./sol` — asserts must pass (prints `PASS`).
5. Defend extensibility: what changes if a new requirement arrives?

## Passing criteria
See the bottom of `solution.cpp`. Must compile + run, asserts pass, and adding a new variant should not require editing existing classes (OCP, plus DRY/KISS/YAGNI).
