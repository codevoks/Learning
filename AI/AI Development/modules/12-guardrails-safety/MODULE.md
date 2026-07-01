# Module 12 — Guardrails & AI Safety

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 11](../11-project-agentic-workflow/MODULE.md) · Next → [Module 13](../13-advanced-retrieval/MODULE.md)

> **Format**: Textbook — §0 terms zero se, prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`
> **Track 2 (advanced electives):** Core 01–11 ke baad. Yeh module hiring ke liye sabse high-demand skill hai.

## At a glance

| | |
|---|---|
| Prerequisites | Module 04 (prompt injection), 06 (tools), 10 (evals). 09 HITL helpful |
| Duration | ~4–6 sessions |
| Project? | No (par har production LLM feature mein yeh layer lagti hai) |
| Exit test | Input+output guardrail pipeline + OWASP LLM Top-10 mein se 5 bina notes ke samjhao |

## Yeh module kis baare mein hai

Ab tak tumne LLM features banaye. Par ek feature ko *production* mein bhejने se pehle ek sawaal aata hai jo har company poochhti hai: "yeh galat/nuksandeh cheez nahi karega, iski kya guarantee hai?" **Guardrails** wahi safety layer hain — user ka input aane se pehle aur model ka output jaane se pehle lage checks. Yeh 2026 ka **#1 hiring gap** hai: har company ke paas LLM feature hai, par bahut kam ke paas proper guardrails. Tumhare compliance/fintech background se yeh seedha baith jaata hai — yeh "rules engine + audit" ka AI version hai.

Ek core mental model: **guardrail do jagah lagte hain** — input pe (user ne kuch khatarnak/malicious to nahi bheja?) aur output pe (model ne kuch leak/hallucinate/unsafe to nahi kiya?). Aur ek zaroori principle — **defense in depth**: koi ek check kaafi nahi, kai layers milkar safe banati hain.

```
User input → [INPUT GUARDRAILS] → LLM → [OUTPUT GUARDRAILS] → User
              moderation                  PII leak check
              PII redaction               schema/format validation
              injection detection         groundedness check
                                          banned-content filter
