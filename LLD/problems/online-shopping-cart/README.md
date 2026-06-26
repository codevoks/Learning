# Online Shopping Cart (Amazon)

## Problem
Design a shopping cart: catalog, add/remove items, discounts, checkout with payment.

## Functional requirements
- Catalog of products; add/remove items with quantity
- Compute subtotal
- Apply a pluggable discount strategy at checkout
- Pay via pluggable payment strategy; return final total
- (bonus) inventory, order placement, multiple coupons

## Patterns to consider
- Strategy (discount + payment)
- State (order)
- SOLID: OCP

## Your job
1. Clarify requirements with the coach.
2. Draw the class diagram (UML) in NOTES.
3. Complete the `// TODO`s in `solution.cpp`.
4. Build + run: `g++ -std=c++17 solution.cpp -o sol && ./sol` — asserts must pass (prints `PASS`).
5. Defend extensibility: what changes if a new requirement arrives?

## Passing criteria
See the bottom of `solution.cpp`. Must compile + run, asserts pass, and adding a new variant should not require editing existing classes (OCP, plus DRY/KISS/YAGNI).
