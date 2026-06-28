# Module 00a — Dev Environment

> **Padho**: Isi file mein **Theory** — bahar mat jao.  
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`  
> **Nav**: Start here · Next → [Module 00b](../00b-python-async/MODULE.md)

> **Format**: Textbook — §0 pehle (terminal / Docker / YAML symbols from zero). `@MODULE-TEACHING-STANDARD.md`

## At a glance

| | |
|---|---|
| Prerequisites | Mac terminal basics — `cd`, `ls` aate hon |
| Duration | ~2–3 sessions (section-by-section, ek din poora mat karo) |
| Project? | No |
| Exit test | `docker compose up` healthy + venv + `.env` load |

## Read order (strict — mat chhodna)

| Session | Padho | Karo (Practice) |
|---------|-------|-----------------|
| 1 | **§0** Terminal + Docker + YAML symbols | Terminal try blocks §0 ke neeche |
| 2 | §1 Problem + §2 Docker Compose | **A1** start — `docker-compose.yml` TODO |
| 3 | §3 Postgres | **A1** complete — `psql SELECT 1` pass |
| 4 | §4 Redis | **A1** verify — `redis-cli ping` |
| 5 | §5 Python venv | **A2** — venv + `requirements.txt` |
| 6 | §6 `.env` secrets | **A3** — `check_env.py` |
| 7 | §7 Layout + active recall | **A4** NOTES + redraw challenge |

**Pehle §0, phir diagram.** Visual map neeche hai — Session 1 ke baad dekho.

---

## Learning hooks (optional — tera parallel)

| Concept | Tera parallel |
|---------|---------------|
| Docker container | Lightweight VM / isolated process — K8s pod ka chhota bhai |
| `docker compose up` | `docker-compose.yml` = infra-as-code — Terraform feel, local scale |
| Postgres volume | Persistent disk mount — EBS volume jaisa |
| Redis | In-memory cache — ElastiCache / Upstash brain |
| Python venv | `node_modules` per project — global `npm install -g` mat karo |
| `.env` | `.env.local` Next.js mein — git mein kabhi nahi |

---

## Theory

### §0. Terminal, Docker aur YAML — pehli baar (30 min)

Tum TS/Node se aaye ho — terminal use kiya hai, par **Docker aur YAML** pehli baar ho sakte hain. Is section ke baad har command aur `docker-compose.yml` line readable lagegi. **Diagram aur compose file se pehle yeh padho.**

#### 0.1 Terminal symbols — Mac pe kya matlab

| Symbol / command | Matlab |
|------------------|--------|
| `$` ya `%` | Prompt — yahan se command type karo (copy mat karo prompt ke saath) |
| `pwd` | **P**rint **w**orking **d**irectory — abhi kahan ho |
| `cd path/to/folder` | **C**hange **d**irectory — folder change |
| `cd ..` | Ek level up — parent folder |
| `ls` | **L**i**s**t files — current folder ki files |
| `ls -la` | Hidden files + details (`-l` long, `-a` all) |
| `# comment` | Shell mein `#` ke baad sab ignore — explanation ke liye |
| `\` line continue | Rare — long command break karna |
| `Ctrl+C` | Running process **stop** — server band |
| `Ctrl+D` | Shell exit / EOF |

**Path types:**

| Path | Example | Matlab |
|------|---------|--------|
| Relative | `practice/check_env.py` | Current folder se relative |
| Absolute | `/Users/vansh/.../practice` | Root `/` se poora rasta |
| `~` | `~/Desktop` | Home folder shortcut |
| `.` | `./docker-compose.yml` | Current directory |
| `..` | `../MODULE.md` | Parent directory |

**Terminal try (abhi karo):**

```bash
pwd
# /Users/vansh/Desktop/Code/Learning/AI/AI Development

cd modules/00a-dev-environment/practice
ls
# docker-compose.yml  check_env.py  README.md  ...

