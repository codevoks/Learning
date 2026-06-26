# Hotel Booking

## Problem
Design a hotel reservation system: room types, availability over date ranges, pricing.

## Functional requirements
- Rooms of types (STANDARD/DELUXE)
- Book a room type for [checkIn, checkOut) only if a room is free (no overlap)
- Fall back to another room of the type if one overlaps
- Pricing via strategy (per type per night)
- (bonus) concurrency: no double-booking

## Patterns to consider
- Strategy (pricing)
- interval overlap
- concurrency

## Your job
1. Clarify requirements with the coach.
2. Draw the class diagram (UML) in NOTES.
3. Complete the `// TODO`s in `solution.cpp`.
4. Build + run: `g++ -std=c++17 solution.cpp -o sol && ./sol` — asserts must pass (prints `PASS`).
5. Defend extensibility: what changes if a new requirement arrives?

## Passing criteria
See the bottom of `solution.cpp`. Must compile + run, asserts pass, and adding a new variant should not require editing existing classes (OCP, plus DRY/KISS/YAGNI).
