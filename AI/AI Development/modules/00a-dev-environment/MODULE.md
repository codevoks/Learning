# Module 00a — Dev Environment

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: Start here · Next → [Module 00b](../00b-python-async/MODULE.md)

> **Format**: Textbook — main samjhata hoon (prose), table sirf reference (commands, errors). Voice: `@MODULE-TEACHING-STANDARD.md`

## At a glance

| | |
|---|---|
| Prerequisites | Mac terminal basics — `cd`, `ls` aate hon |
| Duration | ~2–3 sessions (section-by-section, ek din poora mat karo) |
| Project? | No |
| Exit test | `docker compose up` healthy + venv + `.env` load — bina notes ke setup karke dikha do |

## Yeh module kis baare mein hai

Tum baadwale modules mein FastAPI app, Postgres mein RAG embeddings, Redis se rate-limiting — sab banaoge. Par uske pehle tumhari machine pe ek aisa **local stack** khada hona chahiye jo team ke baaki logon jaisa exactly ho, warna "mere laptop pe to chal raha tha" waali maut milegi. Yeh module wahi neev daalta hai: ek command se Postgres + Redis uthana (Docker), Python ko project-wise isolate karna (venv), aur secrets ko git se bahar rakhna (`.env`).

§0 mein teen cheezein zero se samjhaunga jo tumhare liye nayi ho sakti hain — terminal symbols, Docker vocabulary, aur YAML syntax — kyunki baaki poora module inhi par khada hai.

---

## Read order (ek session ek tukda)

| Session | Padho | Karo (Practice) |
|---------|-------|-----------------|
| 1 | **§0** Terminal + Docker + YAML | Terminal try blocks §0 ke neeche |
| 2 | §1 Problem + §2 Docker Compose | **A1** start — `docker-compose.yml` TODO |
| 3 | §3 Postgres | **A1** complete — `psql SELECT 1` pass |
| 4 | §4 Redis | **A1** verify — `redis-cli ping` |
| 5 | §5 Python venv | **A2** — venv + `requirements.txt` |
| 6 | §6 `.env` secrets | **A3** — `check_env.py` |
| 7 | §7 Layout + active recall | **A4** NOTES + redraw challenge |

**Pehle §0, phir diagram.** Visual map §0 ke baad hai.

---

## Learning hooks (tera parallel — optional)

Tumhare Node/infra background se yeh seedha baith jaayega: Docker container ≈ ek lightweight isolated process (K8s pod ka chhota bhai); `docker-compose.yml` ≈ infra-as-code (Terraform jaisा feel, par local scale pe); Postgres ka volume ≈ persistent disk mount (EBS jaisa); Redis ≈ in-memory cache (ElastiCache / Upstash); Python `venv` ≈ per-project `node_modules` (global install mat karna); aur `.env` ≈ Next.js ka `.env.local` (git mein kabhi nahi).

---

## Theory

### §0. Terminal, Docker aur YAML — pehli baar (30 min)

Tum TS/Node se aaye ho — terminal use kiya hai, par **Docker aur YAML** shayad pehli baar. Is section ke baad har command aur har `docker-compose.yml` line padhi-padhi lagegi. Compose file dekhne se pehle yeh padho.

#### 0.1 Terminal — kaam ke commands

Yeh tumhe mostly aata hoga, par ek baar refresh kar lo kyunki har practice command terminal se chalega. `pwd` batata hai abhi tum kahan ho, `cd <path>` se folder badalte ho (`cd ..` ek level upar), `ls` files dikhata hai (`ls -la` mein hidden files + details bhi). Running process rokna ho to `Ctrl+C`, shell se nikalna ho to `Ctrl+D`.

Path do tarah ke hote hain aur yeh farak yaad rakhna zaroori hai: **relative path** (`practice/check_env.py`) abhi jahan ho wahan se ginਾ jaata hai, jabki **absolute path** (`/Users/vansh/.../practice`) root `/` se poora rasta deta hai. `~` tumhara home folder hai, `.` abhi waala folder, aur `..` parent. Galat path pe `cd` kiya to `no such file or directory` — `pwd` aur `ls` se confirm karke chalo.

Abhi try karo:

