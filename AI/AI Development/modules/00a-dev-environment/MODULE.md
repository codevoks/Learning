# Module 00a — Dev Environment

> **Padho**: Isi file mein **Theory** — bahar mat jao.  
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`  
> **Nav**: Start here · Next → [Module 00b](../00b-python-async/MODULE.md)

## At a glance

| | |
|---|---|
| Prerequisites | Mac terminal basics |
| Duration | ~2–3 sessions |
| Project? | No |
| Exit test | `docker compose up` healthy + venv + `.env` load |

## Visual map

```mermaid
flowchart LR
    Mac["Mac (host)"] --> Docker["Docker Compose"]
    Docker --> PG["Postgres :5432"]
    Docker --> Redis["Redis :6379"]
    Docker -.-> API["FastAPI :8000 (baad mein)"]
```

```
Mac
 └── docker compose up
       ├── postgres + volume (data bachta hai)
       ├── redis
       └── (future) FastAPI app
```

**Mental model**: Mac pe code likho, services containers mein — ek command se poora stack.

**Redraw challenge**: Bina dekhe yahi diagram draw karo.

---

## Read order

1. Visual map → 2. **Theory** (neeche) → 3. **Practice** → 4. Chat agar doubt → 5. NOTES

---

## Theory

### 1. Problem: "Mere machine pe kaam kyu nahi chal raha?"

Tumne Zapier clone, matching engine, Rootstock — sab mein **same stack** chahiye tha: Postgres, Redis, workers.  
Agar har developer apni machine pe alag version install kare → **"works on my machine"** bug.

**Docker** = lightweight box jisme service + uski dependencies packaged hain.  
Tumhari machine pe **Docker Engine** chalta hai; uske andar **containers** chalte hain — alag processes, shared OS kernel.

| Bina Docker | Docker ke saath |
|-------------|-----------------|
| `brew install postgresql@16` — version fight | `image: postgres:16` — sab same |
| Redis alag install | `image: redis:7` — ek line |
| Cleanup messy | `docker compose down` |

**Tera hook**: Production mein K8s pods bhi isi idea pe hain — local pe Compose = chhota K8s.

---

### 2. Docker Compose — ek file, poora stack

`docker-compose.yml` = **declarative config**: kaunsi services, kaunse ports, kaunse env vars.

```yaml
services:
  postgres:
    image: postgres:16
    ports:
      - "5432:5432"    # host:container
    environment:
      POSTGRES_PASSWORD: devpass
      POSTGRES_DB: aidev
    volumes:
      - pgdata:/var/lib/postgresql/data

  redis:
    image: redis:7
    ports:
      - "6379:6379"

volumes:
  pgdata:   # named volume — container delete pe bhi data bachta hai
```

**Port mapping `5432:5432`**:  
- Left = tumhari Mac (`localhost:5432`)  
- Right = container ke andar  
- FastAPI baad mein `postgresql://localhost:5432/aidev` se connect karega

**Volume kyun?**  
Container restart/delete pe **andar ka filesystem gayab** ho sakta hai. Postgres data disk pe volume mein rehta hai — warna har `down` pe DB empty.  
*(Active recall Q1 ka jawab yahi hai.)*

**Commands yaad rakho:**

```bash
docker compose up -d      # background mein start
docker compose ps         # healthy?
docker compose logs postgres
docker compose down       # stop (volume data rehta hai)
docker compose down -v    # volumes bhi delete — careful!
```

---

### 3. Postgres container — tumhara data home

Postgres = **relational DB** — tables, SQL, ACID. Tum Prisma se pehle hi use kar chuke ho.

Is module mein goal: **local DB chal rahi ho** taaki baad mein RAG (pgvector), gateway logs, etc. same Postgres pe.

**Connection string format:**

```
postgresql://USER:PASSWORD@HOST:PORT/DATABASE
postgresql://postgres:devpass@localhost:5432/aidev
```

**Quick test** (container up ke baad):

```bash
docker compose exec postgres psql -U postgres -d aidev -c "SELECT 1;"
```

Agar `1` aaya — DB live hai.

**Ek table bana ke feel lo:**

```sql
CREATE TABLE health_check (
  id SERIAL PRIMARY KEY,
  ok BOOLEAN NOT NULL,
  checked_at TIMESTAMPTZ DEFAULT NOW()
);
INSERT INTO health_check (ok) VALUES (true);
```

Yeh wahi mental model hai — Prisma migration se pehle raw SQL samajhna useful hai.

---

### 4. Redis container — fast memory store

Redis = **in-memory** key-value store. Disk optional. Bahut fast.

