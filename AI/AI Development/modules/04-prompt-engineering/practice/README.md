# Module 04 — Assignments (ek jagah)

> **Theory**: `../MODULE.md` (textbook — §0 terms pehle, session table follow karo)  
> **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`  
> **Standard**: `@MODULE-TEACHING-STANDARD.md` — cheat sheet nahi; har theory § ke baad yahan ka assignment

**Read order:** MODULE.md session table ke hisaab se — Session 2 pe A1, Session 3 pe A2, Session 4 pe A3. Theory skip mat karo.

Order: A1 → A3. Har file mein `TODO` search karo. Pehle MODULE.md § end-to-end walkthrough chalao, phir stubs complete karo.

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
| **Theory §** | §1, §2 |
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
| **Theory §** | §3 |
| **File** | `classifier_fewshot.py` |
| **Kya** | Few-shot examples add karo |
| **Pass** | Accuracy > baseline on 20 examples |

---

## A3 — Injection-safe bot

| | |
|---|---|
| **Theory §** | §5, §6 |
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
