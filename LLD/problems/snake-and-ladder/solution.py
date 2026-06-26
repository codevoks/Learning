"""Snake & Ladder — LLD starter stub. Run: python solution.py"""
from __future__ import annotations
import random


class Board:
    def __init__(self, size: int, jumps: dict[int, int]):
        # jumps[start] = end  (snake if end<start, ladder if end>start)
        self.size = size
        self.jumps = jumps
    def resolve(self, pos: int) -> int:
        # TODO: apply jump if pos has one
        raise NotImplementedError


class Game:
    def __init__(self, board: Board, players: list[str], seed: int | None = None):
        self.board = board
        self.players = players
        self.pos = {p: 0 for p in players}
        self.rng = random.Random(seed)
    def roll(self) -> int:
        return self.rng.randint(1, 6)
    def play_turn(self, player: str, dice: int) -> bool:
        # TODO: move player by dice (no overshoot past size), resolve jumps,
        # return True if player won (reached size)
        raise NotImplementedError


if __name__ == "__main__":
    b = Board(30, {3: 22, 27: 5})  # ladder 3->22, snake 27->5
    g = Game(b, ["P1"])
    g.play_turn("P1", 3)
    assert g.pos["P1"] == 22, g.pos
    print("PASS")

# PASSING CRITERIA:
# - ladders/snakes applied correctly; no overshoot past final cell
# - win detection on reaching last cell
# - supports multiple players
