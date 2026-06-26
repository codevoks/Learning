"""Chess — LLD starter stub. Run: python solution.py"""
from __future__ import annotations
from abc import ABC, abstractmethod


class Piece(ABC):
    def __init__(self, color: str):
        self.color = color
    @abstractmethod
    def is_valid_move(self, board: "Board", fr: tuple[int,int], to: tuple[int,int]) -> bool: ...


class Rook(Piece):
    def is_valid_move(self, board, fr, to):
        # TODO: same row or same col AND path clear
        raise NotImplementedError


class Knight(Piece):
    def is_valid_move(self, board, fr, to):
        # TODO: L-shape (2,1)
        raise NotImplementedError


class Board:
    def __init__(self):
        self.grid: dict[tuple[int,int], Piece] = {}
    def place(self, pos, piece): self.grid[pos] = piece
    def piece_at(self, pos): return self.grid.get(pos)
    def is_path_clear(self, fr, to) -> bool:
        # TODO: for sliding pieces, ensure no piece between fr and to
        raise NotImplementedError


if __name__ == "__main__":
    b = Board()
    b.place((0,0), Rook("white"))
    assert b.piece_at((0,0)).is_valid_move(b, (0,0), (0,5)) is True
    assert Knight("white").is_valid_move(b, (0,0), (1,2)) is True
    print("PASS")

# PASSING CRITERIA:
# - each piece validates its own legal moves (polymorphism)
# - sliding pieces respect blocked paths
# - adding a new piece type needs no change to Board/Game (OCP)
