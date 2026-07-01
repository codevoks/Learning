"""A2 — Grounding helpers: bounding-box center + point-inside.

`python grounding.py` → `_check()` ke asserts pass. Harness edit mat karo.

Contract (box = (x1, y1, x2, y2), top-left + bottom-right):
- center(box) -> (cx, cy): box ka center (reliable click target).
- point_in_box(point, box) -> bool: (px, py) box ke andar (boundary inclusive) hai?
"""


def center(box):
    # TODO: ((x1+x2)/2, (y1+y2)/2)
    raise NotImplementedError


def point_in_box(point, box) -> bool:
    # TODO: x1 <= px <= x2 and y1 <= py <= y2
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    assert center((0, 0, 10, 20)) == (5.0, 10.0), "center galat"
    assert center((4, 4, 4, 4)) == (4.0, 4.0), "point box → wahi point"

    assert point_in_box((5, 10), (0, 0, 10, 20)) is True, "andar ka point"
    assert point_in_box((15, 10), (0, 0, 10, 20)) is False, "bahar (x)"
    assert point_in_box((5, 25), (0, 0, 10, 20)) is False, "bahar (y)"
    assert point_in_box((0, 0), (0, 0, 10, 20)) is True, "boundary inclusive"
    assert point_in_box((10, 20), (0, 0, 10, 20)) is True, "boundary inclusive"
    print("OK: grounding A2 pass — bbox center + point-inside verified")


if __name__ == "__main__":
    _check()
