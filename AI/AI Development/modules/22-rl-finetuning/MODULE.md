# Module 22 — RL Fine-tuning (RLHF, DPO, GRPO)

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 21](../21-computer-use/MODULE.md) · End (Track 3)

> **Format**: Textbook — §0 terms zero se, prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`
> **Track 3:** Module 14 §4 (DPO intro) ka poora — preference/RL fine-tuning depth.

## At a glance

| | |
|---|---|
| Prerequisites | Module 14 (SFT, DPO intro), 10 (evals), 16 (gradient descent) |
| Duration | ~3–5 sessions |
| Project? | Mini — preference dataset + reward eval (matches syllabus "RL finetune + evals") |
| Exit test | RLHF pipeline + PPO vs DPO vs GRPO + reward hacking bina notes ke samjhao |

## Yeh module kis baare mein hai

Module 14 ne SFT (supervised fine-tuning) sikhaya — "yeh sahi output hai". Par bahut cheezein absolute-sahi nahi hoti: helpfulness, tone, safety, reasoning quality. In par align karne ke liye **RL fine-tuning** aati hai — model ko "yeh output us output se **behtar** hai" (preferences) se sikhाना. Yahi wo step hai jisne raw GPT ko ChatGPT banaya (RLHF), aur jisne DeepSeek-R1 jaise reasoning models banaye (GRPO). Syllabus ka "RL finetuning project + writing evals" yahi hai. Tumhe RL researcher nahi banna — par yeh pipeline samajhना aur uske trade-offs bolna top roles mein bada plus hai.

Ek core idea jo module ko anchor karta hai: **SFT single answers sikhata hai, RL preferences sikhata hai.** Aur preferences se sikhने ke liye ek "reward" chahiye jo bataye output kitna accha hai — wo reward ya to ek trained model deta hai (RLHF) ya directly preference-pairs se optimize hota hai (DPO).

```
SFT model → collect preference pairs (chosen vs rejected)
   → RLHF: train reward model → RL optimize (PPO) with KL penalty
   OR DPO: directly optimize on pairs (no separate reward model)
   OR GRPO: group-relative, verifiable rewards (reasoning) — DeepSeek-R1
