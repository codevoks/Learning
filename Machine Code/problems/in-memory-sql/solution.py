"""In-memory SQL — machine-coding stub (target 60 min). Run: python solution.py"""
from typing import Callable


class Table:
    def __init__(self, columns: list[str]):
        self.columns = columns
        self.rows: list[dict] = []


class Database:
    def __init__(self):
        self.tables: dict[str, Table] = {}
    def create_table(self, name: str, columns: list[str]) -> None:
        self.tables[name] = Table(columns)
    def insert(self, name: str, row: dict) -> None:
        # TODO: validate columns, append row
        raise NotImplementedError
    def select(self, name: str, where: Callable[[dict], bool] | None = None,
               order_by: str | None = None, limit: int | None = None) -> list[dict]:
        # TODO: filter by where, sort by order_by, apply limit
        raise NotImplementedError


if __name__ == "__main__":
    db = Database()
    db.create_table("users", ["id", "age"])
    for i, a in [(1, 30), (2, 20), (3, 40)]:
        db.insert("users", {"id": i, "age": a})
    res = db.select("users", where=lambda r: r["age"] >= 30, order_by="age", limit=1)
    assert res == [{"id": 1, "age": 30}], res
    print("PASS")

# PASSING CRITERIA: where filters, order_by sorts, limit caps; invalid column rejected.
