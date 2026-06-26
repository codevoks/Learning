# In-memory KV Store

**Target time:** 45 min

## Problem
A key-value store with TTL expiry and simple transactions (begin/commit/rollback).

## Requirements
- set/get/delete
- set with optional TTL; expired keys return None
- begin/commit/rollback (nested optional)
- clock injected for TTL

## Passing criteria
- TTL expiry correct
- rollback restores prior state
- commit persists

## Drill
Timer ON → 5-min plan → complete `TODO`s (core first) → `python solution.py` (asserts pass) → self-score on rubric → log time-leak in NOTES.