```bash
pwd
# /Users/vansh/Desktop/Code/Learning/AI/AI Development

cd modules/00a-dev-environment/practice
ls
# docker-compose.yml  check_env.py  README.md  ...

cd ../..
pwd     # wapas do level upar
```

#### 0.2 Docker — image aur container ka farak

Docker ek aisa system hai jo kisi bhi service ko uski saari dependencies ke saath ek **box** mein pack kar deta hai, taaki wo har machine pe bilkul same chale. Tumhari Mac pe **Docker Desktop** chalता hai (yeh engine hai), aur uske andar tumhare **containers** chalte hain.

Do shabd hain jo log gadbada dete hain, inhe abhi clear kar lo. **Image** ek read-only template hai — jaise `postgres:16` ek recipe hai "Postgres version 16 kaise khada karna hai". **Container** us image ka **chalta hua instance** hai. Ek image se tum kai containers bana sakte ho — bilkul jaise ek class se kai objects. Recipe (image) ek, par pakwaan (container) jitne chaaho.

Do aur cheezein jo aage aayengi: **volume** ek aisi storage hai jo container ke bahar zinda rehti hai (container delete ho jaaye, data bach jaaye — EBS disk jaisा), aur **port mapping** ek tunnel hai jo tumhari Mac ke `localhost:5432` ko container ke andar ke port se jodता hai.

Check karo Docker ready hai:

```bash
docker --version          # Docker version 27.x.x ...
docker compose version    # Docker Compose version v2.x.x
```

`command not found` aaye to Docker Desktop install karo, app kholo, aur menu-bar mein whale icon green hone ka wait karo (matlab engine chal pada).

#### 0.3 YAML — indentation hi sab kuch hai

`docker-compose.yml` YAML mein likha hota hai. YAML JSON jaisा hai par `{}` `[]` ke bina — yahan **nesting spaces se** batayi jaati hai, isliye indentation galat hui to poori file invalid. Yaad rakho: `key: value` ek pair hai (colon ke baad space zaroori), `- item` ek list entry hai, aur har nesting 2-space indent se andar jaati hai. Ports ko `"5432:5432"` quotes mein likhna safe hai.

Chhota example dekho, structure pakdo:

```yaml
services:           # top-level — kaunsi services chahiye
  postgres:         # service ka naam — tum chunte ho
    image: postgres:16
    ports:
      - "5432:5432"           # host:container
    environment:
      POSTGRES_PASSWORD: devpass
```

Yahan `postgres:` 2 space andar hai kyunki wo `services:` ke *andar* hai, aur uska `image`/`ports` 4 space andar kyunki wo `postgres:` ke andar hain. Agar tum `postgres:` ko `services:` ke barabar (0 indent) likh do, YAML samjhega yeh ek alag top-level cheez hai aur parse fail ho jaayega:

```yaml
services:
postgres:    # ❌ galat — services ke andar hona chahiye, 2 space indent
  image: postgres:16
```

> **Ruko, socho:** Upar wale sahi example mein `"5432:5432"` ke do numbers — left waala kiska port hai, Mac ka ya container ka? (Jawab: left = host/Mac, right = container. `localhost:5432` se baat karoge, andar wo container ke 5432 pe pahunchegi.)

#### 0.4 Docker CLI — pehli commands

Yeh char commands baar-baar use honge: `docker ps` running containers dikhata hai (khaali list normal hai jab kuch nahi chal raha), `docker images` local downloaded images, `docker compose up -d` compose file se sab start karta hai (`-d` = background mein), aur `docker compose down` sab stop + remove karta hai (volume ka data usually bach jaata hai).

#### 0.5 §0 common errors

| Error message | Kyun | Fix |
|---------------|------|-----|
| `command not found: docker` | Docker Desktop install nahi / PATH | Docker Desktop install + open |
| `Cannot connect to the Docker daemon` | Engine nahi chal raha | Docker Desktop start karo, whale green |
| `yaml: line X: mapping values are not allowed` | Indent galat / colon ke baad space missing | 2-space indent; `key: value` mein space |
| `cd: no such file or directory` | Galat path | `pwd` + `ls` se confirm |
| `permission denied` | Execute permission nahi | `python script.py` use karo |

#### §0 checkpoint (khud jawab — NOTES mein)

