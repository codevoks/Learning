"""Library Management — LLD starter stub. Run: python solution.py"""
from __future__ import annotations
from datetime import date, timedelta


class Book:
    def __init__(self, isbn: str, title: str, total: int):
        self.isbn, self.title = isbn, title
        self.total = total
        self.available = total


class Loan:
    def __init__(self, isbn: str, member: str, due: date):
        self.isbn, self.member, self.due = isbn, member, due


class Library:
    LOAN_DAYS = 14
    FINE_PER_DAY = 5
    MAX_BOOKS = 3
    def __init__(self):
        self.books: dict[str, Book] = {}
        self.loans: list[Loan] = []
    def add_book(self, book: Book):
        self.books[book.isbn] = book
    def borrow(self, isbn: str, member: str, today: date) -> Loan:
        # TODO: check availability + member limit; create loan; decrement available
        raise NotImplementedError
    def return_book(self, isbn: str, member: str, today: date) -> int:
        # TODO: find loan; increment available; return fine = max(0, days_late)*FINE_PER_DAY
        raise NotImplementedError


if __name__ == "__main__":
    lib = Library()
    lib.add_book(Book("111", "DDIA", 1))
    today = date(2026, 1, 1)
    lib.borrow("111", "vansh", today)
    fine = lib.return_book("111", "vansh", today + timedelta(days=20))  # 6 days late
    assert fine == 30, fine
    print("PASS")

# PASSING CRITERIA:
# - borrow respects availability + per-member limit
# - return computes correct late fine; restocks copy
# - (bonus) reservation + notify via Observer
