"""Notification Service — machine-coding stub (target 45 min). Run: python solution.py"""
from abc import ABC, abstractmethod


class Channel(ABC):
    @abstractmethod
    def send(self, user: str, msg: str) -> bool: ...   # True = success


class FlakyChannel(Channel):
    def __init__(self, fail_times: int):
        self.fail_times = fail_times
        self.sent: list[str] = []
    def send(self, user, msg):
        # TODO: fail (return False) first `fail_times` calls, then succeed (record + True)
        raise NotImplementedError


class NotificationService:
    def __init__(self, channels: dict[str, Channel], max_retries: int = 3):
        self.channels = channels
        self.max_retries = max_retries
        self.seen: set[str] = set()
    def notify(self, user: str, msg: str, channel: str, idem_key: str) -> bool:
        # TODO: if idem_key seen -> return True (dedup, no resend);
        # else try channel.send up to max_retries; on success mark seen + return True; else False
        raise NotImplementedError


if __name__ == "__main__":
    ch = FlakyChannel(fail_times=2)
    svc = NotificationService({"email": ch}, max_retries=3)
    assert svc.notify("u", "hi", "email", "k1") is True   # succeeds on 3rd try
    assert len(ch.sent) == 1
    assert svc.notify("u", "hi", "email", "k1") is True   # dedup, no new send
    assert len(ch.sent) == 1
    print("PASS")

# PASSING CRITERIA: dedup by idem_key, retry up to max then fail, OCP for new channels.
