# LFU Cache

**Target time:** 45 min

## Problem
Implement an LFU cache: evict least-frequently-used; ties broken by least-recently-used.

## Requirements
- get/put with frequency tracking
- evict min-frequency (LRU among ties) on overflow
- O(1) amortized preferred

## Passing criteria
- correct frequency-based eviction
- tie-break by recency
- update bumps frequency

## Drill
Timer ON → 5-min plan → complete `TODO`s (core first) → `g++ -std=c++17 solution.cpp -o sol && ./sol` (asserts pass) → self-score on rubric → log time-leak in NOTES.
