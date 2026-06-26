"""Splitwise — LLD starter stub. Run: python solution.py"""
from __future__ import annotations
from abc import ABC, abstractmethod
from collections import defaultdict


class SplitStrategy(ABC):
    @abstractmethod
    def shares(self, amount: float, participants: list[str], meta: dict) -> dict[str, float]: ...


class EqualSplit(SplitStrategy):
    def shares(self, amount, participants, meta):
        # TODO: divide equally
        raise NotImplementedError


class PercentSplit(SplitStrategy):
    def shares(self, amount, participants, meta):
        # TODO: meta["percent"] = {user: pct}; pct must sum to 100
        raise NotImplementedError


class Splitwise:
    def __init__(self):
        # balance[a][b] = how much a owes b
        self.balance: dict[str, dict[str, float]] = defaultdict(lambda: defaultdict(float))
    def add_expense(self, paid_by: str, amount: float, participants: list[str],
                    strategy: SplitStrategy, meta: dict | None = None) -> None:
        # TODO: compute shares, update balances (each participant owes paid_by their share)
        raise NotImplementedError
    def balance_of(self, user: str) -> float:
        # TODO: net = owed_to_user - user_owes
        raise NotImplementedError


if __name__ == "__main__":
    s = Splitwise()
    s.add_expense("A", 300, ["A", "B", "C"], EqualSplit())
    assert round(s.balance_of("A")) == 200   # A paid 300, owns 100 share -> net +200
    assert round(s.balance_of("B")) == -100
    print("PASS")

# PASSING CRITERIA:
# - EQUAL/EXACT/PERCENT splits produce correct balances
# - adding a new SplitStrategy needs no change to Splitwise (OCP)
# - net balances sum to 0
