# LRU Cache

**Target time:** 30 min

## Problem
Implement an LRU cache with O(1) get and put.

## Requirements
- get(key) -> value or -1, marks key most-recently-used
- put(key, value); evict least-recently-used when over capacity
- All ops O(1)
- capacity fixed at construction

## Passing criteria
- Working O(1) get/put
- eviction correct
- handles update of existing key

## Drill
Timer ON → 5-min plan → complete `TODO`s (core first) → `g++ -std=c++17 solution.cpp -o sol && ./sol` (asserts pass) → self-score on rubric → log time-leak in NOTES.
