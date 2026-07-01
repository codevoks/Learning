"""A2 — Minimal agent loop (framework ke bina).

`python agent_loop.py` → `_check()` ke asserts pass. Harness fake `llm` deta hai
(taaki offline test ho) — tumhe LOOP banana hai. Harness edit mat karo.

Contract:
- run_agent(task, llm, tools, max_steps=10) -> str:
    scratchpad = [task] se shuru.
    Har step: decision = llm(scratchpad).
      * decision["final"] hai → wahi string return karo (stop: kaam ho gaya).
      * warna decision["tool"] ko tools[name](**decision["args"]) se chalao,
        result scratchpad mein append karo, aur loop continue.
    max_steps khatam → "stopped: max steps reached" (ya "max" wala message) return.
`llm` ek function hai jo scratchpad leke {"tool":name,"args":{}} ya {"final":text} deta hai.
`tools` = {name: fn}.
"""


def run_agent(task: str, llm, tools: dict, max_steps: int = 10) -> str:
    # TODO: think → act → observe loop + stop conditions
    raise NotImplementedError


# ---------------------------------------------------------------------------
# PASS CRITERIA (edit mat karo)
# ---------------------------------------------------------------------------
def _check() -> None:
    tools = {"add": lambda a, b: a + b}

    # Normal path: pehle tool, phir final answer
    seq = iter([{"tool": "add", "args": {"a": 2, "b": 3}}, {"final": "The answer is 5"}])
    out = run_agent("2+3?", lambda scratch: next(seq), tools, max_steps=10)
    assert "5" in out, f"final answer milna chahiye, mila: {out!r}"

    # Max-steps guard: llm hamesha tool maangta hai → loop rukna chahiye
    calls = {"n": 0}
    def counting_add(a, b):
        calls["n"] += 1
        return a + b
    out2 = run_agent(
        "loop forever",
        lambda scratch: {"tool": "add", "args": {"a": 1, "b": 1}},
        {"add": counting_add},
        max_steps=3,
    )
    assert calls["n"] == 3, f"tool max_steps(3) baar chalna chahiye, chala {calls['n']}"
    assert "stop" in out2.lower() or "max" in out2.lower(), "max-steps pe stop message"
    print("OK: agent_loop A2 pass — tool exec + final + max-steps guard verified")


if __name__ == "__main__":
    _check()