1. Image aur container mein farak ek line mein?
2. YAML mein nesting kaise batti hai — `{}` se ya spaces se?
3. `5432:5432` mein left side kiska port hai?

**§0 done?** Ab §1 — problem samjho, phir visual map.

---

## Visual map (§0 ke baad — ab padho)

```
Mac (tumhara code editor + terminal)
 └── docker compose up
       ├── postgres + volume pgdata (data restart pe bachta hai)
       ├── redis (in-memory)
       └── (future) FastAPI app container
```

**Mental model**: Mac pe code likho, databases **containers** mein — ek command se poora local stack. Production mein yahi idea Kubernetes pods pe scale hota hai; tum abhi wahi muscle local pe bana rahe ho.

**Redraw challenge**: Bina dekhe yeh diagram banao — Mac → compose → postgres/redis.

---

### §1. Problem — "mere machine pe kyun nahi chal raha?"

Socho tum aur tumhara teammate same project pe ho. Tumne `brew install postgresql@16` kiya, usne `@15`. Ab ek query tumhare yahan chalti hai, uske yahan toot-ti hai, aur do din yahi debug karne mein nikal jaate hain. Yeh classic **"works on my machine"** bug hai — alag-alag machines pe alag versions, alag config. Bade systems (Rootstock, matching engine) mein yeh bug zeher hai.

Iska seedha ilaaj: environment ko **declare** karo ek file mein. Har banda `docker compose up` chalaye aur sabko bilkul same Postgres, same Redis, same version mile. Manual install ki jagah ek YAML file source of truth ban jaati hai — naya teammate aaye to `git clone` + `compose up`, do ghante ka setup do minute mein.

Tumhare liye hook: yeh local Compose ek **chhota Kubernetes** hai — wahi "declarative infra" soch, bina cluster ke.

> **→ Practice A1** (start): `practice/docker-compose.yml` kholo — ab services samajh aayengi.

---

### §2. Docker Compose — ek file, poora stack

Postgres aur Redis ko alag-alag haath se install karna do moving parts, do version stories. Compose in dono ko ek YAML file mein baandh deta hai — tum likhte ho "mujhe yeh services chahiye", aur Docker khada kar deta hai.

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

Is file mein kuch cheezein samajhne layak hain. `image: postgres:16` Docker Hub se official Postgres version 16 uthata hai. `POSTGRES_PASSWORD` aur `POSTGRES_DB` — yeh special env vars hain jinhe Postgres image pehchaanta hai: pehli baar start pe wo `aidev` naam ka database bana deta hai is password ke saath. Sabse important do lines `volumes` waali hain: `pgdata:/var/lib/postgresql/data` ka matlab hai "Postgres apna data jahan likhta hai (`/var/lib/...`), use `pgdata` naam ke volume pe save karo" — aur neeche `volumes: pgdata:` us volume ko declare karta hai. Yeh kyun zaroori hai, §3 mein khulega, par short mein: bina iske har `down` pe tumhara data udd jaata.

Port mapping ka flow seedha hai: tumhari app `localhost:5432` pe baat karti hai → Docker use container ke `:5432` pe forward karta hai → andar Postgres process sun raha hota hai.

Commands — A1 ke baad ek-ek try karo:

```bash
cd modules/00a-dev-environment/practice
docker compose config          # YAML valid? errors yahan
docker compose up -d           # background start
docker compose ps              # STATUS column dekho
docker compose logs postgres   # debug ke liye
docker compose down            # stop (data bachta hai)
docker compose down -v         # ⚠️ -v = volumes delete, DB empty
```

`docker compose ps` ka output aisा dikhe to samajh lo pass:

```
NAME                  IMAGE         STATUS          PORTS
practice-postgres-1   postgres:16   Up (healthy)    0.0.0.0:5432->5432/tcp
practice-redis-1      redis:7       Up              0.0.0.0:6379->6379/tcp
```

> **Ruko, socho:** `docker compose down` aur `docker compose down -v` mein kya farak hai, aur kaunsa galti se chalा diya to dukh hoga? (Jawab: `-v` volumes delete kar deta hai — DB ka saara data gaya. Bina `-v` sirf containers rukte hain, data bachta hai.)

#### §2 common errors

