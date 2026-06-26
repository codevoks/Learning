"""Parking Lot — LLD starter stub. Complete the TODOs. Run: python solution.py"""
from __future__ import annotations
from abc import ABC, abstractmethod
from enum import Enum
from datetime import datetime, timedelta


class SpotSize(Enum):
    SMALL = 1
    MEDIUM = 2
    LARGE = 3


class Vehicle:
    def __init__(self, plate: str, size: SpotSize):
        self.plate = plate
        self.size = size


class PricingStrategy(ABC):
    @abstractmethod
    def price(self, entry: datetime, exit: datetime, size: SpotSize) -> float: ...


class HourlyPricing(PricingStrategy):
    RATES = {SpotSize.SMALL: 10, SpotSize.MEDIUM: 20, SpotSize.LARGE: 30}
    def price(self, entry, exit, size):
        # TODO: ceil hours * rate[size]
        raise NotImplementedError


class ParkingSpot:
    def __init__(self, spot_id: str, size: SpotSize):
        self.spot_id = spot_id
        self.size = size
        self.vehicle: Vehicle | None = None
    def is_free(self) -> bool:
        return self.vehicle is None
    def can_fit(self, v: Vehicle) -> bool:
        # TODO: a vehicle fits a spot of equal-or-larger size
        raise NotImplementedError


class Ticket:
    def __init__(self, vehicle: Vehicle, spot: ParkingSpot, entry: datetime):
        self.vehicle, self.spot, self.entry = vehicle, spot, entry


class ParkingLot:
    def __init__(self, spots: list[ParkingSpot], pricing: PricingStrategy):
        self.spots = spots
        self.pricing = pricing
        self.active: dict[str, Ticket] = {}
    def park(self, v: Vehicle) -> Ticket:
        # TODO: find nearest free spot that fits, occupy, return ticket
        raise NotImplementedError
    def unpark(self, plate: str, exit: datetime) -> float:
        # TODO: free the spot, compute fee via pricing strategy
        raise NotImplementedError


if __name__ == "__main__":
    spots = [ParkingSpot("S1", SpotSize.SMALL), ParkingSpot("M1", SpotSize.MEDIUM)]
    lot = ParkingLot(spots, HourlyPricing())
    t = lot.park(Vehicle("KA01", SpotSize.SMALL))
    fee = lot.unpark("KA01", t.entry + timedelta(hours=2))
    assert fee == 20, fee  # 2h * 10
    print("PASS")

# PASSING CRITERIA:
# - park assigns a fitting free spot; raises/handles when full
# - unpark frees spot and returns correct fee
# - adding a new PricingStrategy needs NO change to ParkingLot (OCP)
