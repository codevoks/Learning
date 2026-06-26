"""Elevator System — LLD starter stub. Complete the TODOs. Run: python solution.py"""
from __future__ import annotations
from abc import ABC, abstractmethod
from enum import Enum


class Direction(Enum):
    UP = 1
    DOWN = -1
    IDLE = 0


class SchedulingStrategy(ABC):
    @abstractmethod
    def next_target(self, current: int, targets: set[int], direction: Direction) -> int | None: ...


class NearestStrategy(SchedulingStrategy):
    def next_target(self, current, targets, direction):
        # TODO: return the closest target floor, or None if no targets
        raise NotImplementedError


class Elevator:
    def __init__(self, eid: str, strategy: SchedulingStrategy):
        self.eid = eid
        self.floor = 0
        self.direction = Direction.IDLE
        self.targets: set[int] = set()
        self.strategy = strategy
    def request(self, floor: int) -> None:
        self.targets.add(floor)
    def step(self) -> None:
        # TODO: ask strategy for next target, move ONE floor toward it,
        # update direction, remove target on arrival
        raise NotImplementedError


class ElevatorSystem:
    def __init__(self, elevators: list[Elevator]):
        self.elevators = elevators
    def dispatch(self, floor: int) -> Elevator:
        # TODO: choose the best elevator (e.g. closest idle/same-direction)
        raise NotImplementedError


if __name__ == "__main__":
    e = Elevator("E1", NearestStrategy())
    e.request(3)
    for _ in range(5):
        e.step()
        if not e.targets:
            break
    assert e.floor == 3, e.floor
    print("PASS")

# PASSING CRITERIA:
# - elevator reaches requested floor; direction updates correctly
# - swapping SchedulingStrategy (e.g. SCAN) needs no Elevator change
# - dispatcher picks a reasonable elevator
