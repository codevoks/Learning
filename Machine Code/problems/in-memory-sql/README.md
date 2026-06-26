# In-memory SQL

**Target time:** 60 min

## Problem
A tiny in-memory query engine: create table, insert, and select with where/order/limit.

## Requirements
- create_table(name, columns); insert(name, row dict)
- select(name, where=predicate, order_by=col, limit=n)
- return list of matching rows
- (bonus) simple aggregation count/sum

## Passing criteria
- filtering correct
- ordering + limit correct
- missing column handled

## Drill
Timer ON → 5-min plan → complete `TODO`s (core first) → `python solution.py` (asserts pass) → self-score on rubric → log time-leak in NOTES.
