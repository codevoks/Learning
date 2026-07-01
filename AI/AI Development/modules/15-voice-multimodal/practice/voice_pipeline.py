"""A1 — Voice agent pipeline: STT → LLM → TTS orchestration (streaming-aware).

Yeh assignment API-dependent hai (OpenAI audio + chat) — iska koi offline `_check()`
nahi. Contract follow karke implement karo, phir ek real audio file se test karo.

Contract:
- run_voice_turn(audio_path) -> bytes: audio file ka path lo, aur:
    1. STT: audio → text (whisper)
    2. LLM: text → jawab text (chat)  — bonus: streaming se sentences nikaalo
    3. TTS: jawab text → audio bytes
  Return: reply audio bytes.
- Bonus (§3): LLM output ko stream karke, jaise sentence bane, use turant TTS ko
  bhejo — "time to first audio" kam karne ke liye. Latency ko `latency_budget.py`
  ki tarah measure karo aur NOTES mein likho kaunsa hop bottleneck tha.

Streaming/latency measurement hi is assignment ka asli seekhne wala hissa hai —
sirf teen calls chain karna aasan hai, unhe fast banana asli kaam.
"""


def run_voice_turn(audio_path: str) -> bytes:
    # TODO: STT (whisper) → LLM (chat, ideally streaming) → TTS → reply audio bytes
    raise NotImplementedError


if __name__ == "__main__":
    print("A1 ko real audio file + API keys ke saath test karo (README dekho).")
    print("Latency har hop ki measure karo — bottleneck NOTES mein likho.")
