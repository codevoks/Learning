# Notification Service

**Target time:** 45 min

## Problem
Send notifications over multiple channels with retry + dedup (CV: outbox/exactly-once).

## Requirements
- channels: email/sms (pluggable); send(user, msg, channel)
- dedup: same (user,msg,key) not sent twice
- retry on channel failure up to N times

## Passing criteria
- dedup by idempotency key
- retry then give up
- new channel added without core change

## Drill
Timer ON → 5-min plan → complete `TODO`s (core first) → `python solution.py` (asserts pass) → self-score on rubric → log time-leak in NOTES.
