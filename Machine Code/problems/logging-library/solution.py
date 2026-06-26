"""Logging Library — machine-coding stub (target 30 min). Run: python solution.py"""
from abc import ABC, abstractmethod
from enum import IntEnum


class Level(IntEnum):
    DEBUG = 1; INFO = 2; WARN = 3; ERROR = 4


class Appender(ABC):
    @abstractmethod
    def write(self, line: str) -> None: ...


class MemoryAppender(Appender):
    def __init__(self): self.lines: list[str] = []
    def write(self, line):
        # TODO: append line
        raise NotImplementedError


class Logger:
    def __init__(self, min_level: Level, appenders: list[Appender]):
        self.min_level, self.appenders = min_level, appenders
    def log(self, level: Level, msg: str) -> None:
        # TODO: if level>=min_level, write f"[{level.name}] {msg}" to all appenders
        raise NotImplementedError


if __name__ == "__main__":
    mem = MemoryAppender()
    lg = Logger(Level.INFO, [mem])
    lg.log(Level.DEBUG, "x"); lg.log(Level.ERROR, "boom")
    assert mem.lines == ["[ERROR] boom"], mem.lines
    print("PASS")

# PASSING CRITERIA: level filtering, multi-appender fan-out, OCP for new appenders.
