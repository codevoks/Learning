# Module 01 — Fundamentals & Estimation

> **Agent spawn**: `@Memory.md` + `@Prompt.md` + this file + `@NOTES.md`
> **Nav**: ← [00 Framework](../00-framework/MODULE.md) · Next → [02 Scaling & LB](../02-scaling-load-balancing/MODULE.md)

## At a glance
| | |
|---|---|
| Prerequisites | 00 |
| Duration | ~1 session |
| Exit test | Latency table + estimate any app QPS/storage |

## Visual map
```
LATENCY (memorize):
  L1 ~1ns | RAM ~100ns | SSD ~100µs | DC RTT ~0.5ms | disk seek ~10ms | cross-region ~50-150ms

QPS = daily_requests / 10^5     (1 day ≈ 86,400 ≈ 10^5 s)
Availability: 99.9%=8.7h/yr  99.99%=52min  99.999%=5min
```
```mermaid
flowchart LR
    DAU[DAU] --> Req[req/user/day] --> Total[total/day] --> QPS[/10^5 = QPS]
    QPS --> Peak[x2-3 = peak QPS]
```
**Mental model**: Estimation = sanity check, perfect nahi. Round numbers. Read:write ratio se cache/replica decisions nikalte hain. Latency numbers se "memory mein rakhun ya disk" decide hota hai.

**Redraw challenge**: Latency ladder + QPS formula chain.

## Objectives
1. Latency vs throughput; latency numbers
2. Back-of-envelope: QPS, storage, bandwidth, memory
3. SLA/SLO/SLI; availability 9s
4. Peak vs average; capacity planning

## Topics
- Latency vs throughput; tail latency (p50/p95/p99)
- Latency numbers every engineer should know
- Estimation: QPS, storage/day & 5yr, bandwidth, cache memory
- Read:write ratio implications
- SLA vs SLO vs SLI; availability math

## Assignments
| # | Task | Passing criteria |
|---|------|------------------|
| A1 | Photo app (200M DAU): storage/yr + QPS + bandwidth | Reasonable order-of-magnitude, shown working |
| A2 | Servers needed for 500k QPS (assume per-server cap) | Justified number |

## Active recall bank
1. Latency table top-to-bottom?
2. QPS formula + peak factor?
3. 99.99% = kitna downtime/year?
4. p99 kyun matter karta p50 se zyada?

## Progress checklist
- [ ] Latency numbers from memory
- [ ] A1, A2 done
- [ ] NOTES.md updated
