# Stack Overflow

## Problem
Design a Q&A site: questions, answers, voting, accepted answer, tags.

## Functional requirements
- Post questions with tags; post answers to a question
- Up/down vote questions (and answers)
- Question author can accept exactly one answer
- (bonus) tag search, user reputation, comments

## Patterns to consider
- composition
- encapsulation
- SOLID: SRP

## Your job
1. Clarify requirements with the coach.
2. Draw the class diagram (UML) in NOTES.
3. Complete the `// TODO`s in `solution.cpp`.
4. Build + run: `g++ -std=c++17 solution.cpp -o sol && ./sol` — asserts must pass (prints `PASS`).
5. Defend extensibility: what changes if a new requirement arrives?

## Passing criteria
See the bottom of `solution.cpp`. Must compile + run, asserts pass, and adding a new variant should not require editing existing classes (OCP, plus DRY/KISS/YAGNI).
