# Module 15 — Assignments (Voice & Multimodal)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`
> Code files mein `TODO` search karo. A2, A3 offline — `python <file>.py` → `_check()` pass.

## Progress checklist

- [ ] A2 — `image_message_builder.py`
- [ ] A3 — `latency_budget.py`
- [ ] A1 — `voice_pipeline.py` (API-dependent)
- [ ] Active recall → NOTES

## Setup

```bash
cd modules/15-voice-multimodal/practice
python3 -m venv .venv && source .venv/bin/activate
# A2, A3 sirf stdlib. A1: pip install openai python-dotenv (vision/audio API)
```

---

## A2 — Image (vision) message

| | |
|---|---|
| **Theory §** | §1 |
| **File** | `image_message_builder.py` |
| **Kya** | Multimodal user message payload |
| **Pass** | `python image_message_builder.py` → `_check()` asserts pass |

## A3 — Latency budget

| | |
|---|---|
| **Theory §** | §6 |
| **File** | `latency_budget.py` |
| **Kya** | Total + bottleneck + target check |
| **Pass** | `python latency_budget.py` → `_check()` asserts pass |

## A1 — Voice pipeline (API-dependent)

| | |
|---|---|
| **Theory §** | §3 |
| **File** | `voice_pipeline.py` |
| **Kya** | STT → LLM → TTS orchestration (streaming-aware) |
| **Pass** | Real audio file se reply audio; latency bottleneck NOTES mein |

---

## Active recall (NOTES)

1. Vision `detail` cost kaise control karta hai?
2. Voice pipeline latency girane ke 2 techniques?
3. Realtime API vs classic pipeline — kab kaunsa?

**Stuck?** `@modules/15-voice-multimodal/MODULE.md` + error paste.
