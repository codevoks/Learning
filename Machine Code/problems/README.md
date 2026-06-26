# Machine Coding Problems — Timed C++ Practice 🔥

> Har problem: `README.md` (requirements + time budget + passing criteria) + `solution.cpp` (starter stub). **Timer laga ke** solve karo, build+run karke asserts pass karao, phir rubric pe self-score.

## Drill loop (every problem)
1. Start a timer (target time in README).
2. 5–10 min plan: entities + interfaces + MUST/NICE.
3. Complete the `// TODO`s — **core happy-path first**.
4. Build + run: `g++ -std=c++17 solution.cpp -o sol && ./sol` → asserts pass + prints `PASS`.
5. Self-score: Working / Clean / Design / Extensible / Tested / Edge (1–5).
6. Note in `NOTES.md`: time taken + where time leaked + 1 fix.

## Problem set
| # | Problem | Target | Key idea | Folder |
|---|---------|--------|----------|--------|
| 1 | LRU Cache | 30m | hashmap + doubly linked list | `lru-cache/` |
| 2 | LFU Cache | 45m | freq buckets | `lfu-cache/` |
| 3 | Rate Limiter | 30m | token bucket (CV) | `rate-limiter/` |
| 4 | In-memory KV store | 45m | map + TTL + txn | `in-memory-kv-store/` |
| 5 | In-memory SQL | 60m | table + where/order/limit | `in-memory-sql/` |
| 6 | Task Scheduler | 45m | min-heap by run-time | `task-scheduler/` |
| 7 | Logging Library | 30m | levels + appenders | `logging-library/` |
| 8 | Calendar Scheduler | 45m | interval overlap | `calendar-meeting-scheduler/` |
| 9 | In-memory File System | 60m | tree + paths | `file-system/` |
| 10 | Snake & Ladder | 30m | board + dice | `snake-and-ladder/` |
| 11 | Tic-Tac-Toe | 30m | NxN win-check | `tic-tac-toe/` |
| 12 | Notification Service | 45m | channels + retry + dedup (CV) | `notification-service/` |
| 13 | Text Editor (undo/redo) | 45m | Command pattern / stacks | `text-editor/` |
| 14 | Pub-Sub System | 45m | topics + subscribers (Observer) | `pub-sub-system/` |

> Ramp: 1 LRU → 3 Rate limiter → 7 Logging → 11 Tic-Tac-Toe → 13 Text editor → 4 KV → 14 Pub-Sub → 6 Scheduler → 8 Calendar → 5 SQL → 9 File system.
