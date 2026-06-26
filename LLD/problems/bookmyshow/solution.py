"""BookMyShow — LLD starter stub (concurrency). Run: python solution.py"""
from __future__ import annotations
import threading


class Show:
    def __init__(self, show_id: str, seats: list[str]):
        self.show_id = show_id
        self.available = set(seats)
        self.booked: set[str] = set()
        self.lock = threading.Lock()


class BookingService:
    def __init__(self):
        self.shows: dict[str, Show] = {}
    def add_show(self, show: Show):
        self.shows[show.show_id] = show
    def book(self, show_id: str, seats: list[str]) -> bool:
        show = self.shows[show_id]
        # TODO: acquire show.lock; verify ALL seats available;
        # if yes move them available->booked and return True; else return False
        raise NotImplementedError


if __name__ == "__main__":
    svc = BookingService()
    svc.add_show(Show("S1", ["A1", "A2", "A3"]))
    results = []
    def worker():
        results.append(svc.book("S1", ["A1"]))
    ts = [threading.Thread(target=worker) for _ in range(10)]
    [t.start() for t in ts]; [t.join() for t in ts]
    assert sum(1 for r in results if r) == 1, results  # exactly one booking wins A1
    print("PASS")

# PASSING CRITERIA:
# - under concurrent requests, a seat is booked exactly once
# - partial booking (some seats taken) is rejected atomically
# - (bonus) seat-hold with timeout
