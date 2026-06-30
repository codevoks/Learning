# Module teaching standard — textbook, cheat sheet nahi

> Har `MODULE.md` ek **teacher ki awaaz** hai jo baith ke samjha raha hai — notes nahi jo tumne exam se pehle banaye.
> Audience: **pehli baar seekh raha hai** ya **dusre stack se migrate** (TS/Node → Python/Go).
> **Reference example: [`modules/01-llm-apis/MODULE.md`](modules/01-llm-apis/MODULE.md)** — yahi voice copy karni hai.

## Rule 1 — Prose pehle, table sirf reference ke liye

Yeh sabse important rule hai, aur purana standard yahin galat tha.

**Concept samjhana hai → poore wakya likho.** Ek concept = 3–6 line ka paragraph jo confusion se insight tak le jaaye, intuition pehle aur fact baad mein. Analogy ko wakya ke andar bunno, table cell mein nahi.

**Table sirf tab jab cheez sach mein lookup/reference ho** — error catalog, parameter ranges, status codes, side-by-side comparison. Agar koi naya banda us table ko *sikhne* ke liye padhega, toh wo table galat hai — usko prose banao.

> **Banned:** har naye term/concept ko ek table-row mein define karna (`| Term | Matlab |`). Wo revision notes ka format hai. Pehli baar wala bandా table scan karta hai, samajhta nahi.

## Rule 2 — Code ke neeche narration, line-by-line table nahi

Purana rule "har code block ke neeche `| Line | Matlab |` table" — **yeh ab banned hai.** Wahi rule har cheez ko cheat sheet bana raha tha.

Iske badle: code block ke baad **prose mein** wo 2–3 cheezein samjhao jo sach mein matter karti hain, aur **kyun** matter karti hain. Har line explain karne ki zaroorat nahi — important line pe ruko, uska reason batao. Numbered "request flow 1 → 2 → 3" theek hai jab sequence hi point ho.

## Rule 3 — Intuition pehle, "kyun" har jagah

- Har section ek **"yeh kyun seekh rahe ho / problem kya hai"** se shuru ho.
- Ek **worked example dheere-dheere develop karo** — number/output dikhao taaki feel aaye (jaise 01 ka cost example: per-call → 1M calls).
- Fact batao toh uska **mechanism/kyun** bhi do ("output mehenga hai *kyunki* sequential generation").

## Rule 4 — "Ruko, socho" beats

Section ke beech mein chhote active-recall jhatke daalo:

> **Ruko, socho:** <chhota sawaal> (jawab ek line mein, par pehle khud socho)

Yeh padhne ko active banata hai. 1–2 per section kaafi.

## Rule 5 — Theory § → Practice assignment

Har theory section ke end pe:

> **→ Practice Ax** (pass: curl / command output)

Ek section padho → assignment → agla section. Poora module ek din mein nahi.

## Rule 6 — Reference tables jo bachne chahiye

Yeh tables prose ki jagah rakhna sahi hai (yeh genuinely lookup hain):

- **Common errors:** `| Error / symptom | Kyun | Fix |`
- **At a glance:** prerequisites / duration / exit test
- **Read order:** session-by-session — kya padhna, kya karna
- **Parameters / status codes / pricing tiers:** side-by-side compare

## Module checklist (ship se pehle)

- [ ] Har concept prose mein samjhaya — table-row definitions nahi
- [ ] Code ke baad narration (sahi 2–3 cheezein + kyun), na ki line-by-line table
- [ ] Kam se kam ek worked example numbers ke saath develop hua
- [ ] 1–2 "ruko socho" beats per section
- [ ] §0 mein har naya symbol/term *use se pehle* define
- [ ] Har section → Practice Ax pointer
- [ ] curl / go run / python commands with expected output
- [ ] Active recall samajh test karta hai, ratta nahi
- [ ] Sections sahi order mein numbered (§1, §2… — koi §7-before-§6 jaisी galti nahi)

## Track 0 vs Track 1

- **Code modules (00a–00e):** §0 = language/tool syntax zero se (`:=`, `@`, docker commands) — par **prose mein samjhao**, sirf syntax table mat do.
- **AI modules (01–11):** §0 = terms zero se (token, embedding, RAG, agent, MCP…) — har term analogy + chhote example ke saath, **paragraph mein**.

High-level architecture diagrams **§0 ke baad** — pehle terms, phir picture.
