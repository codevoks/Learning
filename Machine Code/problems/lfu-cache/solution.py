"""LFU Cache — machine-coding stub (target 45 min). Run: python solution.py"""
from collections import defaultdict, OrderedDict


class LFUCache:
    def __init__(self, capacity: int):
        self.cap = capacity
        self.val: dict[int, int] = {}
        self.freq: dict[int, int] = {}
        self.buckets: dict[int, "OrderedDict[int, None]"] = defaultdict(OrderedDict)
        self.min_freq = 0
    def _bump(self, key: int) -> None:
        # TODO: move key from freq f bucket to f+1 bucket; update min_freq
        raise NotImplementedError
    def get(self, key: int) -> int:
        # TODO: if present, bump freq, return val; else -1
        raise NotImplementedError
    def put(self, key: int, value: int) -> None:
        # TODO: update existing (bump); else evict if full (min_freq bucket, LRU), insert at freq 1
        raise NotImplementedError


if __name__ == "__main__":
    c = LFUCache(2)
    c.put(1, 1); c.put(2, 2)
    assert c.get(1) == 1      # freq(1)=2, freq(2)=1
    c.put(3, 3)               # evicts key 2 (least freq)
    assert c.get(2) == -1 and c.get(3) == 3
    print("PASS")

# PASSING CRITERIA: evicts least-frequent; ties by LRU; get/put both raise frequency.
