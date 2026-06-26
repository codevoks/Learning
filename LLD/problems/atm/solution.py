"""ATM — LLD starter stub (State pattern). Run: python solution.py"""
from __future__ import annotations
from abc import ABC, abstractmethod


class Account:
    def __init__(self, pin: str, balance: int):
        self.pin, self.balance = pin, balance


class ATMState(ABC):
    def __init__(self, atm: "ATM"): self.atm = atm
    @abstractmethod
    def insert_card(self, acc: Account): ...
    @abstractmethod
    def enter_pin(self, pin: str): ...
    @abstractmethod
    def withdraw(self, amount: int): ...


class IdleState(ATMState):
    def insert_card(self, acc):
        # TODO: set current account, move to CardInsertedState
        raise NotImplementedError
    def enter_pin(self, pin): raise RuntimeError("Insert card first")
    def withdraw(self, amount): raise RuntimeError("Insert card first")


# TODO: CardInsertedState (enter_pin), AuthenticatedState (withdraw)


class ATM:
    def __init__(self, cash: int):
        self.cash = cash
        self.account: Account | None = None
        self.state: ATMState = IdleState(self)
    def insert_card(self, acc): self.state.insert_card(acc)
    def enter_pin(self, pin): self.state.enter_pin(pin)
    def withdraw(self, amount): self.state.withdraw(amount)


if __name__ == "__main__":
    atm = ATM(cash=10000)
    acc = Account("1234", 500)
    atm.insert_card(acc)
    atm.enter_pin("1234")
    atm.withdraw(300)
    assert acc.balance == 200 and atm.cash == 9700
    print("PASS")

# PASSING CRITERIA:
# - wrong PIN rejected; actions illegal for a state raise
# - withdraw checks account balance AND atm cash
# - balances update correctly