cd ../..
pwd
# wapas AI Development root (ya jahan se start kiya)
```

| Output | Matlab |
|--------|--------|
| `/Users/.../practice` | `cd` kaam kiya — ab practice folder mein ho |
| file list | `ls` ne folder contents dikhaye |
| wapas root path | `cd ../..` se do level up |

#### 0.2 Docker vocabulary — image vs container

Docker = **lightweight box** jisme service + dependencies packaged hain. Tumhari Mac pe **Docker Desktop** (Engine) chalta hai; uske andar **containers** chalte hain.

| Term | Analogy (Hinglish) | Technical matlab |
|------|-------------------|------------------|
| **Image** | APK / Docker image = recipe | Read-only template — `postgres:16` |
| **Container** | App instance running | Image ka running process |
| **Dockerfile** | Build recipe (baad mein) | Image kaise banega — is module mein nahi |
| **Volume** | External HDD attach | Data container ke bahar survive kare |
| **Port mapping** | `localhost:5432` → box ke andar 5432 | Host se container tak tunnel |
| **Compose** | Multi-service orchestrator | Ek YAML se postgres + redis + app |

**Commands preview (detail §2 mein):**

```bash
docker --version
# Docker version 27.x.x, build ...

docker compose version
# Docker Compose version v2.x.x
```

Agar `command not found` — Docker Desktop install karo, app open karo, whale icon green ho.

#### 0.3 YAML syntax — `docker-compose.yml` padhne se pehle

YAML = **indentation matters** — JSON jaisa `{` `}` nahi, spaces se nesting.

| Symbol | Matlab | JS/TS parallel |
|--------|--------|----------------|
| `key: value` | Key-value pair | `"key": "value"` |
| `- item` | List mein ek entry | array element |
| `2 spaces indent` | Nested block | object nesting |
| `# comment` | Ignore line | `// comment` |
| `"5432:5432"` | String (safe for ports) | same |
| `5432:5432` | Number bhi ho sakta — ports ke liye quotes safe |
| `|` multiline | Rare is module mein | template strings |

**Chhota example — samjho structure:**

```yaml
services:           # top-level key — kaunsi services
  postgres:         # service ka naam — tum choose karte ho
    image: postgres:16    # kaunsi image pull karni hai
    ports:
      - "5432:5432"       # list item — host:container
    environment:
      POSTGRES_PASSWORD: devpass   # env var container ke andar
```

| Line / symbol | Matlab |
|---------------|--------|
| `services:` | Sab services yahan declare |
| `postgres:` | Ek service — naam arbitrary (connection string mein host nahi, port use hoga) |
| `image: postgres:16` | Docker Hub se Postgres version 16 pull |
| `ports:` + `- "5432:5432"` | Mac `localhost:5432` → container port 5432 |
| `environment:` | Container ke andar env vars — `POSTGRES_*` Postgres image ke liye standard |
| Indent 2 spaces | `postgres:` ke andar sab indented — galat indent = parse error |

**Galat indent example (mat likho):**

```yaml
services:
postgres:    # ❌ YAML parse error — postgres services ke andar hona chahiye
  image: postgres:16
```

#### 0.4 Docker CLI — pehli commands

```bash
docker ps
# CONTAINER ID   IMAGE     COMMAND   CREATED   STATUS   PORTS   NAMES
# (empty agar kuch nahi chal raha — normal)

docker images | head -5
# REPOSITORY   TAG   IMAGE ID   CREATED   SIZE
# postgres     16    ...        ...       ...
```

| Command | Matlab |
|---------|--------|
| `docker ps` | Running containers — `-a` = stopped bhi |
| `docker images` | Local pe downloaded images |
| `docker compose up -d` | Compose file se start — `-d` = detached (background) |
| `docker compose down` | Stop + remove containers (volume data usually rehta) |

#### 0.5 §0 common errors

| Error message | Kyun | Fix |
|---------------|------|-----|
| `command not found: docker` | Docker Desktop install nahi / PATH | Docker Desktop install + open |
| `Cannot connect to the Docker daemon` | Engine nahi chal raha | Docker Desktop start karo |
| `yaml: line X: mapping values are not allowed` | Indent galat / colon space missing | 2-space indent check; `key: value` mein space after `:` |
| `cd: no such file or directory` | Galat path | `pwd` + `ls` se confirm karo |
| `permission denied` | File execute permission | `chmod +x script.sh` ya `python script.py` use karo |

#### §0 checkpoint (khud jawab — NOTES mein optional)

