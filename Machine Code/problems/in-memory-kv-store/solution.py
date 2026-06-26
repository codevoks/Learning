"""In-memory KV Store — machine-coding stub (target 45 min). Run: python solution.py"""


class KVStore:
    def __init__(self, now=lambda: 0.0):
        self.data: dict[str, tuple[str, float | None]] = {}  # key -> (value, expire_at)
        self.now = now
        self.tx_stack: list[dict] = []
    def set(self, key: str, value: str, ttl: float | None = None) -> None:
        # TODO: store value with expire_at = now()+ttl if ttl else None
        raise NotImplementedError
    def get(self, key: str) -> str | None:
        # TODO: return value if present and not expired, else None (and purge if expired)
        raise NotImplementedError
    def delete(self, key: str) -> None:
        self.data.pop(key, None)
    def begin(self) -> None:
        # TODO: push a snapshot/copy of data
        raise NotImplementedError
    def rollback(self) -> None:
        # TODO: restore last snapshot
        raise NotImplementedError
    def commit(self) -> None:
        # TODO: drop last snapshot (changes persist)
        raise NotImplementedError


if __name__ == "__main__":
    t = {"v": 0.0}
    kv = KVStore(now=lambda: t["v"])
    kv.set("a", "1", ttl=10)
    assert kv.get("a") == "1"
    t["v"] = 11
    assert kv.get("a") is None          # expired
    kv.set("b", "x"); kv.begin(); kv.set("b", "y"); kv.rollback()
    assert kv.get("b") == "x"           # rolled back
    print("PASS")

# PASSING CRITERIA: TTL expiry, rollback restores, commit persists, clock injected.
