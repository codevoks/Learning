# Parking Lot

## Problem
Design a parking lot that supports multiple vehicle and spot sizes, ticketing, and pluggable pricing.

## Functional requirements
- Multiple floors, each with spots of types: SMALL, MEDIUM, LARGE
- Vehicle types map to allowed spot sizes
- Park: assign nearest suitable free spot, issue ticket (entry time)
- Unpark: free spot, compute fee via a pricing strategy
- Pricing must be swappable (hourly, flat, day-based) WITHOUT editing ParkingLot

## Core entities (suggested)
`ParkingLot`, `Floor`, `ParkingSpot`, `Vehicle`, `Ticket`, `PricingStrategy`

## Patterns to consider
- Strategy (pricing)
- Factory (spot/vehicle)
- SOLID: OCP for pricing

## Your job
1. Clarify requirements with the coach.
2. Draw the class diagram (UML) in NOTES.
3. Complete the `TODO`s in `solution.cpp`.
4. Run `g++ -std=c++17 solution.cpp -o sol && ./sol` — the demo asserts must pass.
5. Defend extensibility: what changes if a new requirement arrives?

## Passing criteria
See the bottom of `solution.cpp`. Code must run, asserts pass, and adding a new variant should not require editing existing classes (OCP).
