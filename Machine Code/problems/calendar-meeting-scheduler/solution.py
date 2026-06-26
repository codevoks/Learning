"""Calendar / Meeting Scheduler — machine-coding stub (target 45 min). Run: python solution.py"""


class Calendar:
    def __init__(self):
        self.rooms: dict[str, list[tuple[int, int]]] = {}
    def book(self, room: str, start: int, end: int) -> bool:
        # TODO: reject if [start,end) overlaps an existing booking in room; else add and return True
        # note: adjacent intervals (prev_end == start) do NOT overlap
        raise NotImplementedError
    def bookings(self, room: str) -> list[tuple[int, int]]:
        return sorted(self.rooms.get(room, []))


if __name__ == "__main__":
    cal = Calendar()
    assert cal.book("R1", 10, 20) is True
    assert cal.book("R1", 15, 25) is False   # overlap
    assert cal.book("R1", 20, 30) is True    # adjacent ok
    assert cal.book("R2", 15, 25) is True    # different room
    print("PASS")

# PASSING CRITERIA: overlap detection correct, adjacent allowed, per-room isolation.
