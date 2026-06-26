# Module 04 — Classic Synchronization Problems

> **Agent spawn**: `@Memory.md` + `@Prompt.md` + this file + `@NOTES.md`
> **Nav**: ← [03 Synchronization](../03-synchronization/MODULE.md) · Next → [05 Deadlocks](../05-deadlocks/MODULE.md)

## At a glance
| | |
|---|---|
| Prerequisites | 03 |
| Duration | ~2 sessions |
| Exit test | Har classic problem ka hazard + fix |

## Visual map
```
Producer–Consumer (bounded buffer):
  Producer ──put──► [ _ _ x x x ] ──get──► Consumer
            empty↑ semaphore       ↑full semaphore + mutex

Dining Philosophers:
       P0
   f4      f0
 P4            P1
   f3      f1
       f2
  P3 ───── P2     each needs LEFT + RIGHT fork → circular wait risk
```
```mermaid
flowchart LR
    P[Producers] -->|wait empty, lock| BUF[(Bounded Buffer)]
    BUF -->|signal full| C[Consumers]
    C -->|signal empty| BUF
```
**Mental model**: Har problem = limited shared resource + coordination. Tools: mutex (exclusion) + semaphores (counting/signaling) + condition variables.

**Redraw challenge**: Producer-consumer with 3 semaphores; dining table with circular wait.

## Objectives
1. Producer–Consumer (empty/full/mutex)
2. Readers–Writers (reader-pref, writer-pref, fair) + starvation
3. Dining Philosophers — deadlock + 3 fixes
4. Sleeping Barber

## Topics
- Producer–Consumer: empty, full, mutex semaphores
- Readers–Writers: 3 variants; writer starvation
- Dining Philosophers: deadlock cause → resource ordering / arbitrator / limit-N-1 diners
- Sleeping Barber; (bonus) Cigarette Smokers

## Assignments
| # | Task | Passing criteria |
|---|------|------------------|
| A1 | Bounded buffer producer-consumer from scratch (Condition) | No lost/dup items, no busy-wait, stress test ok |
| A2 | Dining philosophers — show deadlock then fix with ordering | Fixed version never deadlocks under stress |
| A3 | Readers–writers (writer-preference, stub) | Writers don't starve; concurrent readers allowed |

## Active recall bank
1. Producer-consumer mein 3 semaphores kaun-kaun, kyun?
2. Dining philosophers deadlock kaunsi Coffman condition se?
3. Reader-preference mein writer kaise starve hota?

## Progress checklist
- [ ] Producer-consumer diagram from memory
- [ ] A1–A3 pass
- [ ] NOTES.md updated
