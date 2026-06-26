"""Logging Framework — LLD starter stub (Chain of Responsibility). Run: python solution.py"""
from __future__ import annotations
from abc import ABC, abstractmethod
from enum import IntEnum


class Level(IntEnum):
    DEBUG = 1
    INFO = 2
    WARN = 3
    ERROR = 4


class Appender(ABC):
    @abstractmethod
    def append(self, level: Level, msg: str) -> None: ...


class ConsoleAppender(Appender):
    def __init__(self): self.lines: list[str] = []
    def append(self, level, msg):
        # TODO: store/print f"[{level.name}] {msg}"
        raise NotImplementedError


class Logger:
    def __init__(self, min_level: Level, appenders: list[Appender]):
        self.min_level = min_level
        self.appenders = appenders
    def log(self, level: Level, msg: str) -> None:
        # TODO: if level >= min_level, dispatch to all appenders
        raise NotImplementedError
    def info(self, msg): self.log(Level.INFO, msg)
    def error(self, msg): self.log(Level.ERROR, msg)


if __name__ == "__main__":
    con = ConsoleAppender()
    log = Logger(Level.INFO, [con])
    log.log(Level.DEBUG, "skip me")
    log.info("hello")
    log.error("boom")
    assert len(con.lines) == 2, con.lines  # debug filtered out
    print("PASS")

# PASSING CRITERIA:
# - messages below min_level are filtered
# - multiple appenders all receive eligible messages
# - new appender/level added without editing Logger (OCP)
