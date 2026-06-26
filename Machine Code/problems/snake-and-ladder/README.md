# Snake & Ladder

**Target time:** 30 min

## Problem
Simulate Snake & Ladder for multiple players (deterministic dice for tests).

## Requirements
- board size N, jumps dict (start->end)
- players take turns; move by dice; apply jumps; no overshoot
- first to reach N wins

## Passing criteria
- jumps applied
- no overshoot past N
- win detected

## Drill
Timer ON → 5-min plan → complete `TODO`s (core first) → `g++ -std=c++17 solution.cpp -o sol && ./sol` (asserts pass) → self-score on rubric → log time-leak in NOTES.
