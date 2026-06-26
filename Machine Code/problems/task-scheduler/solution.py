"""Task Scheduler — machine-coding stub (target 45 min). Run: python solution.py"""
import heapq
import itertools


class Scheduler:
    def __init__(self):
        self.heap: list[tuple[float, int, object, float | None]] = []
        self.counter = itertools.count()
    def schedule(self, task, run_at: float, interval: float | None = None) -> None:
        # TODO: push (run_at, seq, task, interval) onto heap
        raise NotImplementedError
    def run_due(self, now: float) -> list:
        # TODO: pop all tasks with run_at <= now, call them, re-schedule recurring; return executed tasks
        raise NotImplementedError


if __name__ == "__main__":
    log = []
    s = Scheduler()
    s.schedule(lambda: log.append("a"), run_at=5)
    s.schedule(lambda: log.append("b"), run_at=1)
    s.run_due(now=2)            # only b
    assert log == ["b"], log
    s.run_due(now=10)           # then a
    assert log == ["b", "a"], log
    print("PASS")

# PASSING CRITERIA: runs due tasks in time order; recurring re-schedules; future tasks not run early.
