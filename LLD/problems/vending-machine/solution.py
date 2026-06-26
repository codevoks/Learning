"""Vending Machine — LLD starter stub (State pattern). Run: python solution.py"""
from __future__ import annotations
from abc import ABC, abstractmethod


class State(ABC):
    def __init__(self, machine: "VendingMachine"):
        self.machine = machine
    @abstractmethod
    def select(self, code: str) -> None: ...
    @abstractmethod
    def insert(self, amount: int) -> None: ...
    @abstractmethod
    def dispense(self) -> None: ...


class IdleState(State):
    def select(self, code):
        # TODO: if item in stock, set selected + move to ItemSelectedState
        raise NotImplementedError
    def insert(self, amount):
        raise RuntimeError("Select an item first")
    def dispense(self):
        raise RuntimeError("Select and pay first")


# TODO: implement ItemSelectedState, HasMoneyState, DispensingState


class VendingMachine:
    def __init__(self, inventory: dict[str, tuple[int, int]]):
        # inventory: code -> (price, qty)
        self.inventory = inventory
        self.selected: str | None = None
        self.balance = 0
        self.state: State = IdleState(self)
    def select(self, code): self.state.select(code)
    def insert(self, amount): self.state.insert(amount)
    def dispense(self): self.state.dispense()


if __name__ == "__main__":
    vm = VendingMachine({"A1": (30, 2)})
    vm.select("A1")
    vm.insert(20)
    vm.insert(10)
    vm.dispense()  # should dispense A1
    assert vm.inventory["A1"][1] == 1
    print("PASS")

# PASSING CRITERIA:
# - illegal action for a state raises/handled
# - dispense only after sufficient payment; change returned
# - inventory decrements; out-of-stock handled
