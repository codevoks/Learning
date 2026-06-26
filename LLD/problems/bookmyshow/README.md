# BookMyShow (Movie Booking)

## Problem
Design a movie ticket booking system with concurrent seat booking — NO double booking.

## Functional requirements
- Movies, theatres, screens, shows, seats
- Search shows; view seat availability
- Book seats for a show; hold seats briefly then confirm on payment
- CONCURRENCY: two users must not book the same seat
- Release hold on timeout/cancel

## Core entities (suggested)
`BookingService`, `Show`, `Seat`, `Booking`, `SeatLock`

## Patterns to consider
- Concurrency (locking)
- State (booking)
- SOLID: SRP

## Your job
1. Clarify requirements with the coach.
2. Draw the class diagram (UML) in NOTES.
3. Complete the `TODO`s in `solution.cpp`.
4. Run `g++ -std=c++17 solution.cpp -o sol && ./sol` — the demo asserts must pass.
5. Defend extensibility: what changes if a new requirement arrives?

## Passing criteria
See the bottom of `solution.cpp`. Code must run, asserts pass, and adding a new variant should not require editing existing classes (OCP).