| Error message | Kyun | Fix |
|---------------|------|-----|
| `port is already allocated` | Mac pe Postgres/Redis already chal raha | `brew services stop postgresql` ya mapping `"5433:5432"` |
| `service "postgres" refers to undefined volume` | Bottom `volumes: pgdata:` missing | Bottom volumes block add karo |
| `pull access denied` | Image naam typo | `postgres:16` spelling check |
| `dependency failed to start` | Bad env / corrupt volume | `docker compose logs postgres`; worst case `down -v` (data loss) |

> **→ Practice A1** (pass): `docker compose up -d` → postgres + redis dono `Up`.

---

### §3. Postgres container — tumhara data ghar

Aage RAG (pgvector), gateway logs, user data — yeh sab ek **relational database** maangte hain, aur wo Postgres hai. Tum Prisma se Postgres use kar chuke ho; yahan ek level neeche jaake raw connection samajhna hai.

Pehle wo "volume kyun" waali baat poori karte hain, kyunki yeh naye log ko hamesha kaatti hai. Container ka apna andar ka filesystem **ephemeral** hai — container hata, filesystem gaya. Agar tumne Postgres ka data sidha container ke andar rakha, to har `docker compose down` pe DB khaali ho jaata. Isliye hum `pgdata` volume mount karte hain: data Docker ke managed disk pe rehta hai, container aaye-jaaye, data bana rehta hai.

Postgres se baat karne ka connection string ek fixed shape mein hota hai:

```
postgresql://USER:PASSWORD@HOST:PORT/DATABASE
postgresql://postgres:devpass@localhost:5432/aidev
```

Yahan user `postgres` (default superuser), password `devpass` (compose ke `POSTGRES_PASSWORD` se exactly match hona chahiye), host `localhost` (Mac se mapped port tak), port `5432`, aur database `aidev` (`POSTGRES_DB` waala). Yeh paanch tukde galat hue to connection fail — isliye password ko ek hi jagah decide karke har jagah same rakho.

Container up hone ke baad test:

```bash
docker compose exec postgres psql -U postgres -d aidev -c "SELECT 1;"
```

`docker compose exec postgres` ka matlab "chalte hue postgres container ke andar yeh command chalao". `psql` Postgres ka CLI hai, `-U postgres` user, `-d aidev` database, aur `-c "..."` ek single SQL chalata hai. Sahi chala to:

```
 ?column?
----------
        1
(1 row)
```

Ek chhoti table banake feel le lo:

```bash
docker compose exec postgres psql -U postgres -d aidev \
  -c "CREATE TABLE IF NOT EXISTS health_check (id SERIAL PRIMARY KEY, ok BOOLEAN NOT NULL); INSERT INTO health_check (ok) VALUES (true);"
```

`SERIAL PRIMARY KEY` ek auto-increment ID deta hai, `BOOLEAN NOT NULL` matlab `ok` true/false hona zaroori. SQL tumne pehle dekha hai — yahan point sirf yeh hai ki container ke andar database zinda hai aur likh raha hai.

#### §3 common errors

| Error message | Kyun | Fix |
|---------------|------|-----|
| `connection refused` on 5432 | Container down / wrong port | `docker compose ps` |
| `FATAL: password authentication failed` | `.env` password ≠ compose password | Same password har jagah |
| `database "aidev" does not exist` | `POSTGRES_DB` missing / typo | Compose env check |
| `role "postgres" does not exist` | Galat `-U` | `-U postgres` (default image) |

> **→ Practice A1** (verify): `psql ... SELECT 1` → `1` row.

---

### §4. Redis container — tez memory store

Har cheez Postgres mein daalna theek nahi. Rate-limit counters, cache, pub/sub jaisा ephemeral data disk pe likhna slow hai. Redis ek **in-memory** key-value store hai — sab kuch RAM mein, isliye microseconds mein. Tradeoff yeh ki RAM-based hai, to durability Postgres jaisi nahi — par jis data ko hum Redis mein rakhte hain (cache, counters) uske kho jaane se kayamat nahi aati.

Yahi Postgres vs Redis ka core farak hai: Postgres **source of truth** hai (disk-first, durable, SQL/joins), Redis **speed layer** hai (RAM-first, simple GET/SET, ephemeral OK). Gateway banoge to billing logs/users Postgres mein jaayenge, cache aur rate-limit Redis mein. Aage projects mein Redis yeh kaam karega: matching-engine jaisा pub/sub (channels), LLM semantic cache (`SET key value EX 3600`), rate-limiting (`INCR user:123:requests`), aur TTL keys jo auto-expire ho jaati hain.