1. Image aur container mein farq ek line mein?
2. YAML mein nesting kaise batata hai — `{` ya spaces?
3. `5432:5432` port mapping mein left side kiska port hai — Mac ya container?

**§0 done?** Ab §1 — problem samjho, phir Session 2 pe visual map dekho.

---

## Visual map (§0 ke baad — ab padho)

```mermaid
flowchart LR
    Mac["Mac (host)"] --> Docker["Docker Compose"]
    Docker --> PG["Postgres :5432"]
    Docker --> Redis["Redis :6379"]
    Docker -.-> API["FastAPI :8000 (baad mein)"]
```

```
Mac (tumhara code editor + terminal)
 └── docker compose up
       ├── postgres + volume pgdata (data restart pe bachta hai)
       ├── redis (in-memory)
       └── (future) FastAPI app container
```

**Mental model**: Mac pe code likho, databases **containers** mein — ek command se poora local stack. Production mein yahi idea K8s pods pe scale hota hai.

**Redraw challenge**: Bina dekhe upar wala ASCII diagram draw karo — Mac → compose → postgres/redis.

---

### §1. Problem — "Mere machine pe kyu nahi chal raha?"

**Problem kya hai:** Tumne Zapier clone, matching engine, Rootstock — sab mein **same stack** chahiye: Postgres, Redis, baad mein workers. Agar har developer apni machine pe alag version install kare (`brew install postgresql@15` vs `@16`), toh **"works on my machine"** bug aata hai — CI pass, tumhare laptop pe fail.

**Solution brain:** Environment **declare** karo ek file mein; sab `docker compose up` se same images pull karein.

| Bina Docker | Docker ke saath |
|-------------|-----------------|
| `brew install postgresql@16` — version fight | `image: postgres:16` — team same |
| Redis alag install, config alag | `image: redis:7` — ek line |
| Uninstall/cleanup messy | `docker compose down` |
| New teammate = 2 ghante setup | `git clone` + `compose up` |

**Tera hook:** Local Compose = chhota **Kubernetes** — same "declarative infra" muscle, bina cluster ke.

> **→ Practice A1** (start): `practice/docker-compose.yml` kholo — ab services samajh aaengi.

---

### §2. Docker Compose — ek file, poora stack

**Problem kya hai:** Postgres aur Redis alag-alag install karna = do moving parts, do version stories. Compose ek **YAML file** mein poora stack define karta hai.

`docker-compose.yml` = **declarative config**: kaunsi services, ports, env vars, volumes.

```yaml
services:
  postgres:
    image: postgres:16
    ports:
      - "5432:5432"
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
  pgdata:
```

| Line / symbol | Matlab |
|---------------|--------|
| `services:` | Compose file ka main block |
| `postgres:` / `redis:` | Service names — `docker compose logs postgres` mein use |
| `image: postgres:16` | Official Postgres image, tag 16 |
| `"5432:5432"` | **Host:Container** — Mac `localhost:5432` → Postgres inside |
| `POSTGRES_PASSWORD` | Superuser password — dev mein simple; prod mein strong + secret |
| `POSTGRES_DB` | Database create on first start — naam `aidev` |
| `volumes:` (service) | Mount path container ke andar |
| `/var/lib/postgresql/data` | Postgres data directory — yahan tables disk pe |
| `pgdata:` (bottom) | **Named volume** — Docker manage karta hai |
| `redis:7` | Redis major version 7 |

**Port mapping flow:**

```
1. Tumhari app (Mac) → localhost:5432
2. Docker port forward → container :5432
3. Postgres process container ke andar sun raha hai
```

**Commands — har ek try karo (A1 ke baad):**

```bash
cd modules/00a-dev-environment/practice
docker compose config          # YAML valid? — errors yahan dikhenge
docker compose up -d           # background start
docker compose ps              # STATUS column — running/healthy
docker compose logs postgres   # last lines — errors debug
docker compose down            # stop — volume data rehta hai
docker compose down -v         # ⚠️ volumes delete — DB empty ho jayega
```

**Expected `docker compose ps` (pass feel):**

