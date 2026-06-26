# Practice — Module 00a

1. Read theory in `../MODULE.md`
2. Complete files here in Cursor
3. Run commands from MODULE Theory sections

## A1

```bash
cd modules/00a-dev-environment/practice
docker compose up -d
docker compose ps
```

## A2

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install fastapi uvicorn httpx python-dotenv
```

## A3

```bash
cp .env.example .env
python check_env.py
```

Copy `.env.example` to repo root `.env` when you wire the full stack later.
