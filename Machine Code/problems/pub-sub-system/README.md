# Pub-Sub System

**Target time:** 45 min

## Problem
An in-memory publish-subscribe message broker with topics and subscribers.

## Requirements
- subscribe/unsubscribe a subscriber to a topic
- publish a message: all topic subscribers receive it
- no duplicate subscriptions; no delivery after unsubscribe
- (bonus) wildcard topics, async delivery, at-least-once

## Passing criteria
- per-topic fan-out
- subscribe/unsubscribe correct
- Observer pattern, OCP for new subscriber types

## Drill
Timer ON → 5-min plan → complete `// TODO`s (core first) → `g++ -std=c++17 solution.cpp -o sol && ./sol` (asserts pass) → self-score on rubric → log time-leak in NOTES.