```
NAME                IMAGE         STATUS          PORTS
practice-postgres-1 postgres:16   Up (healthy)    0.0.0.0:5432->5432/tcp
practice-redis-1    redis:7       Up              0.0.0.0:6379->6379/tcp
```

| Step | Command | Pass signal |
|------|---------|-------------|
| 1 | `docker compose config` | No error, services listed |
| 2 | `docker compose up -d` | Pull + Created + Started |
| 3 | `docker compose ps` | Both `Up` |

#### §2 common errors

| Error message | Kyun | Fix |
|---------------|------|-----|
| `port is already allocated` | Mac pe Postgres/Redis already chal raha | `brew services stop postgresql` ya mapping `"5433:5432"` |
| `service "postgres" refers to undefined volume` | `volumes: pgdata:` bottom mein missing | Bottom `volumes:` block add |
| `pull access denied` | Image name typo | `postgres:16` spelling check |
| `dependency failed to start` | Bad env / corrupt volume | `docker compose logs postgres`; worst case `down -v` (data loss) |

> **→ Practice A1** (pass): `docker compose up -d` → postgres + redis dono `Up`.

---

### §3. Postgres container — tumhara data home

**Problem kya hai:** Baad mein RAG (pgvector), gateway logs, user data — sab **relational DB** chahiye. Local Postgres bina install ke container se chalao.

Postgres = **relational DB** — tables, SQL, ACID. Prisma use kiya hai — yahan raw connection samjho pehle.

**Volume kyun?** Container delete/restart pe **andar ka filesystem ephemeral** ho sakta hai. Bina volume: har `down` pe DB empty. Volume = data Docker ke managed disk pe.

**Connection string format:**

```
postgresql://USER:PASSWORD@HOST:PORT/DATABASE
postgresql://postgres:devpass@localhost:5432/aidev
```

| Part | Is example mein |
|------|-----------------|
| `postgresql://` | Scheme — driver prefix |
| `postgres` | Username (default superuser) |
| `devpass` | Password — compose `POSTGRES_PASSWORD` se match |
| `localhost` | Host — Mac se container tak mapped port |
| `5432` | Port |
| `aidev` | Database name — `POSTGRES_DB` |

**Quick test (container up ke baad):**

```bash
docker compose exec postgres psql -U postgres -d aidev -c "SELECT 1;"
```

Expected:

```
 ?column?
----------
        1
(1 row)
```

| Part | Matlab |
|------|--------|
| `docker compose exec` | Running container ke andar command |
| `postgres` | Service name |
| `psql` | Postgres CLI |
| `-U postgres` | User |
| `-d aidev` | Database |
| `-c "SELECT 1;"` | One-shot SQL |

**Ek table — feel ke liye:**

```sql
CREATE TABLE health_check (
  id SERIAL PRIMARY KEY,
  ok BOOLEAN NOT NULL,
  checked_at TIMESTAMPTZ DEFAULT NOW()
);
INSERT INTO health_check (ok) VALUES (true);
SELECT * FROM health_check;
```

| Line / symbol | Matlab |
|---------------|--------|
| `SERIAL PRIMARY KEY` | Auto-increment ID |
| `BOOLEAN NOT NULL` | true/false required |
| `TIMESTAMPTZ DEFAULT NOW()` | Timestamp with timezone, default abhi |
| `INSERT ... VALUES` | Ek row add |

Run via:

```bash
docker compose exec postgres psql -U postgres -d aidev -c "CREATE TABLE IF NOT EXISTS health_check (id SERIAL PRIMARY KEY, ok BOOLEAN NOT NULL); INSERT INTO health_check (ok) VALUES (true);"
```

#### §3 common errors

| Error message | Kyun | Fix |
|---------------|------|-----|
| `connection refused` on 5432 | Container down / wrong port | `docker compose ps` |
| `FATAL: password authentication failed` | `.env` password ≠ compose | Same password everywhere |
| `database "aidev" does not exist` | `POSTGRES_DB` missing / typo | Compose env check |
| `role "postgres" does not exist` | Wrong `-U` | `-U postgres` default image |

> **→ Practice A1** (verify): `psql ... SELECT 1` → `1` row.

---

### §4. Redis container — fast memory store

**Problem kya hai:** Har cheez Postgres mein = slow for ephemeral data (rate limits, cache, pub/sub). Redis = **in-memory** key-value — microseconds.

