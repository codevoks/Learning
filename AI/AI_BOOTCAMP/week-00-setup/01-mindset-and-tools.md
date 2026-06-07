# Week 0 — Lesson 1: Mindset + tools (bina AI ke)

## TL;DR

AI se pehle tumhe **ek service** banani aani chahiye jo **predictable** ho — errors, validation, logs. Aaj sirf **mindset + machine check**.

## Pehle yeh samjho

1. **LLM = flaky component**  
   Network slow, rate limit, weird output — yeh normal. Isliye **baaki system** strong hona chahiye.

2. **Order matter karta hai**  
   Seedha RAG / agents mat pakdo. Pehle: “ek POST endpoint jo input check karta hai aur sahi status code deta hai.”

3. **Portfolio mein signal**  
   Interview mein “maine agent banaya” se zyada **“maine failure modes handle kiye”** signal deta hai.

## Karke dikhao (machine ready)

Neeche jo ho sake woh karo — jo already nahi hai:

1. **Git** — terminal mein `git --version`
2. **Node 20+** *ya* **Python 3.11+** — jo stack tumne pick kiya ho  
   - Node: `node -v`  
   - Python: `python3 --version`
3. **Code editor** — Cursor theek hai  
4. **Ek empty folder** banao jahan Week 1 ka project rahega, e.g.  
   `~/Desktop/Code/Learning/AI/bootcamp-labs/week-01-api`

`bootcamp-labs` repo tum khud banaoge; main sirf lessons dunga.

## Homework

1. **Stack decide karo** — TypeScript *ya* Python (abhi se; Week 1 tak final).  
2. Upar wale **4 checks** likh ke batao (chat mein): kaunsa install / version kya hai.  
3. Ek line mein likho: **“is week end tak main kya bana paunga?”**  
   Sahi answer kuch aisa: *“ek in-memory notes API jisme create/list ho aur galat input pe 400 aaye.”*

## Done jab

- [ ] Git + chosen runtime version terminal mein clear hai  
- [ ] Stack pick ho gaya (A ya B)  
- [ ] `bootcamp-labs/week-01-api` jaisa folder plan hai (banaya ya abhi sirf path decide)  
- [ ] Homework ki teen cheezein chat mein likh di

**Next lesson:** `../week-01-backend/01-mini-rest-in-memory.md` (Week 0 ke baad)
