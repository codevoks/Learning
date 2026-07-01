# A2 — prompt vs RAG vs fine-tune (tum bharoge)

> Har scenario ke liye **ek** chuno (prompt / RAG / fine-tune / combo) aur **kyun**
> likho (§1 framework use karo: facts → RAG, behaviour tweak → prompt, consistent
> format/style with many examples → fine-tune).

| # | Scenario | Choice | Reason (1-2 lines) |
|---|----------|--------|--------------------|
| 1 | Support bot ko company ki latest refund policy chahiye (har hafte badalti hai) | | |
| 2 | Model ko hamesha strict JSON schema mein reply karna hai; prompt se kabhi-kabhi toot-ta hai | | |
| 3 | Bot thoda zyada formal tone mein bole (aaj casual hai) | | |
| 4 | Ek medical-notes summarizer jo bahut specific hospital format follow kare (5000 labelled examples hain) | | |
| 5 | GPT-4 kaam kar raha par mehenga; ek high-volume classify task ko sasta karna hai | | |

## Bonus — apne shabdon mein

- Fine-tuning ko "naye facts" sikhane ke liye kyun **nahi** use karte? (2 lines)
- Ek galti jo log fine-tuning ke saath karte hain aur uska cost?
