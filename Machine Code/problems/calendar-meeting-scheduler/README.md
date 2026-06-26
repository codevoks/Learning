# Calendar / Meeting Scheduler

**Target time:** 45 min

## Problem
Book meetings in rooms without overlap; find free slots.

## Requirements
- book(room, start, end) -> success only if no overlap
- list bookings per room
- (bonus) find earliest free slot of duration d

## Passing criteria
- overlap rejected
- adjacent (end==start) allowed
- per-room isolation

## Drill
Timer ON → 5-min plan → complete `TODO`s (core first) → `g++ -std=c++17 solution.cpp -o sol && ./sol` (asserts pass) → self-score on rubric → log time-leak in NOTES.
