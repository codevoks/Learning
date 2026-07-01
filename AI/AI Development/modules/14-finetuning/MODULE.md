# Module 14 — Fine-tuning & Model Customization

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 13](../13-advanced-retrieval/MODULE.md) · Next → [Module 15](../15-voice-multimodal/MODULE.md)

> **Format**: Textbook — §0 terms zero se, prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`
> **Track 2 (advanced):** 00d ka "training awareness" ab decision-ready depth.
> ⭐ **EDGE — §1 decision MUST, baaki skim** — application eng rarely fine-tunes, par "prompt vs RAG vs finetune" interview mein aata hai. Priority: [PRIORITY.md](../../PRIORITY.md).

## At a glance

| | |
|---|---|
| Prerequisites | 00d (training vs inference), 04 (prompts), 05 (RAG), 10 (evals) |
| Duration | ~3–5 sessions |
| Project? | No (par "kya banayein" decision har AI role mein aata hai) |
| Exit test | "prompt vs RAG vs fine-tune" decision + SFT dataset format bina notes ke samjhao |

## Yeh module kis baare mein hai

00d mein tumne dekha ki tumhara kaam mostly inference hai, training "awareness only". Yeh sach hai — par interview mein ek sawaal *hamesha* aata hai: **"prompt engineering, RAG, aur fine-tuning mein kab kaunsa?"** Aur bahut candidates yahan galat jawab dete hain (fine-tune ko default samajh lete hain). Yeh module tumhe wo decision **confidently defend** karna sikhata hai, plus fine-tuning ka enough practical depth ki tum dataset bana sako aur code padh sako — bina ML researcher bane.

Ek line jo poora module baandhti hai: **fine-tuning knowledge nahi sikhata, behaviour sikhata hai.** Naya *fact* chahiye (latest policy, private docs) → RAG. Naya *format/style/task* chahiye (hamesha aise JSON do, is tone mein bolo) → fine-tune. Yeh galat samajhna sabse common mistake hai.

```
Naya requirement?
  ├── "model ko naya knowledge/facts chahiye"      → RAG (Module 05/13)
  ├── "behaviour theek karna hai — 2-3 examples se" → prompt + few-shot (04)
  └── "consistent format/style/task, bahut examples" → fine-tune (yeh module)
