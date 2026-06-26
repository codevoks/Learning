"""LRU Cache — machine-coding stub (target 30 min). Run: python solution.py"""
from collections import OrderedDict


class LRUCache:
    def __init__(self, capacity: int):
        self.cap = capacity
        self.store: "OrderedDict[int, int]" = OrderedDict()
    def get(self, key: int) -> int:
        # TODO: if present, move_to_end and return; else -1
        raise NotImplementedError
    def put(self, key: int, value: int) -> None:
        # TODO: set+move_to_end; if over capacity, popitem(last=False)
        raise NotImplementedError


if __name__ == "__main__":
    c = LRUCache(2)
    c.put(1, 1); c.put(2, 2)
    assert c.get(1) == 1
    c.put(3, 3)            # evicts key 2 (LRU)
    assert c.get(2) == -1
    c.put(4, 4)            # evicts key 1
    assert c.get(1) == -1 and c.get(3) == 3 and c.get(4) == 4
    print("PASS")

# PASSING CRITERIA: O(1) get/put, correct eviction order, updating existing key refreshes recency.