Test:

```bash
docker compose exec redis redis-cli ping       # PONG
docker compose exec redis redis-cli SET test "hello"   # OK
docker compose exec redis redis-cli GET test   # "hello"
```

`PONG` matlab Redis zinda hai; `SET`/`GET` se ek key likh-padh ke confirm ho gaya. Cache ka pattern aisा hota hai: app pehle `GET cache:key` karti hai, miss hua to Postgres/API se laata hai, phir `SET cache:key EX 3600` karke agli baar ke liye cache kar deti hai.

#### §4 common errors

| Error message | Kyun | Fix |
|---------------|------|-----|
| `Could not connect to Redis` | Container down / wrong port | `docker compose ps`; `6379:6379` |
| `(error) NOAUTH` | Password set (humne nahi kiya) | Default image — local pe no password |
| `OOM` (rare local) | Memory full | `docker compose restart redis` |

> **→ Practice A1** (final): `redis-cli ping` → `PONG`.

---

### §5. Python virtual environment (venv)

Yeh concept tumhe Node se seedha samajh aayega. System ke global Python mein `pip install` karna **version hell** hai — project A ko FastAPI 0.100 chahiye, B ko 0.115, dono global install ek doosre ko tod denge. Node mein bhi tum global install se bachte ho aur `node_modules` per-project rakhte ho. Python mein wahi kaam **venv** karta hai: har project ka apna isolated Python + packages.

```bash
cd modules/00a-dev-environment/practice
python3 -m venv .venv          # .venv folder mein isolated python
source .venv/bin/activate      # is shell mein venv on (prompt pe (.venv))
pip install fastapi uvicorn httpx python-dotenv
python -c "import fastapi; print('ok')"   # ok
deactivate                     # venv off
```

Yahan `python3 -m venv .venv` ek `.venv` folder banata hai jisme alag Python rehta hai. `source .venv/bin/activate` us venv ko current shell mein "on" kar deta hai — ab `pip install` jo bhi laaye, wo **sirf is venv** mein jaata hai, system gandा nahi hota. Kaam khatam to `deactivate`.

Team ke saath same versions ke liye `pip freeze > requirements.txt` se exact versions lock karte ho, aur doosra banda `pip install -r requirements.txt` se wahi versions paata hai. Mapping yaad rakho: `node_modules/` ≈ `.venv/`, aur `package-lock.json` ≈ `requirements.txt`.

#### §5 common errors

| Error message | Kyun | Fix |
|---------------|------|-----|
| `ModuleNotFoundError: fastapi` | Venv activate nahi / galat python | `which python` → `.venv/bin/python` hona chahiye |
| `pip: command not found` | Python incomplete | `python3 -m pip install ...` |
| `externally-managed-environment` (PEP 668) | System Python protected | **venv use karo**, system pe install mat karo |

> **→ Practice A2** (pass): `import fastapi` → `ok`; `requirements.txt` exists.

---

### §6. `.env` — secrets kabhi git mein nahi

API keys aur DB passwords agar code mein hardcode kar diye, to ek baar GitHub pe push hote hi wo public ho gaye — aur git history se delete karna painful hai (commit history mein reh jaate hain). Node mein tum `.env.local` use karte the; Python mein `.env` file + `python-dotenv` library.

Pattern yeh hai: ek `.env.example` git mein rakho (template, **fake** values) taaki team ko pata ho kaunse vars chahiye, aur asli values `.env` mein jo git mein **kabhi nahi** jaati:

```
# .env.example — git mein (template, fake values)
DATABASE_URL=postgresql://postgres:devpass@localhost:5432/aidev
REDIS_URL=redis://localhost:6379
OPENAI_API_KEY=sk-your-key-here

# .env — git mein NAHI (asli values)
```

Python mein load karna:

```python
from dotenv import load_dotenv
import os

load_dotenv()                       # current/parent dir se .env padho
db_url = os.getenv("DATABASE_URL")  # missing ho to None milta hai
```