```

**Redraw challenge**: prompt vs RAG vs fine-tune decision tree — bina dekhe banao.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + §1 The decision | **A2** — `DECISION.md` (5 scenarios) |
| 2 | §2 SFT + dataset format | **A1** — `build_sft_dataset.py` |
| 3 | §3 LoRA/PEFT + §4 DPO | — |
| 4 | §5 Dataset prep + eval | **A3** — `dataset_quality.py` |
| 5 | §6 Distillation + serving | Recall + NOTES |

---

## Theory

### §0. Terms pehli baar — SFT, LoRA, DPO, distillation

**Base vs instruct model.** **Base model** raw text pe train hua (sirf next-token), instructions follow nahi karta. **Instruct model** (jise tum API se use karte ho) base ko instruction-following ke liye fine-tune kiya gaya. Yani jo model tum use karte ho, wo already fine-tuned hai — tum uske upar aur customize kar sakte ho.

**SFT (Supervised Fine-Tuning).** Sabse common fine-tuning — model ko `(input, desired_output)` pairs dikhाo, wo un jaisा output dena seekh leta hai. Dataset format aksar **chat/JSONL** hota hai (system + user + assistant messages). Yeh "behaviour cloning" hai — tum jo examples doge, model unka pattern seekhega.

**LoRA / PEFT (Parameter-Efficient Fine-Tuning).** Poore model (billions of weights) ko fine-tune karna mehenga hai. **LoRA** ek trick hai — original weights ko **freeze** karo aur sirf chhote "adapter" matrices train karo (total params ka ~1%). Result lagभग full fine-tuning jaisा, par bahut sasta (ek GPU pe possible) aur adapters chhote (MB mein, swap kar sakte ho). Aaj zyादातar fine-tuning LoRA se hoti hai.

**DPO / RLHF (preference tuning).** SFT "yeh sahi output hai" sikhata hai. **Preference tuning** "yeh output us output se behtar hai" sikhata hai — `(prompt, chosen, rejected)` triples se. **RLHF** (reinforcement learning from human feedback) original method tha; **DPO (Direct Preference Optimization)** simpler + popular alternative hai. Yeh tone/helpfulness/safety align karne ke liye use hota hai.

**Distillation.** Ek bade "teacher" model (GPT-4) se ek chhote "student" model ko train karna — teacher ke outputs ko training data bana ke. Result: chhota, sasta, fast model jo specific task pe bade jaisा kaam kare. Cost optimization ka bada lever.

**Catastrophic forgetting.** Fine-tuning ke doubling-edged: model naya task seekhta hai par purani general capabilities bhool sakta hai. Isliye dataset quality/diversity + holdout eval zaroori (§5).

> **Ruko, socho:** Tumhe model ko "aaj ki company policy" sikhani hai jo har hafte badalti hai. Fine-tune karoge? (Jawab: nahi — yeh *knowledge* hai jo badalta rehta hai, isके liye RAG. Fine-tune karoge to har policy change pe re-train karna padega, aur model phir bhi hallucinate kar sakta hai. Fine-tuning behaviour ke liye hai, changing facts ke liye nahi.)

**§0 checkpoint:** (1) Base vs instruct model? (2) LoRA full fine-tuning se sasta kyun? (3) SFT vs DPO — kya-kya sikhate hain?

---

### §1. The decision — prompt vs RAG vs fine-tune

Yeh interview ka classic hai, aur sahi framework yeh hai (order matter karta hai — sasta pehle):

1. **Prompt engineering pehle try karo** (Module 04). Sabse sasta, fastest iteration, koi infra nahi. Achha prompt + few-shot 80% cases solve kar deta hai. Yahan se shuru — hamesha.
2. **RAG jab naya/changing knowledge chahiye** (Module 05/13). Private docs, latest data, facts jinhe cite karna hai. Fine-tune se behtar kyunki facts update karne ke liye sirf DB update karo, re-train nahi — aur sources cite kar sakte ho.
3. **Fine-tune jab behaviour/format consistent chahiye** aur prompt kaafi nahi. Signs: bahut lambा prompt (few-shot examples token budget khा rahe), strict output format jo prompt se reliably nahi aata, ya ek specialized tone/style. Fine-tune se woh behaviour "bake" ho jaata hai — chhota prompt, consistent output, aur kabhi sasta (chhota fine-tuned model bade generic model ki jagah).

Ek key table jo yaad rakhne layak hai:

| Chahiye | Solution | Kyun |
|---------|----------|------|
| Latest/private facts | RAG | Update = DB change, cite-able |
| Thoda behaviour tweak | Prompt + few-shot | Sasta, instant |
| Consistent format/style/task, 100s examples | Fine-tune (SFT) | Behaviour baked, short prompt |
| Tone/safety alignment | DPO | Preference se seekhता |
| Chhota sasta model, ek task | Distillation | Teacher se clone |

**Sabse common galtiyaan:** fine-tuning ko facts sikhane ke liye use karna (wo RAG ka kaam), aur fine-tuning ko default samajhna jab prompt/RAG kaafi tha (mehenga + slow). Interview mein yeh confidently bolna tumhe alag karta hai.

> **→ Practice A2** (`DECISION.md`) — 5 scenarios, har ke liye prompt/RAG/fine-tune + reason.

---

### §2. SFT — dataset format sabse important

SFT ka 90% kaam **dataset** hai (training run to ek API call/script hai). Model utna hi accha hoga jitna tumhara data. Format aksar chat JSONL hota hai — har line ek example, ek conversation:

```json
{"messages": [
  {"role": "system", "content": "You are a support classifier. Reply with one label."},
  {"role": "user", "content": "I was charged twice for my order"},
  {"role": "assistant", "content": "billing_dispute"}
]}
```

Har line mein wahi shape jo tum inference pe use karoge — system (task/persona), user (input), assistant (desired output). Model in examples se pattern seekhता hai: "aise input pe aisा output". Kuch rules: (1) inference format se **exactly match** karo (jo system prompt training mein tha, wahi serve pe), (2) desired output bilkul waisा likho jaisा chahiye (model literally copy karega — galat/inconsistent labels model ko confuse karenge), (3) enough examples (task pe depend — simple classification ~50-100, complex behaviour 1000s).

> **→ Practice A1** (`build_sft_dataset.py`) — raw `(instruction, output)` pairs → chat JSONL format + validate.

---

### §3. LoRA / PEFT — sasti fine-tuning

Poore model ke billions weights update karna GPU + memory ka pahaad hai. **LoRA** ka insight: original weights ko chhedो mat (freeze), unke saath chhote **adapter** matrices jodo aur sirf woh train karo. Yeh total params ka ~0.1–1% hota hai, isliye:

- Ek consumer/single GPU pe fine-tune possible.
- Adapters chhote (MB) — ek base model + kai task-specific adapters swap kar sakte ho.
- Base model intact rehta hai, to catastrophic forgetting kam.

Quality lagभग full fine-tuning jaisी. Aaj managed platforms (OpenAI fine-tuning, Together, etc.) aur open tools (Hugging Face PEFT, Unsloth) sab LoRA-style karte hain. Tumhe khud LoRA math implement nahi karna — samajhna hai ki yeh kya hai aur kyun default hai, taaki config padh sako (rank `r`, `alpha`, target modules jaise terms).

Related — **quantization** (model weights ko kam precision, jaise 4-bit, mein rakhna) memory aur cost aur girata hai (QLoRA = quantized + LoRA). Serving pe bhi quantized models saste hote hain.

---

### §4. Preference tuning (DPO) — behtar vs bura sikhana  ⏭️ SKIP-able

> ⏭️ **Application job ke liye skim** — awareness kaafi; poora RL/DPO depth Module 22 (optional) mein.

SFT ek "sahi answer" sikhata hai, par kuch cheezein absolute-right nahi hoti — helpfulness, tone, safety. Yahan **preference tuning** aata hai: model ko `(prompt, chosen, rejected)` triples do — "is prompt pe yeh output us output se behtar hai". Model preferences seekhता hai, single answers nahi.

**RLHF** original approach tha (reward model + RL — complex). **DPO** ek simpler math trick se wahi effect deta hai bina alag reward model ke, isliye popular ho gaya. Practically: yeh alignment/polish step hai, aksar SFT ke baad. Tumhare liye — samajhna ki yeh exist karta hai aur kab use hota hai (tone/safety/helpfulness align), implement karna abhi zaroori nahi.

---

### §5. Dataset prep + eval — quality > quantity

Fine-tuning ka result 100% data quality pe hai. Char cheezein:

- **Quality** — har example accurate aur consistent ho. 100 clean examples 1000 shor (noisy) examples se behtar. Ek galat label model ko galat pattern sikhaता hai.
- **Dedup** — duplicate examples model ko un pe overfit kara dete hain aur eval ko jhutha inflate karte hain (agar dup train aur holdout dono mein aaye). Exact + near-dup hatao.
- **Holdout split** — data ka ek hissa (jaise 20%) train se alag rakho, sirf eval ke liye. **Zaroori** ki train aur holdout mein overlap na ho, warna tumhare eval scores jhoothe (model ne wo example dekh liya tha).
- **Diversity** — examples task ke edge cases cover karein, sab ek jaise nahi (warna catastrophic forgetting + narrow model).

Aur eval — fine-tune ke baad Module 10 ka harness chalao: holdout pe pass-rate, aur general capability na toot-ne ka check (kuch off-task prompts). "Fine-tune ne task accuracy 82%→94% ki, general benchmark 2% gira" — yahi defendable result hai.

> **Ruko, socho:** Tumne dataset dedup nahi kiya aur ek example train + holdout dono mein aa gaya. Eval pe kya galat dikhega? (Jawab: eval score jhootha high aayega — model ne wo example training mein "dekh" liya, to holdout pe use "yaad" hai, seekha nahi. Dedup + strict train/holdout split isliye zaroori.)

> **→ Practice A3** (`dataset_quality.py`) — dedup + clean + deterministic train/holdout split.

---

### §6. Distillation + serving

**Distillation** cost ka bada lever hai. Ek bada model (GPT-4) tumhare task pe accha hai par mehenga. Uske outputs ko training data bana ke ek chhote model ko fine-tune karo — ab chhota model us task pe bade jaisा, par 10-50x sasta aur fast. Yeh "capability ko compress" karna hai. YC startups aksar prototype GPT-4 pe karte hain, phir hot paths ko distilled chhote model pe le jaate hain (margin ke liye).

Serving pe: fine-tuned/open models ko host karna padta hai (managed endpoint ya khud vLLM/TGI se). Yahan quantization (§3) + batching latency/cost manage karte hain. Yeh AI-infra territory hai — tumhare liye awareness kaafi, par "cost kam karne ke liye distill + quantize + self-host" ek strong interview point hai.

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge.
> A1, A3 offline — `python <file>.py` → `_check()` pass. A2 written.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §2 | `build_sft_dataset.py` | `_check()` asserts pass (chat JSONL format) |
| A2 | §1 | `DECISION.md` | 5 scenarios: prompt/RAG/finetune + reason |
| A3 | §5 | `dataset_quality.py` | `_check()` asserts pass (dedup + split, no leak) |

### Setup

```bash
cd modules/14-finetuning/practice
python3 -m venv .venv && source .venv/bin/activate
# A1, A3 sirf stdlib. (Actual fine-tuning: OpenAI/Together/HF PEFT — awareness.)
```

---

## Active recall (khud jawab likho NOTES mein)

1. Prompt vs RAG vs fine-tune — decision framework (order + trigger each)?
2. Fine-tuning changing facts ke liye kyun galat hai?
3. LoRA full fine-tuning se sasta + flexible kyun?
4. Train/holdout overlap se eval kyun jhootha?

**Chat drill** (optional): "Module 14 — 3 scenarios pe prompt/RAG/finetune defend karo."

---

## Progress checklist

- [ ] §0 terms clear
- [ ] Theory §1–§6 padha
- [ ] Practice A1–A3 pass
- [ ] Redraw challenge (decision tree)
- [ ] Active recall NOTES mein
- [ ] NOTES session log

---

## Optional appendix

- [OpenAI Fine-tuning guide](https://platform.openai.com/docs/guides/fine-tuning)
- [Hugging Face PEFT / LoRA](https://huggingface.co/docs/peft)
- [DPO paper (intuition)](https://arxiv.org/abs/2305.18290)
- Module 00d (training vs inference) · 04 (prompts) · 05 (RAG) · 10 (evals)
