# Task Scheduler

**Target time:** 45 min

## Problem
Schedule tasks to run at/after a given time; support recurring tasks.

## Requirements
- schedule(task, run_at); run_due(now) runs all due tasks in time order
- recurring tasks re-schedule by interval
- clock injected

## Passing criteria
- due tasks run in order
- recurring re-enqueues
- not-yet-due skipped

## Drill
Timer ON → 5-min plan → complete `TODO`s (core first) → `python solution.py` (asserts pass) → self-score on rubric → log time-leak in NOTES.
