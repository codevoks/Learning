# Rate Limiter

**Target time:** 30 min

## Problem
Implement a token-bucket rate limiter (CV anchor). allow(key) returns True/False.

## Requirements
- Per-key bucket: capacity C, refill rate r tokens/sec
- allow(key, now) consumes a token if available
- Clock injected (testable, no real sleep)
- (bonus) sliding-window variant

## Passing criteria
- correct allow/deny under burst
- refill over time works
- clock injected

## Drill
Timer ON → 5-min plan → complete `TODO`s (core first) → `python solution.py` (asserts pass) → self-score on rubric → log time-leak in NOTES.
