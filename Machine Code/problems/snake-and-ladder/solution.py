"""Snake & Ladder — machine-coding stub (target 30 min). Run: python solution.py"""


class Game:
    def __init__(self, size: int, jumps: dict[int, int], players: list[str]):
        self.size = size
        self.jumps = jumps
        self.pos = {p: 0 for p in players}
    def move(self, player: str, dice: int) -> bool:
        # TODO: new = pos+dice; if new>size: stay; else apply jump; update; return True if new==size
        raise NotImplementedError


if __name__ == "__main__":
    g = Game(20, {3: 11, 17: 4}, ["P1"])
    assert g.move("P1", 3) is False and g.pos["P1"] == 11   # ladder
    assert g.move("P1", 6) is False and g.pos["P1"] == 17 - 13  # 17->4 snake
    print("PASS")

# PASSING CRITERIA: ladders/snakes applied, no overshoot, win on reaching size, multiplayer.
