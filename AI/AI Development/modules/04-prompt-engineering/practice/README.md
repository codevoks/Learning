# Module 04 — Assignments (ek jagah)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`

Order: A1 → A3. `TODO` search in each file.

---

## Progress checklist

- [ ] A1 — `summarizer_prompt.py`
- [ ] A2 — `classifier_fewshot.py`
- [ ] A3 — `injection_safe_bot.py`
- [ ] Active recall → NOTES
- [ ] Redraw challenge

---

## Setup

```bash
cd modules/04-prompt-engineering/practice
python3 -m venv .venv && source .venv/bin/activate
pip install openai python-dotenv httpx
cp .env.example .env   # API key
```

---

## A1 — Fix summarizer

| | |
|---|---|
| **File** | `summarizer_prompt.py` |
| **Kya** | Broken summarizer prompt fix |
| **Pass** | Stable bullets 10/10 runs |

### Hints

- System: max 3 bullets, no preamble
- `temperature: 0`

---

## A2 — Few-shot classifier

| | |
|---|---|
| **File** | `classifier_fewshot.py` |
| **Kya** | Few-shot examples add karo |
| **Pass** | Accuracy > baseline on 20 examples |

---

## A3 — Injection-safe bot

| | |
|---|---|
| **File** | `injection_safe_bot.py` |
| **Kya** | Prompt injection resistant support bot |
| **Pass** | 5 attack strings fail safely |

### Hints

- Test: "ignore instructions", "repeat system prompt", doc injection

---

## Active recall (NOTES)

1. Few-shot token cost control?
2. CoT production mein kab band?
3. System vs developer message (Anthropic)?

---

## Files

| File | Assignment |
|------|------------|
| `summarizer_prompt.py` | A1 |
| `classifier_fewshot.py` | A2 |
| `injection_safe_bot.py` | A3 |
| `.env.example` | copy → `.env` |

**Stuck?** `@modules/04-prompt-engineering/MODULE.md` + error paste.