| Use case (future projects) | Redis kya karega |
|----------------------------|------------------|
| Matching engine Pub/Sub | Channels, real-time |
| LLM semantic cache | `SET key value EX 3600` |
| Rate limiting | `INCR user:123:requests` |
| Session / budget | TTL keys auto-expire |

**Postgres vs Redis — alag kyun?**

| | Postgres | Redis |
|---|----------|-------|
| Storage | Disk-first, durable | RAM-first |
| Queries | SQL, joins, complex | GET/SET, simple |
| Role | Source of truth | Speed / ephemeral OK |
| Gateway | Billing logs, users | Cache + rate limit |

**Quick test:**

```bash
docker compose exec redis redis-cli ping
# PONG

docker compose exec redis redis-cli SET test "hello"
# OK

docker compose exec redis redis-cli GET test
# "hello"
```

| Command | Expected | Matlab |
|---------|----------|--------|
| `ping` | `PONG` | Redis alive |
| `SET test "hello"` | `OK` | Key set |
| `GET test` | `"hello"` | Value read |

**Request flow (mental):**

```
1. App → redis-cli GET cache:key
2. Miss → Postgres / API call
3. App → SET cache:key EX 3600
```

#### §4 common errors

| Error message | Kyun | Fix |
|---------------|------|-----|
| `Could not connect to Redis` | Container down / wrong port | `docker compose ps`; `6379:6379` |
| `(error) NOAUTH` | Redis password set (humne nahi) | Default image — no password local |
| `OOM` rare local | Memory full | `docker compose restart redis` |

> **→ Practice A1** (final): `redis-cli ping` → `PONG`.

---

### §5. Python virtual environment (venv)

**Problem kya hai:** System Python mein global `pip install` = **version hell** — project A ko FastAPI 0.100, B ko 0.115. Node mein bhi global install avoid karte ho; Python mein **venv** = isolated env per project.

```bash
cd modules/00a-dev-environment/practice
python3 -m venv .venv
source .venv/bin/activate
pip install fastapi uvicorn httpx python-dotenv
python -c "import fastapi; print('ok')"
deactivate
```

| Line / command | Matlab |
|----------------|--------|
| `python3 -m venv .venv` | `.venv` folder mein isolated Python |
| `source .venv/bin/activate` | Current shell mein venv on — prompt `(.venv)` |
| `pip install ...` | Packages **sirf** is venv mein |
| `python -c "..."` | One-liner script |
| `deactivate` | Venv off |

**Expected:**

```
ok
```

**`requirements.txt` — team same versions:**

```bash
pip freeze > requirements.txt
pip install -r requirements.txt
```

| Node | Python |
|------|--------|
| `node_modules/` | `.venv/` |
| `package.json` | manual list / `pip freeze` |
| `package-lock.json` | `requirements.txt` |
| `nvm use 20` | `python3 -m venv` (version alag se pyenv se) |

#### §5 common errors

| Error message | Kyun | Fix |
|---------------|------|-----|
| `ModuleNotFoundError: fastapi` | Venv activate nahi / wrong python | `which python` → `.venv/bin/python` |
| `pip: command not found` | Python incomplete | `python3 -m pip install ...` |
| `externally-managed-environment` (PEP 668) | System Python protected | **venv use karo**, system pe mat install |

> **→ Practice A2** (pass): `import fastapi` → `ok`; `requirements.txt` exists.

---

### §6. `.env` — secrets kabhi git mein nahi

**Problem kya hai:** API keys, DB passwords **code mein hardcode** = GitHub pe leak, history se delete mushkil. Node mein `.env.local` — Python mein **`.env`** + **`python-dotenv`**.

```
# .env.example — GIT mein (template, fake values)
DATABASE_URL=postgresql://postgres:devpass@localhost:5432/aidev
REDIS_URL=redis://localhost:6379
OPENAI_API_KEY=sk-your-key-here

# .env — GIT mein NAHI (asli values)
```

**Load in Python:**

```python
from dotenv import load_dotenv
import os

load_dotenv()
db_url = os.getenv("DATABASE_URL")
```

