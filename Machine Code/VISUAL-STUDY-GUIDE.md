# Machine Coding Visual Study Guide — Vansh

> Visual learner master sheet. Approach + rubric pehle, redraw se recall.

## The 90-min playbook (MEMORIZE)
```mermaid
flowchart LR
    A[0-10 Clarify + feature priority] --> B[10-20 Design: entities/interfaces/patterns]
    B --> C[20-55 Code CORE happy path first - demoable]
    C --> D[55-75 Add features incrementally]
    D --> E[75-85 Tests + edge cases]
    E --> F[85-90 Refactor + walkthrough]
```
```
RULE 1: Working > elegant-but-unfinished. Get something runnable EARLY.
RULE 2: MUST features before NICE features.
RULE 3: Speak assumptions, comment them.
```

## Scoring rubric (self-score every attempt)
```
Working      ▢▢▢▢▢  runs + core demoable
Clean        ▢▢▢▢▢  readable, small methods, good names
OOP/Design   ▢▢▢▢▢  right classes, SOLID, pattern where it fits
Extensible   ▢▢▢▢▢  new requirement = minimal change (OCP)
Tested       ▢▢▢▢▢  demo/asserts/unittest
Edge cases   ▢▢▢▢▢  invalid/empty/concurrency
```

## Reusable building blocks
```
In-memory Repository : dict[id]->obj + indexes; add/get/query
ID gen               : itertools.count() or uuid4()
Clock injection      : pass a now() callable → testable time logic
State machine        : Enum + dict transitions (or State pattern)
Strategy             : pluggable algorithm (pricing/split/assignment)
Concurrency          : threading.Lock per resource / queue.Queue
```

## CV → Machine-coding bridge
```
In-memory matching engine ──► KV store, in-memory SQL
Token-bucket rate limiter ──► Rate limiter problem
Queue workers / outbox    ──► Task scheduler, notification service
Refund state machine      ──► Vending / ATM / order state problems
```

## LRU in O(1) (most-asked)
```
HashMap key->node  +  Doubly Linked List (MRU head ... LRU tail)
get: move node to head | put: insert head, if over capacity evict tail
(Python shortcut: collections.OrderedDict.move_to_end + popitem)
```

## Spaced-rep recall bank
1. 6-step playbook?
2. Rubric 6 dimensions?
3. LRU O(1) data structures?
4. Token bucket logic?
5. Clock injection kyun (testability)?
6. Working-first kyun > elegant-unfinished?
