# Module 00a — Assignments (ek jagah)

> **Theory**: `../MODULE.md` — **pehle §0** (terminal / Docker / YAML symbols), phir session table follow karo.  
> **Code**: isi folder mein  
> **Apni learnings**: `../NOTES.md`  
> **Doubt / review**: Cursor chat `@MODULE.md`

Pehle **§0 + theory section** padho (MODULE mein Theory § column dekho), phir **order mein** A1 → A4 karo.

---

## Progress checklist

- [ ] A1 — `docker-compose.yml`
- [ ] A2 — venv + packages
- [ ] A3 — `check_env.py`
- [ ] A4 — `NOTES.md` bullets
- [ ] Active recall — `../NOTES.md` mein jawab
- [ ] Redraw challenge — visual map bina dekhe

---

## A1 — Docker Compose

| | |
|---|---|
| **File** | `docker-compose.yml` |
| **Kya karna hai** | Saare `# TODO` comments complete karo |
| **Pass when** | `docker compose up -d` → postgres + redis dono running |

### Instructions

1. File kholo → `TODO` search karo (`Cmd+F`)
2. Complete karo: ports, environment vars, postgres volume mount, bottom pe `pgdata` declare
3. Syntax check: `docker compose config`
4. Start: `docker compose up -d`
5. Verify:

```bash
docker compose ps
docker compose exec postgres psql -U postgres -d aidev -c "SELECT 1;"
docker compose exec redis redis-cli ping   # PONG
```

### Hints

- `healthcheck` optional hai — skip ok for pass
- Port `5432` / `6379` Mac pe already use ho rahe hon toh mapping change karo
- `POSTGRES_DB: aidev` — sirf database ka naam (AI Development ka short name)

---

## A2 — Python venv

| | |
|---|---|
| **File** | manual (koi stub nahi) — optional: `setup.sh` khud bana sakte ho |
| **Kya karna hai** | Project-specific Python env + dependencies install |
| **Pass when** | `import fastapi` error ke bina chale |

### Instructions

```bash
cd modules/00a-dev-environment/practice
python3 -m venv .venv
source .venv/bin/activate          # prompt mein (.venv) dikhe
pip install fastapi uvicorn httpx python-dotenv
python -c "import fastapi; print('ok')"
pip freeze > requirements.txt      # lock file jaisa
```

### Pass check

- `ok` print ho
- `requirements.txt` ban jaye
- `pip show fastapi` → location `.venv/...` ke andar ho (system nahi)

---

## A3 — Load `.env`

| | |
|---|---|
| **File** | `check_env.py` |
| **Kya karna hai** | Saare `# TODO` complete karo |
| **Pass when** | Script chalao → masked `DATABASE_URL` print ho (password full mat dikhe) |

### Instructions

1. `.env` banao: `cp .env.example .env`
2. `.env` mein values apne compose se match karo (password `abc` agar wahi use kiya)
3. `check_env.py` kholo → har `TODO` complete karo:
   - `load_dotenv` + `os` import
   - `load_dotenv()` call
   - `mask_url()` — password hide karo
   - `DATABASE_URL` read karke print karo
4. Run (venv active):

```bash
python check_env.py
```

### Hints

- URL missing ho toh `"missing"` print karo
- Mask example: `devpass` → `dev***` (pehle 3–4 chars + `***`)
- `.env` git mein nahi jaata — `.env.example` template hai

---

## A4 — NOTES (written)

| | |
|---|---|
| **File** | `../NOTES.md` |
| **Kya karna hai** | **Node vs Python project layout** — 5 bullets likho |
| **Pass when** | Khud check / coach approve |

### Prompt (copy as heading)

> Node (package.json, node_modules) vs Python (venv, requirements.txt) — 5 differences ya parallels

Example angles (khud apne words mein): deps file, install folder, lock file, secrets, monorepo feel.

---

## Active recall (written — `../NOTES.md`)

MODULE theory ke baad `## Active recall answers` mein likho:

1. Docker volume Postgres ke liye kyun chahiye?
2. Redis aur Postgres gateway mein alag kyun?
3. `.env` git mein kyun nahi jaata?

---

## Files is folder mein

| File | Role |
|------|------|
| `docker-compose.yml` | A1 — edit karo |
| `check_env.py` | A3 — edit karo |
| `.env.example` | template — copy → `.env` |
| `.env` | local secrets — **gitignore** |
| `requirements.txt` | A2 ke baad `pip freeze` se banta hai |

---

## Stuck?

Chat mein: `@modules/00a-dev-environment/MODULE.md` + error/output paste. Poora solution mat maango — hints milenge.