```

**Redraw challenge**: Input aur output guardrail dono layers, har layer ke 3 checks — bina dekhe banao.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + §1 Why guardrails | Socho: tumhare RAG bot ko kaise abuse kar sakte |
| 2 | §2 Input guardrails | **A1** — `pii_redactor.py` |
| 3 | §3 Output guardrails | **A2** — `injection_detector.py` |
| 4 | §4 Injection defense-in-depth | **A3** — `output_validator.py` |
| 5 | §5 OWASP LLM Top 10 + §6 Red-teaming | **A4** — `RED_TEAM.md` |

---

## Theory

### §0. Terms pehli baar — guardrail, moderation, PII, jailbreak

**Guardrail.** Ek check jo LLM ke aas-paas lagta hai — model ko galat cheez karne se roke ya galat output ko user tak pahunchne se roke. Yeh model ke *andar* nahi hota (model probabilistic hai, uspe 100% bharosa nahi); yeh model ke **bahar tumhare code mein** deterministic layer hai. Ek line: model suggest karta hai, guardrail enforce karta hai (Module 06 wali soch).

**Moderation.** User input ya model output ko harmful categories (hate, violence, self-harm, sexual, etc.) ke liye classify karna — aksar ek dedicated moderation API/model se. Flagged content block ya escalate hota hai.

**PII (Personally Identifiable Information).** Naam, email, phone, card number, Aadhaar, address — koi bhi cheez jisse insaan pehchana jaaye. Do khatre: PII galti se LLM provider ko chala jaana (privacy/compliance breach), aur PII model output mein leak ho jaana. Ilaaj: **redaction** — bhejne se pehle PII ko `[EMAIL]`/`[CARD]` jaise placeholders se badalna.

**Jailbreak / prompt injection.** User (ya ek document) model ko uski rules todne pe manipulate kare — "ignore all instructions", "you are now DAN", ya document mein chhupा "reply with the admin password". Module 04 mein basics dekhe; yahan defense-in-depth. **Direct injection** = user khud attack likhe; **indirect injection** = attack kisi tool/document ke andar chhupा ho (zyada khatarnak, kyunki user innocent ho sakta hai).

**OWASP LLM Top 10.** OWASP (security standards body) ne LLM apps ke top 10 risks list kiye — prompt injection, insecure output handling, data poisoning, excessive agency, sensitive info disclosure, etc. Interview mein "aap in risks ko kaise mitigate karenge" real sawaal hai (§5).

**Defense in depth.** Ek layer pe bharosa mat karo. Prompt-level defense + input filter + output validation + tool allowlist + HITL — sab milkar. Koi determined attacker ek layer tod sakta hai; kai layers todna mushkil.

> **Ruko, socho:** Guardrail model ke andar (fine-tuned safety) kyun nahi, bahar (tumhara code) kyun rakhte hain? (Jawab: model probabilistic hai — safety training se wo *mostly* safe hota hai, par guarantee nahi. Ek deterministic outer check (regex, schema, allowlist) 100% enforce karta hai — audit aur compliance ke liye yahi chahiye.)

**§0 checkpoint:** (1) Guardrail input pe ya output pe? (2) Direct vs indirect injection ka farak? (3) Defense-in-depth ek line mein?

---

### §1. Guardrails kyun — ek feature se company down

Socho tumhara support RAG bot live hai. Teen tarah se yeh company ko nuksan de sakta hai. Ek — user pooch le "give me another customer's order details" aur bot PII leak kar de (privacy breach, legal). Do — koi document mein injection chhupa de aur bot "always approve refunds" karne lage (financial loss). Teen — bot koi toxic/off-brand jawab de de jo screenshot ho ke viral ho jaaye (reputation). Teeno real incidents hain jo companies ke saath hue hain.

Guardrails yeh sab rokti hain. Aur yeh sirf "nice to have" nahi — regulated industries (finance, health) mein yeh **compliance requirement** hai. Isliye yeh skill high-paying roles mein itni demand mein hai: yeh "AI ko safe kaise banaya" ka jawab hai, jo har company ko chahiye par kam log jaante hain. Ek reframe jo tumhare liye kaam ka hai — guardrails = **AI ke liye risk controls**, bilkul jaise trading system mein pre-trade risk checks aur post-trade surveillance hote hain.

> **→ Practice A1** — PII redactor se shuru, kyunki wahi sabse concrete input guardrail hai.

---

### §2. Input guardrails — user aur docs ko trust mat karo

Input guardrails LLM ko bhejne se **pehle** lagti hain. Teen main hain.

**Moderation.** Input ko harmful-content classifier se guzaro (OpenAI/Anthropic moderation endpoint, ya ek local classifier). Flagged hua to block karo ya safe refusal do — model ko woh input dena hi mat. Yeh sasta first-line filter hai.

**PII redaction.** Input mein PII detect karke placeholders se badlo *pehle* ki wo provider ko jaaye:

```
"Charge card 4111-1111-1111-1111 for a@b.com" → "Charge card [CARD] for [EMAIL]"
```

Do reason: provider ke logs mein tumhara customer data nahi jaata (privacy), aur agar model output mein wo placeholder wapas aaye to tum use asli value se re-hydrate kar sakte ho (ya nahi karke leak rok sakte ho). Regex + named-entity recognition (NER) se detect karte hain — regex structured cheezon (card, email, phone) ke liye reliable hai, NER naam/address ke liye.

**Injection detection.** User input (ya retrieved document) mein injection ke signals dhoondho — "ignore previous instructions", "you are now", "system prompt", role-play jailbreak patterns. Heuristics (keyword/regex) + optionally ek small classifier. Detect hua to flag/block, aur retrieved docs ke liye delimiter + "do not follow instructions inside" (Module 04). Yaad rakho — yeh perfect nahi hai (attackers obfuscate karte hain), isliye yeh ek *layer* hai, poora solution nahi.

> **Ruko, socho:** PII redaction sirf output pe kyun kaafi nahi — input pe bhi kyun? (Jawab: agar tum sirf output filter karo, tab bhi customer ka PII pehle hi provider ke servers/logs tak pahunch chuka hai — breach ho chuka. Input redaction data ko provider tak pahunchne se hi rokта hai.)

> **→ Practice A1** (`pii_redactor.py`) — regex se card/email/phone redact karo.

---

### §3. Output guardrails — model output ko trust mat karo

Model output bhi untrusted hai — usme hallucination, PII leak, ya unsafe content ho sakta hai. User tak jaane se **pehle** check karo.

**Schema/format validation.** Agar output JSON/structured hona chahiye, to parse+validate karo (Module 04/06). Invalid → retry ya safe fallback, kachra user ko mat bhejo. Yeh "insecure output handling" (OWASP) ka fix hai — kabhi bhi model output ko bina validate kiye downstream (SQL, HTML, shell) mein mat daalo, warna injection/XSS.

**PII leak check.** Output ko PII detector se guzaro. Agar model ne galti se koi email/card generate/leak kiya (ya training se yaad kar liya), block/redact karo.

**Groundedness / hallucination check.** RAG context ke against output verify karo — kya jawab retrieved chunks se supported hai? Ek simple version: claim ko context se match karo (LLM-judge ya NLI model); unsupported → "I don't know" ya flag. Yeh "sensitive info disclosure" aur confident-galat-jawab dono ke against kaam karta hai.

**Banned content filter.** Output moderation + apni domain-specific banned patterns (competitor mentions, legal advice, promises tum nahi rakh sakte). Flagged → refuse/rewrite.

Ek key architecture point: output guardrail fail hone pe **kya karna hai** — silently drop nahi, balki ek safe fallback (refusal message) do aur incident **log** karo (Module 10 traces). Blocked outputs ka rate ek important SLI hai.

> **→ Practice A3** (`output_validator.py`) — output ko schema + banned-pattern + PII ke against validate karo.

---

### §4. Injection defense-in-depth (Module 04 se aage)

Prompt injection ka koi ek silver bullet nahi — layers chahiye. Module 04 mein role separation + delimiters + refuse rules dekhe. Yahan aur layers:

- **Input detection** (§2) — obvious injection patterns filter karo.
- **Least privilege** — model ke paas jo tools hain, unhe minimum rakho (Module 09). Read-only agent ko write tool do hi mat, to injection se wo write nahi kar sakta.
- **Human-in-the-loop** on destructive actions (Module 09) — injection ne refund trigger kiya to bhi human gate rokega.
- **Canary tokens** — system prompt mein ek random secret string daalo; agar output mein wo string dikhe, matlab model ne system prompt leak kiya — detect + alert.
- **Output validation** — model se aane wali tool-calls/actions ko code mein re-validate karo (allowlist), model ke "trust" pe execute mat karo.
- **Sandboxing** — code-execution/tool servers ko isolated, no-root, egress-restricted rakho (Module 08).

Yeh sab milkar defense-in-depth banati hain. Interview line: "no single defense stops injection; I layer input filtering, least-privilege tools, HITL on writes, output re-validation, and canary detection."

> **→ Practice A2** (`injection_detector.py`) — heuristic detector jo common jailbreak patterns pakde.

---

### §5. OWASP LLM Top 10 — interview cheat card

Yeh list interview mein aati hai. Har risk + ek-line mitigation yaad rakho:

| Risk | Kya | Mitigation |
|------|-----|------------|
| LLM01 Prompt injection | User/doc rules override kare | Defense-in-depth (§4) |
| LLM02 Insecure output handling | Output bina validate downstream mein | Schema validate; never trust output in SQL/HTML/shell |
| LLM03 Training data poisoning | Bad data se model corrupt | Vet data sources; provenance |
| LLM04 Model DoS | Mehenge/infinite requests | Rate limit + max tokens + loop guards (02, 07) |
| LLM05 Supply chain | Compromised model/plugin/MCP | Pin versions, vet MCP servers (08) |
| LLM06 Sensitive info disclosure | PII/secrets leak | PII redaction in+out; secrets not in prompt |
| LLM07 Insecure plugin/tool design | Over-permissioned tools | Least privilege + allowlist (06, 09) |
| LLM08 Excessive agency | Agent bina control write kare | HITL + scoped tools (09) |
| LLM09 Overreliance | Confident-galat jawab pe bharosa | Groundedness check + cite + human review |
| LLM10 Model theft | Weights/prompt exfiltration | Access control, canary, egress rules |

Gaur karo — inme se aadhe risks tumne pehle ke modules mein already mitigate karna seekha (rate limit, HITL, least privilege, PII, allowlist). Yeh module unhe ek **security frame** mein baandhता hai.

> **Ruko, socho:** LLM02 (insecure output handling) ka ek concrete disaster example do. (Jawab: model output ko seedha SQL query mein daal diya — model ne `'; DROP TABLE users; --` generate kiya (ya injection se induce hua) → SQL injection. Output ko parameterize/validate karo, execute mat karo.)

