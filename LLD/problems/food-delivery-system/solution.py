"""Food Delivery — LLD starter stub. Run: python solution.py"""
from __future__ import annotations
from abc import ABC, abstractmethod
from enum import Enum


class OrderStatus(Enum):
    PLACED = 1; ACCEPTED = 2; PREPARING = 3; OUT_FOR_DELIVERY = 4; DELIVERED = 5


class Rider:
    def __init__(self, rid: str, location: int, active_orders: int = 0):
        self.rid, self.location, self.active_orders = rid, location, active_orders


class AssignmentStrategy(ABC):
    @abstractmethod
    def assign(self, riders: list[Rider], restaurant_loc: int) -> Rider | None: ...


class NearestRider(AssignmentStrategy):
    def assign(self, riders, restaurant_loc):
        # TODO: return free-ish rider closest to restaurant_loc
        raise NotImplementedError


class Order:
    def __init__(self, oid: str, restaurant_loc: int):
        self.oid, self.restaurant_loc = oid, restaurant_loc
        self.status = OrderStatus.PLACED
        self.rider: Rider | None = None


class FoodDeliveryApp:
    def __init__(self, riders: list[Rider], strategy: AssignmentStrategy):
        self.riders = riders
        self.strategy = strategy
    def assign_rider(self, order: Order) -> Rider:
        # TODO: use strategy; set order.rider; bump rider.active_orders; advance status
        raise NotImplementedError


if __name__ == "__main__":
    riders = [Rider("R1", 10), Rider("R2", 2)]
    app = FoodDeliveryApp(riders, NearestRider())
    o = Order("O1", restaurant_loc=3)
    r = app.assign_rider(o)
    assert r.rid == "R2", r.rid  # R2 closer to loc 3
    print("PASS")

# PASSING CRITERIA:
# - assignment uses the strategy; order gets a rider + status advances
# - swapping AssignmentStrategy needs no app change (OCP)
# - rider load tracked
