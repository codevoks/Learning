# Food Delivery System

## Problem
Design a food delivery app: restaurants, orders, and a pluggable rider-assignment strategy.

## Functional requirements
- Restaurants with menus; customers place orders
- Order lifecycle states (PLACED, ACCEPTED, PREPARING, OUT_FOR_DELIVERY, DELIVERED)
- Rider assignment strategy (nearest, least-busy) — swappable
- Track order status
- Surge/ETA (bonus)

## Core entities (suggested)
`FoodDeliveryApp`, `Restaurant`, `Order`, `Rider`, `AssignmentStrategy`

## Patterns to consider
- Strategy (assignment)
- State (order)
- SOLID: OCP

## Your job
1. Clarify requirements with the coach.
2. Draw the class diagram (UML) in NOTES.
3. Complete the `TODO`s in `solution.py`.
4. Run `python solution.py` — the demo asserts must pass.
5. Defend extensibility: what changes if a new requirement arrives?

## Passing criteria
See the bottom of `solution.py`. Code must run, asserts pass, and adding a new variant should not require editing existing classes (OCP).
