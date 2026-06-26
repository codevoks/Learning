"""Tic-Tac-Toe — machine-coding stub (target 30 min). Run: python solution.py"""


class TicTacToe:
    def __init__(self, n: int = 3):
        self.n = n
        self.grid = [["" for _ in range(n)] for _ in range(n)]
        self.marks = ("X", "O")
        self.turn = 0
    def move(self, r: int, c: int) -> str:
        # TODO: validate; place current mark; return "X wins"/"O wins"/"draw"/"ok"/"invalid"
        raise NotImplementedError
    def _wins(self, mark: str) -> bool:
        # TODO: any full row/col/diagonal
        raise NotImplementedError


if __name__ == "__main__":
    g = TicTacToe(3)
    for (r, c), exp in [((0,0),"ok"),((1,0),"ok"),((0,1),"ok"),((1,1),"ok"),((0,2),"X wins")]:
        assert g.move(r, c) == exp, (r, c)
    print("PASS")

# PASSING CRITERIA: correct win/draw/invalid for NxN, alternating turns.