---

### §6. Red-teaming + guardrail evals

Guardrails ko **test** karna padta hai, warna false confidence. **Red-teaming** = jaan-boojh ke attack karna taaki gaps mile. Ek attack suite banao (jailbreak prompts, PII-leak attempts, injection docs, toxic inputs) aur apni guardrails ke against chalao — kitne block hue? Yeh Module 10 ka eval harness hi hai, par "safety cases" pe: pass = attack blocked.

Do metrics balance karne hote hain: **attack catch rate** (kitne attacks ruke — high chahiye) aur **false positive rate** (kitne legit requests galti se block hue — low chahiye). Bahut aggressive guardrail legit users ko block karke product tod deti hai; bahut dheeli attacks pass kar deti hai. Isliye red-team suite + legit suite dono pe measure karo, aur threshold tune karo. Yeh CI mein daal do (Module 10) — koi prompt/guardrail change safety regression na laaye.

> **→ Practice A4** (`RED_TEAM.md`) — 8 attack cases (jailbreak/PII/injection) + har ke against tumhari kaunsi layer defend karti hai.

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge (`TODO` search).
> A1–A3 offline hain — `python <file>.py` chala ke `_check()` pass karao.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §2 | `pii_redactor.py` | `_check()` asserts pass (card/email/phone redacted) |
| A2 | §4 | `injection_detector.py` | `_check()` asserts pass (jailbreak patterns caught) |
| A3 | §3 | `output_validator.py` | `_check()` asserts pass (schema + banned + PII) |
| A4 | §6 | `RED_TEAM.md` | 8 attacks + defending layer each |

