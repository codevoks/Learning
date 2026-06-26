# Practice — Module 02

1. Read theory in `../MODULE.md`
2. Redis running: `docker compose up -d` from repo root or 00a practice
3. Complete stubs below

## Setup

```bash
cd modules/02-llm-infra/practice
python3 -m venv .venv
source .venv/bin/activate
pip install redis httpx python-dotenv
```

## Files

| File | Assignment |
|------|------------|
| `rate_limiter.py` | A1 |
| `exact_cache.py` | A2 |
| `circuit_breaker.py` | A3 |
| `request_middleware.py` | A4 |
