# Logging Library

**Target time:** 30 min

## Problem
A logging library with levels and multiple pluggable appenders.

## Requirements
- levels DEBUG<INFO<WARN<ERROR; min level filter
- multiple appenders (console/in-memory) receive eligible logs
- new appender added without core change

## Passing criteria
- below-min filtered
- all appenders get eligible logs
- format includes level

## Drill
Timer ON → 5-min plan → complete `TODO`s (core first) → `python solution.py` (asserts pass) → self-score on rubric → log time-leak in NOTES.