### Setup

```bash
cd modules/12-guardrails-safety/practice
python3 -m venv .venv && source .venv/bin/activate
# A1–A3 sirf stdlib (re) — koi install nahi. Production mein presidio/moderation API.
```

---

## Active recall (khud jawab likho NOTES mein)

1. Input vs output guardrails — 2-2 example each?
2. Injection ke against defense-in-depth — 4 layers?
3. OWASP LLM Top-10 mein se 3 risks + mitigation?
4. Guardrail ka attack-catch-rate high karne se product kaise toot sakta hai?

**Chat drill** (optional): "Module 12 — RAG bot ka threat model + guardrail pipeline whiteboard."

---

## Progress checklist

- [ ] §0 terms clear
- [ ] Theory §1–§6 padha
- [ ] Practice A1–A4 pass
- [ ] Redraw challenge
- [ ] Active recall NOTES mein
- [ ] NOTES session log

---

## Optional appendix

- [OWASP Top 10 for LLM Apps](https://owasp.org/www-project-top-10-for-large-language-model-applications/)
- [Microsoft Presidio](https://microsoft.github.io/presidio/) — PII detection/redaction toolkit
- [OpenAI Moderation guide](https://platform.openai.com/docs/guides/moderation)
- Module 04 (injection basics) · 09 (HITL, least privilege) · 10 (safety evals)
