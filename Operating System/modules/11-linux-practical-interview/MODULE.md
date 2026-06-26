# Module 11 — Linux Practical + Interview Rapid-fire

> **Agent spawn**: `@Memory.md` + `@Prompt.md` + this file + `@NOTES.md`
> **Nav**: ← [10 IPC](../10-ipc/MODULE.md)

## At a glance
| | |
|---|---|
| Prerequisites | 01–10 |
| Duration | ~1–2 sessions |
| Exit test | 10 rapid-fire FAQ confidently + read a `top` snapshot |

## Visual map
```
Containers = namespaces (isolation) + cgroups (resource limits)
  namespaces: pid, net, mount, user, ipc, uts  → "alag duniya dikhti hai"
  cgroups:    cpu, memory, io limits            → "itna hi milega"

top:  load avg 1.20 0.90 0.50  → 1/5/15 min runnable+uninterruptible procs
      > #cores sustained = overloaded
```
```mermaid
flowchart LR
    Proc -->|reads| ProcFS[/proc/PID]
    Tools[top/ps/strace/lsof] --> ProcFS
    ProcFS --> Insight[CPU / mem / fds / syscalls]
```
**Mental model**: `/proc` = kernel ka live data filesystem ke roop mein. Tools usi ko padhte hain. Docker container = Linux process with namespaces + cgroups, alag VM nahi.

**Redraw challenge**: namespaces + cgroups = container diagram.

## Objectives
1. `/proc`, `top`/`ps`/`vmstat`/`iostat`, `strace`, `lsof`
2. Load average, OOM killer, file descriptors
3. namespaces + cgroups → containers bridge
4. Rapid-fire interview FAQ

## Topics
- `/proc` & `/sys`; reading `top`/`htop`/`ps`/`vmstat`/`iostat`
- `strace`/`ltrace`; load average; OOM killer; `nice`/`renice`
- File descriptors + `lsof`; ulimits
- cgroups + namespaces → Docker/containers
- **FAQ**: process vs thread, deadlock, paging vs segmentation, virtual memory, context-switch cost, mutex vs semaphore, GIL, fork vs exec, what happens on `malloc`, zombie/orphan

## Assignments
| # | Task | Passing criteria |
|---|------|------------------|
| A1 | Read a real `top` output — explain CPU/mem/load | Each field explained correctly |
| A2 | `strace` a Python script, identify syscalls | Top syscalls named + categorized |

## Active recall bank (rapid-fire — bina notes ke)
1. Load average 3 numbers?
2. Container = ? + ?
3. Context switch mehnga kyun?
4. malloc pe kya hota (sbrk/mmap, page fault)?

## Progress checklist
- [ ] 10 FAQ confidently answered
- [ ] A1, A2 done
- [ ] **OS spaced-rep checklist** (LEARNING-PLAN) full pass
- [ ] NOTES.md updated