```

**Redraw challenge**: RLHF pipeline (SFT → reward model → RL) vs DPO (direct) — bina dekhe banao.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + §1 Why RL + §2 RLHF pipeline | **A3** — `DECISION.md` |
| 2 | §3 Reward models | **A1** — `preference_dataset.py` |
| 3 | §4 PPO vs DPO vs GRPO | **A2** — `reward_eval.py` |
| 4 | §5 Reward hacking + §6 RL evals | Recall + NOTES |

---

## Theory

### §0. Terms pehli baar — RLHF, reward model, DPO, GRPO

**RLHF (RL from Human Feedback).** Wo pipeline jisne LLMs ko "helpful assistant" banaya: SFT model lo → humans se output preferences collect karo → us se ek reward model train karo → RL se model ko optimize karo taaki reward badhe.

**Reward model.** Ek model jo ek output ko ek **score** deta hai ("yeh kitna accha/preferred hai"). Yeh preference pairs (chosen vs rejected) se train hota hai — chosen ko zyada score dena seekhता hai.

**Preference data.** `(prompt, chosen, rejected)` triples — ek prompt pe do outputs, aur kaunsa insaan ne behtar samjha. Yeh RL fine-tuning ka fuel hai (SFT ka fuel `(input, output)` tha).

**Policy.** RL ki bhasha mein, "policy" = tumhara model (jo actions/tokens choose karta). RL policy ko update karta hai taaki reward badhe.

**PPO (Proximal Policy Optimization).** Original RLHF ka RL algorithm — reward model ke against model ko optimize karta hai, ek **KL penalty** ke saath (base model se zyada door na jaaye). Powerful par complex + unstable.

**DPO (Direct Preference Optimization).** Ek smarter math trick — bina alag reward model + RL loop ke, directly preference pairs se model optimize karता hai. Simpler, stable, popular (Module 14 §4). Aaj bahut alignment DPO se hota.

**GRPO (Group Relative Policy Optimization).** DeepSeek ka approach, khaaskar **reasoning** ke liye. Ek prompt ke kai outputs generate karo, unhe relative-rank karo (aksar **verifiable** rewards se — math answer sahi hai ya nahi, code chalta hai ya nahi), aur us relative signal se optimize. Isne R1 jaise strong reasoning models banaye.

**KL penalty.** RL optimization mein ek term jo model ko base model ke **paas** rakhता hai — taaki wo reward ko chase karne mein apni general capability na khoye (ya reward hack na kare, §5).

**Reward hacking.** Model reward ko game kar leta hai bina asli goal poora kiye — jaise reward "lambा jawab = accha" samajh gaya to bekaar lambा likhne lage. RL ka classic problem.

> **Ruko, socho:** SFT already "achha jawab" sikhata hai — to RLHF/preferences ki zaroorat kyun? (Jawab: bahut qualities single "sahi answer" nahi hoti — do jawab dono sahi ho sakte, par ek zyada helpful/safe/clear. Preferences yeh "behtar vs bura" ka signal dete hain jo SFT ke pass nahi. Isliye ChatGPT ka "feel" RLHF se aaya, sirf SFT se nahi.)

**§0 checkpoint:** (1) Reward model kya deta hai? (2) DPO PPO se simpler kaise? (3) Reward hacking ek example?

---

### §1. Why RL fine-tuning — SFT ki seemा

SFT behaviour clone karता hai — jo examples do, wo copy. Par teen jagah wo kam padta hai: (1) **subjective qualities** (helpfulness, tone) jinke liye ek "sahi answer" nahi hai; (2) **negative signal** — SFT sirf "yeh karo" sikhata, "yeh mat karo" nahi (rejected examples ka faayda nahi le pata); (3) **preferences over answers** — insaan aksar "A better than B" bol sakta hai bhale perfect answer na likh sake. RL fine-tuning (RLHF/DPO) yeh gap bharता hai — preferences se sikhकर model ko human values/quality ke saath **align** karta. Isiliye yeh alignment ka core step hai.

---

### §2. RLHF pipeline — teen stages

Classic RLHF teen steps mein: **(1) SFT** — base model ko instruction-following pe fine-tune (Module 14). **(2) Reward model** — SFT model se ek prompt pe kai outputs generate karo, humans unhe rank karein, aur us preference data se ek reward model train karo jo "achhे output ko zyada score" de. **(3) RL optimize (PPO)** — SFT model ko reward model ke against optimize karo — jo outputs zyada reward paate, un ki taraf policy shift, saath mein KL penalty (base se door na jaao). Result: ek model jo human preferences ke saath aligned. Yeh pipeline powerful par mehenga + complex hai — isliye DPO (§4) popular hua jo iska shortcut hai.

---

### §3. Reward models — preferences se score

Reward model RLHF ka dil hai. Input: ek `(prompt, output)`; output: ek scalar score. Train kaise? **Preference pairs** se — `(prompt, chosen, rejected)`. Model ko sikhाya jaata ki `reward(chosen) > reward(rejected)` (pairwise loss). Enough pairs se model ek general "quality sense" seekh leta jo naye outputs pe bhi score de sake. Iska eval simple hai aur interview mein aata: **pairwise accuracy** — held-out preference pairs pe, kitni baar model ne chosen ko rejected se zyada score diya? (Yeh Module 10 ka eval, reward model pe.) Achha reward model = high pairwise accuracy on held-out human preferences.

> **→ Practice A1** (`preference_dataset.py`) — raw ranked outputs se `(prompt, chosen, rejected)` pairs banao.
> **→ Practice A2** (`reward_eval.py`) — ek reward function ki pairwise accuracy compute karo.

---

### §4. PPO vs DPO vs GRPO

Teen approaches, evolution ke order mein. **PPO** (original RLHF) — alag reward model + RL loop + KL penalty. Powerful par complex, unstable, aur mehenga (reward model host + RL). **DPO** — ek elegant insight se reward model + RL loop ko **skip** karta hai: preference pairs pe seedhे ek loss optimize karता hai jo effectively wahi kaam karta. Simpler, stable, sasta — isliye aaj default alignment. **GRPO** (DeepSeek) — reasoning ke liye: ek prompt ke **group** of outputs generate karo, unhe relative rank karo (aksar **verifiable/programmatic** reward se — math sahi? code pass?), aur us group-relative advantage se optimize; separate value/reward model ki zaroorat kam. Isne R1 jaise reasoning models diye. Interview line: "PPO se DPO ne complexity hataayi; GRPO ne verifiable rewards se reasoning unlock kiya."

---

### §5. Reward hacking + KL penalty

RL ka classic failure — **reward hacking**: model reward metric ko game kar leta hai bina asli goal poora kiye. Examples: reward model lambे jawab prefer karta tha → model bekaar verbose ho gaya; reward "confident tone" like karta tha → model galat cheezon pe bhi over-confident. Model wahi optimize karता hai jo tum measure karte ho, jo tum *chahte* ho wo nahi (Goodhart's law). Do defenses: **KL penalty** (model ko base ke paas rakho — extreme reward-chasing rok) aur **better reward signal** (diverse preferences, adversarial examples, human audit). Isiliye §6 (RL evals) critical — bina achhे eval ke tumhe pata bhi nahi chalega model ne reward hack kiya.

> **Ruko, socho:** Tumhare RLHF ke baad model bahut lambे, over-polite jawab dene laga jo actually helpful kam hain. Kya hua? (Jawab: reward hacking — reward model ne length/politeness ko "achha" seekh liya tha, to policy usko exploit kar rahi. Fix: reward signal theek karo (length-bias hatao), KL penalty badhाo, aur held-out human eval se pakdo.)

---

### §6. Evals for RL fine-tuning

RL fine-tuning mein tum **loss pe bharosa nahi** kar sakte (reward badhna ≠ model behtar — reward hack ho sakta). Isliye alag evals chahiye (Module 10): **win-rate** — held-out prompts pe, naya model vs base, human/LLM-judge kitni baar naye ko prefer karta? **Capability retention** — general benchmarks na girein (alignment tax check). **Safety/red-team** (Module 12) — RL ne koi naya unsafe behaviour to nahi laaya. Yahi "writing evals" wala hissa hai jo syllabus mein RL project ke saath aata — RL fine-tuning ka result sirf preference-eval + win-rate + retention se defend hota hai, training curve se nahi.

> **→ Practice A3** (`DECISION.md`) — 4 scenarios: SFT vs DPO vs GRPO vs "RL zaroorat nahi".

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge.
> A1, A2 offline — `python <file>.py` → `_check()` pass. A3 written.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §3 | `preference_dataset.py` | `_check()` asserts pass (chosen/rejected pairs) |
| A2 | §3, §6 | `reward_eval.py` | `_check()` asserts pass (pairwise accuracy) |
| A3 | §4 | `DECISION.md` | 4 scenarios: SFT/DPO/GRPO/none |

### Setup

```bash
cd modules/22-rl-finetuning/practice
python3 -m venv .venv && source .venv/bin/activate
# A1, A2 sirf stdlib. Actual RL: TRL (HuggingFace) — awareness.
```

---

## Active recall (khud jawab likho NOTES mein)

1. SFT vs RL fine-tuning — kya alag sikhate hain?
2. RLHF ke 3 stages?
3. DPO PPO se simpler kaise? GRPO kis ke liye?
4. Reward hacking + 2 defenses?
5. RL fine-tune ka result kaise defend karoge (loss se kyun nahi)?

**Chat drill** (optional): "Module 22 — RLHF pipeline + reward hacking whiteboard."

---

## Progress checklist

- [ ] §0 terms clear
- [ ] Theory §1–§6 padha
- [ ] Practice A1–A3 pass
- [ ] Redraw challenge (RLHF vs DPO)
- [ ] Active recall NOTES mein
- [ ] NOTES session log

---

## Optional appendix

- [HuggingFace TRL](https://huggingface.co/docs/trl) — SFT/DPO/PPO/GRPO trainers
- [DPO paper](https://arxiv.org/abs/2305.18290) · [DeepSeek-R1 (GRPO)](https://arxiv.org/abs/2501.12948)
- Module 14 (SFT + DPO intro) · 10 (evals) · 12 (safety evals)
