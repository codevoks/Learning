"""Tic-Tac-Toe — LLD starter stub. Run: python solution.py"""
from __future__ import annotations


class Board:
    def __init__(self, n: int = 3):
        self.n = n
        self.grid = [["" for _ in range(n)] for _ in range(n)]
    def place(self, r: int, c: int, mark: str) -> bool:
        # TODO: place if empty + in-bounds, return success
        raise NotImplementedError
    def has_won(self, mark: str) -> bool:
        # TODO: any full row/col/diagonal of `mark`
        raise NotImplementedError
    def is_full(self) -> bool:
        return all(cell for row in self.grid for cell in row)


class Game:
    def __init__(self, n: int = 3, marks=("X", "O")):
        self.board = Board(n)
        self.marks = marks
        self.turn = 0
    def move(self, r: int, c: int) -> str:
        mark = self.marks[self.turn % 2]
        # TODO: place; if win return f"{mark} wins"; if full return "draw"; else "next"
        raise NotImplementedError


if __name__ == "__main__":
    g = Game(3)
    seq = [(0,0),(1,0),(0,1),(1,1),(0,2)]  # X wins top row
    res = ""
    for r,c in seq: res = g.move(r,c)
    assert res == "X wins", res
    print("PASS")

# PASSING CRITERIA:
# - correct win/draw/invalid detection for NxN
# - alternating turns enforced
# - adding a new WinStrategy needs no Board rewrite (OCP)