| Use case (tumhare projects mein) | Redis kya karega |
|----------------------------------|------------------|
| Matching engine Pub/Sub | Channels, real-time |
| LLM semantic cache (baad mein) | `SET key value EX 3600` |
| Rate limiting counters | `INCR user:123:requests` |
| Session / budget tracking | TTL keys |

**Postgres vs Redis — alag kyun?** *(Active recall Q2)*  
- Postgres = durable, complex queries, source of truth  
- Redis = speed, ephemeral OK, simple ops  
- Gateway mein **dono**: Postgres = billing logs; Redis = cache + rate limit

**Quick test:**

```bash
docker compose exec redis redis-cli ping
# PONG

docker compose exec redis redis-cli SET test "hello"
docker compose exec redis redis-cli GET test
# "hello"
```

---

### 5. Python virtual environment (venv)

System Python mein global `pip install` = **version hell** (project A ko FastAPI 0.100 chahiye, B ko 0.115).

**venv** = project-specific Python + packages isolated folder.

```bash
cd modules/00a-dev-environment/practice
python3 -m venv .venv
source .venv/bin/activate    # prompt mein (.venv) dikhega
pip install fastapi uvicorn httpx python-dotenv
python -c "import fastapi; print('ok')"
deactivate                   # band karna
```

**`requirements.txt`** — freeze karke team same versions use kare:

```bash
pip freeze > requirements.txt
pip install -r requirements.txt
```

**Node parallel**: `venv` ≈ per-project `node_modules`; `requirements.txt` ≈ `package-lock.json`.

---

### 6. `.env` — secrets kabhi git mein nahi

API keys, DB passwords **code mein hardcode nahi**.  
`.env` file local machine pe — **`.gitignore` mein add**.

```
# .env.example (yeh GIT mein jaata hai — template, fake values)
DATABASE_URL=postgresql://postgres:devpass@localhost:5432/aidev
REDIS_URL=redis://localhost:6379
OPENAI_API_KEY=sk-your-key-here

# .env (yeh GIT mein NAHI — asli values)
```

**python-dotenv** load karta hai:

```python
from dotenv import load_dotenv
import os

load_dotenv()
db_url = os.getenv("DATABASE_URL")
```

*(Active recall Q3: `.env` git mein kyun nahi — leak = compromised keys, history se delete mushkil.)*

---

### 7. Folder layout — aage ke projects ke liye

```
AI Development/
  docker-compose.yml          # root pe — poora stack
  .env.example
  modules/
    00a-dev-environment/
      MODULE.md               # yeh file
      NOTES.md                # tumhari learnings
      practice/               # code yahan
  services/                   # baad mein
    llm-gateway/              # FastAPI app
```

Abhi `practice/` mein 00a exercises. Baad mein `services/` mein real projects.

---

## Practice

> **Saare assignments ek jagah**: [`practice/README.md`](practice/README.md) — problem statements, instructions, pass criteria.  
> Code **tum** likhoge Cursor mein. Stubs `practice/` mein hain (`TODO` search).  
> Stuck? Chat: `@modules/00a-dev-environment/MODULE.md` + error paste karo.

| # | File | Kya karna hai | Pass when |
|---|------|---------------|-----------|
| A1 | `practice/docker-compose.yml` | `TODO` comments complete karo | `docker compose up -d` → both healthy |
| A2 | `practice/setup.sh` or manual | venv + deps install | `import fastapi` works |
| A3 | `practice/check_env.py` | `TODO` complete — load `.env` | Prints masked DATABASE_URL |
| A4 | `NOTES.md` | Node vs Python layout — 5 bullets | Coach approve / self-check |

### A1 hints

- `healthcheck` optional but production mindset: `pg_isready`, `redis-cli ping`
- Ports `5432` aur `6379` already Mac pe use ho rahe hon toh mapping change karo

### A3 hints

- Password print mat karo full — `devpass` → `dev***` mask karo

---

## Active recall (khud jawab likho NOTES mein)

1. Docker volume Postgres ke liye kyun chahiye?
2. Redis aur Postgres gateway mein alag kyun?
3. `.env` git mein kyun nahi jaata?

**Chat drill** (optional): "Module 00a recall — 3 questions test karo"

---

## Progress checklist

- [ ] Theory Section 1–7 padh liya
- [ ] Redraw challenge kiya
- [ ] Practice A1–A4 pass
- [ ] Active recall NOTES mein likha
- [ ] NOTES session log updated

---

## Optional appendix (zarurat ho tab)

- [Docker Compose docs](https://docs.docker.com/compose/) — deep dive only
