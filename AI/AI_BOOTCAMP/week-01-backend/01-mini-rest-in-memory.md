# Week 1 — Lesson 1: Mini REST API (in-memory, bina DB)

> **Pehle complete karo:** `week-00-setup/01-mindset-and-tools.md`

## TL;DR

Ek **Notes API**: `POST /notes` (title + body), `GET /notes`, `GET /notes/:id`.  
Galat input → **400** + clear JSON error. Id galat → **404**. Sab **in-memory** (restart pe data gayab — abhi theek hai).

## Pehle yeh samjho

- **Validation:** client kuch bhi bhej sakta hai; tumhari duty hai reject karna.
- **Status codes:** `400` = client ne galti ki, `404` = resource nahi mila, `500` = tumhari side bug (start mein kam dikhe toh better).
- **Structured error:** `{ "error": "...", "details": ... }` jaisa pattern rakho — debugging easy.

## Karke dikhao

### Agar TypeScript (Fastify suggest)

1. Folder: `bootcamp-labs/week-01-api`
2. `npm init -y` → `npm i fastify`
3. `main.ts` ya `main.js` — ek hi file mein chalega v1  
4. Routes implement karo (neeche contract)

### Agar Python (FastAPI)

1. Folder: `bootcamp-labs/week-01-api`
2. `python -m venv .venv` → activate → `pip install fastapi uvicorn`
3. `main.py` — same routes

### API contract (dono stacks yeh follow karein)

**POST /notes**

- Body JSON: `{ "title": string (required, min 1 char), "body": string (optional, default "") }`
- Success: `201` + `{ "id": string, "title": "...", "body": "...", "createdAt": ISO string }`
- Fail validation: `400` + `{ "error": "validation_failed", "details": ... }`

**GET /notes**

- Success: `200` + `{ "notes": [ ... ] }`

**GET /notes/:id**

- Found: `200` + single note object  
- Not found: `404` + `{ "error": "not_found" }`

**IDs:** UUID ya `note_` + random string — kuch bhi stable unique.

## Homework

1. Poora API run karo locally.  
2. **3 curl / Postman** examples test karo:  
   - valid create  
   - invalid (empty title)  
   - GET unknown id → 404  
3. Chat mein paste karo: **run command** + **ek sample success response** (sensitive data mat).

## Done jab

- [ ] Teen routes kaam kar rahe hain  
- [ ] Validation + 400 / 404 sahi hain  
- [ ] Tumne khud 3 tests chala ke dekhe  
- [ ] Homework ka evidence chat mein hai  

**Next lesson:** `02-logging-and-request-id.md` (jab main add karunga — ya chat bolo "Week 1 L1 done")