| Line / symbol | Matlab |
|---------------|--------|
| `from dotenv import load_dotenv` | Library — `.env` file read |
| `load_dotenv()` | Current dir (or parent) se `.env` load |
| `os.getenv("DATABASE_URL")` | Env var read — missing pe `None` |

**`.gitignore` mein add:**

```
.env
.venv/
```

**Mask password print (A3 pattern):**

```python
# devpass in URL → dev***
# postgresql://postgres:devpass@localhost:5432/aidev
# → postgresql://postgres:dev***@localhost:5432/aidev
```

#### §6 common errors

| Error message | Kyun | Fix |
|---------------|------|-----|
| `None` printed for DATABASE_URL | `.env` missing / wrong cwd | `cp .env.example .env`; run from `practice/` |
| Secrets in `git status` | `.env` tracked | `.gitignore`; `git rm --cached .env` |
| Password full console pe | Mask function missing | A3 `mask_url()` implement |

> **→ Practice A3** (pass): `python check_env.py` → masked URL, password hidden.

---

### §7. Folder layout — aage ke projects ke liye

**Problem kya hai:** Modules, practice code, future services — bina layout ke har project alag jagah.

```
AI Development/
  docker-compose.yml          # (optional root — abhi practice/ mein A1)
  .env.example
  modules/
    00a-dev-environment/
      MODULE.md               # yeh file
      NOTES.md                # tumhari learnings
      practice/               # A1–A3 code
  services/                   # baad mein
    llm-gateway/              # FastAPI app — Module 00c+
```

| Path | Role |
|------|------|
| `modules/00x-.../MODULE.md` | Theory textbook |
| `modules/.../practice/` | Hands-on assignments |
| `modules/.../NOTES.md` | Active recall + session log |
| `services/` | Real apps jab projects start |

Abhi sab kuch `practice/` mein. Module 00c se FastAPI app yahi pattern follow karega.

> **→ Practice A4** (pass): NOTES mein Node vs Python layout — 5 bullets.

---

## Practice

> **Saare assignments ek jagah**: [`practice/README.md`](practice/README.md) — problem statements, instructions, pass criteria.  
> Code **tum** likhoge Cursor mein. Stubs `practice/` mein hain (`TODO` search).  
> Stuck? Chat: `@modules/00a-dev-environment/MODULE.md` + error paste karo.

| # | Theory § | File | Kya karna hai | Pass when |
|---|----------|------|---------------|-----------|
| A1 | §2–§4 | `practice/docker-compose.yml` | `TODO` comments complete karo | `docker compose up -d` → both healthy; `psql SELECT 1`; `PONG` |
| A2 | §5 | manual / optional `setup.sh` | venv + deps install | `import fastapi` works; `requirements.txt` |
| A3 | §6 | `practice/check_env.py` | `TODO` complete — load `.env` | Prints masked `DATABASE_URL` |
| A4 | §7 | `NOTES.md` | Node vs Python layout — 5 bullets | Coach approve / self-check |

### A1 hints

- `healthcheck` optional — production mindset: `pg_isready`, `redis-cli ping`
- Ports `5432` / `6379` Mac pe busy hon toh `"5433:5432"` try karo — connection string update

### A3 hints

- Password print mat karo full — `devpass` → `dev***` mask karo
- URL missing → `"missing"` print

---

## Active recall (khud jawab likho NOTES mein)

1. Docker volume Postgres ke liye kyun chahiye?
2. Redis aur Postgres gateway mein alag kyun?
3. `.env` git mein kyun nahi jaata?

**Chat drill** (optional): "Module 00a recall — 3 questions test karo"

---

## Progress checklist

- [ ] §0 terminal + Docker + YAML try kiya
- [ ] Visual map redraw challenge kiya
- [ ] Theory §1–§7 padh liya (section-by-section)
- [ ] Practice A1–A4 pass
- [ ] Active recall NOTES mein likha
- [ ] NOTES session log updated

---

## Optional appendix (zarurat ho tab)

- [Docker Compose docs](https://docs.docker.com/compose/) — deep dive only
- [Postgres Docker official image](https://hub.docker.com/_/postgres) — env vars list
- [python-dotenv](https://pypi.org/project/python-dotenv/) — load behavior