`load_dotenv()` `.env` ko padhke us session ke environment mein daal deta hai, phir `os.getenv(...)` se values nikalti hain. Aur sabse zaroori — `.gitignore` mein `.env` aur `.venv/` daalo taaki galti se commit na ho jaaye.

Ek production habit abhi se: jab DB URL print karo (debugging), to password mask karo — `postgresql://postgres:devpass@...` ko `postgresql://postgres:dev***@...` dikhao. Logs mein poora password aana ek real leak hai.

#### §6 common errors

| Error message | Kyun | Fix |
|---------------|------|-----|
| `None` printed for DATABASE_URL | `.env` missing / galat cwd | `cp .env.example .env`; `practice/` se chalao |
| Secrets in `git status` | `.env` track ho gaya | `.gitignore` + `git rm --cached .env` |
| Password poora console pe | Mask function missing | A3 ka `mask_url()` implement karo |

> **→ Practice A3** (pass): `python check_env.py` → masked URL, password hidden.

---

### §7. Folder layout — aage ke projects ke liye

Jaise-jaise modules badhenge, theory, practice code, aur future real services — sabko ek consistent jagah chahiye warna har cheez bikhar jaayegi. Layout aisा hai:

```
AI Development/
  modules/
    00a-dev-environment/
      MODULE.md     # theory (yeh file)
      NOTES.md      # tumhari learnings + session log
      practice/     # A1–A4 ka code
  services/         # baad mein — asli apps (FastAPI gateway, etc.)
```

Soch seedhi hai: har module mein `MODULE.md` theory, `practice/` hands-on, `NOTES.md` tumhare active-recall aur session log. Abhi sab kuch `practice/` mein hai; Module 00c se jab asli FastAPI app banegi, wo `services/` mein yahi pattern follow karegi.

> **→ Practice A4** (pass): NOTES mein Node vs Python layout — 5 bullets (jaise `node_modules`→`.venv`, `package.json`→`requirements.txt`, ...).

---

## Practice

> **Saare assignments ek jagah**: [`practice/README.md`](practice/README.md) — problem statements, instructions, pass criteria.
> Code **tum** likhoge Cursor mein. Stubs `practice/` mein (`TODO` search karo).
> Stuck? Chat: `@modules/00a-dev-environment/MODULE.md` + error paste. Solution mat maango — hint maango.

| # | Theory § | File | Kya karna hai | Pass when |
|---|----------|------|---------------|-----------|
| A1 | §2–§4 | `practice/docker-compose.yml` | `TODO` complete karo | `up -d` → both healthy; `psql SELECT 1`; `PONG` |
| A2 | §5 | manual / optional `setup.sh` | venv + deps install | `import fastapi` works; `requirements.txt` |
| A3 | §6 | `practice/check_env.py` | `TODO` complete — load `.env` | masked `DATABASE_URL` print |
| A4 | §7 | `NOTES.md` | Node vs Python layout — 5 bullets | self-check |

### A1 hints

- `healthcheck` optional par production-minded — `pg_isready`, `redis-cli ping`.
- Ports `5432`/`6379` Mac pe busy ho to `"5433:5432"` try karo aur connection string update karo.

### A3 hints

- Full password mat print karo — `devpass` → `dev***`.
- URL missing → `"missing"` print karo, crash nahi.

---

## Active recall (khud jawab likho NOTES mein)

1. Docker volume Postgres ke liye kyun chahiye — bina iske kya hota?
2. Redis aur Postgres gateway mein alag-alag kyun, dono ka kaam kya?
3. `.env` git mein kyun nahi jaata, aur leak ho jaaye to kya dikkat?

**Chat drill** (optional): "Module 00a recall — 3 questions mujhse poochh."

---

## Progress checklist

- [ ] §0 terminal + Docker + YAML try kiya
- [ ] Visual map redraw challenge kiya
- [ ] Theory §1–§7 padha (section-by-section)
- [ ] Practice A1–A4 pass
- [ ] Active recall NOTES mein likha
- [ ] NOTES session log updated

---

## Optional appendix (zarurat ho tab)

- [Docker Compose docs](https://docs.docker.com/compose/) — deep dive
- [Postgres Docker image](https://hub.docker.com/_/postgres) — env vars list
- [python-dotenv](https://pypi.org/project/python-dotenv/) — load behavior
