# Practice — Module 01

1. Read theory in `../MODULE.md`
2. Complete files here in Cursor
3. Set `OPENAI_API_KEY` or `ANTHROPIC_API_KEY` in `.env`

## Setup

```bash
cd modules/01-llm-apis/practice
python3 -m venv .venv
source .venv/bin/activate
pip install fastapi uvicorn httpx python-dotenv openai
cp .env.example .env   # add your key
```

## A1 — chat_route.py

```bash
uvicorn chat_route:app --reload
curl -X POST http://localhost:8000/chat -H "Content-Type: application/json" -d '{"message":"Hello"}'
```

## A2 — stream_route.py

```bash
curl -N http://localhost:8000/chat/stream -H "Content-Type: application/json" -d '{"message":"Count to 5"}'
```

## A3 — cost_calculator.py

```bash
python cost_calculator.py
```

## A4 — context_trimmer.py

```bash
python context_trimmer.py
```
