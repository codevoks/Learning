# Module 18 — HuggingFace & Running Open Models

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 17](../17-transformers-scratch/MODULE.md) · Next → [Module 19](../19-agents-first-principles/MODULE.md)

> **Format**: Textbook — §0 terms zero se, prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`
> **Track 3 (internals):** API se aage — open models khud chalao.
> ⏭️ **SKIP for application/product jobs** — sirf jab open models self-host karne hon (cost/privacy). Warna closed API kaafi. Priority: [PRIORITY.md](../../PRIORITY.md).

## At a glance

| | |
|---|---|
| Prerequisites | 00d (embeddings), 17 (transformers), 14 (fine-tuning) |
| Duration | ~3–5 sessions |
| Project? | No |
| Exit test | pipeline vs AutoModel, tokenizer round-trip, open-vs-API decision bina notes ke samjhao |

## Yeh module kis baare mein hai

Ab tak sab **closed API** (OpenAI/Anthropic) tha. Par ek bada AI world **open models** ka hai — Llama, Mistral, Qwen, DeepSeek — jinhe tum download karke khud chala sakte ho. Yeh matter karta hai kyunki: cost (self-host sasta at scale), privacy (data tumhare server pe rehta), control (fine-tune kar sakte ho — Module 14/22), aur latest research access. **HuggingFace** is poore ecosystem ka GitHub hai — models, datasets, aur `transformers` library jo unhe chalाna aasan banati hai. Yeh module tumhe API-user se "open models bhi chalा sakta hoon" wala engineer banata hai.

Ek practical spectrum jo poore module ko anchor karta hai: **easy → control.** HuggingFace `pipeline` ek-line mein model chala deta hai (easy, kam control); `AutoModel`+`AutoTokenizer` full control dete hain (thoda code, poora access); aur production serving (vLLM/Ollama) speed/scale ke liye. Jitni control chahiye, utna neeche jao.

```
find model (Hub) → load (pipeline OR AutoModel+AutoTokenizer) → tokenize → inference → decode
   local (CPU/GPU, quantized) · serve at scale (vLLM / Ollama / TGI)
```

**Redraw challenge**: HuggingFace ecosystem — Hub → transformers (pipeline/AutoModel) → local/serve — bina dekhe banao.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + §1 Why open + §2 Hub | Hub pe ek model card padho |
| 2 | §3 transformers library + §4 Tokenizers | **A1** — `mini_tokenizer.py` |
| 3 | §5 Running local + serving | **A2** — `pipeline_run.py` (API/model) |
| 4 | §6 Open vs API decision | **A3** — `MODEL_CHOICE.md` |

---

## Theory

### §0. Terms pehli baar — Hub, pipeline, tokenizer, quantization

**HuggingFace Hub.** Models, datasets, aur demos ka central repository (GitHub-for-AI). Har model ka ek **model card** hota hai — kya task, size, license, kaise use.

**`transformers` library.** HuggingFace ki Python library jo hazaron models ko ek consistent API se load aur chalाti hai. Do levels: `pipeline` (high-level, easy) aur `AutoModel`/`AutoTokenizer` (low-level, control).

**pipeline.** Ek-line helper — task + model do, kaam ho jaata: `pipe = pipeline("text-generation", model="..."); pipe("Hello")`. Tokenization, inference, decoding sab andar handle. Prototyping ke liye best.

**Tokenizer.** Text ↔ token IDs convert karta hai (Module 00d/17). Har model ka apna tokenizer hota hai (usi ke saath train hua) — isliye model aur tokenizer **match** hone chahiye. `AutoTokenizer.from_pretrained(model)` sahi tokenizer laata hai.

**AutoModel / AutoTokenizer.** "Auto" classes jo model ke naam se sahi architecture/tokenizer auto-load karti hain — tumhe class naam yaad rakhne ki zaroorat nahi. Yeh full control deती hain (raw logits, custom generation).

**Quantization / GGUF.** Model weights ko kam precision (4-bit/8-bit) mein rakhna taaki memory aur cost gire (Module 14 §3). **GGUF** ek popular quantized format hai (llama.cpp/Ollama). Isse bade models consumer hardware pe chal jaate hain.

**Serving — Ollama / vLLM / TGI.** Local/production pe open models serve karne ke tools. **Ollama** — laptop pe ek command se model (dev-friendly). **vLLM / TGI** — high-throughput production serving (batching, KV cache — Module 17 §7).

> **Ruko, socho:** Ek model download kiya par uske saath galat tokenizer use kar liya. Output kaisा hoga? (Jawab: kachra — tokenizer text ko galat token IDs mein todега jo model ne kabhi us arrangement mein nahi dekhe. Model aur uska tokenizer hamesha jodे — isliye `AutoTokenizer.from_pretrained(same_model)`.)

**§0 checkpoint:** (1) pipeline vs AutoModel? (2) Model aur tokenizer match kyun zaroori? (3) Quantization kya bachata hai?

---

### §1. Open models kyun — API ke alawa

Closed API (Module 01) convenient hai par har cheez ke liye best nahi. Open models char reason se matter karte hain: **cost** — high volume pe self-hosted open model API se kaafi sasta ho sakta hai (per-token fee nahi, apni infra); **privacy** — data tumhare server se bahar nahi jaata (regulated industries ke liye zaroori); **control** — tum fine-tune (Module 14/22), quantize, aur customize kar sakte ho; aur **access** — latest research models (DeepSeek, Qwen) aksar pehle open aate hain. Trade-off: tumhe infra chalani padti hai (GPU, serving, ops), aur top closed models (GPT/Claude) aksar quality mein aage rehte hain. Isliye decision context-dependent hai (§6) — par ek engineer ko dono aana chahiye.

---

### §2. The Hub — sahi model dhoondhna

HuggingFace Hub pe lakhon models hain, to filter karna aana chahiye. Task se search karo (`text-generation`, `sentence-similarity`, `automatic-speech-recognition`). Phir model card mein dekho: **size** (parameters — 7B laptop pe chal sakta, 70B nahi bina serious GPU), **license** (commercial use OK? Llama/Apache/MIT alag terms), **task fit** (base vs instruct-tuned — chat ke liye instruct chahiye), aur **popularity/recency** (downloads, likes — battle-tested?). Yeh wahi model-card-reading skill hai jo 00d §8 mein embeddings ke liye dekhi thi, ab generation models ke liye.

---

### §3. transformers library — pipeline vs AutoModel

Do tareeke, easy se control tak. **pipeline** (easy):

```python
from transformers import pipeline
pipe = pipeline("text-generation", model="Qwen/Qwen2.5-0.5B-Instruct")
print(pipe("Explain RAG in one line:", max_new_tokens=40))
```

Ek line — tokenization/inference/decoding sab andar. Prototyping perfect. **AutoModel + AutoTokenizer** (control):

```python
from transformers import AutoModelForCausalLM, AutoTokenizer
tok = AutoTokenizer.from_pretrained(name)
model = AutoModelForCausalLM.from_pretrained(name)
inputs = tok("Hello", return_tensors="pt")
out = model.generate(**inputs, max_new_tokens=40)
print(tok.decode(out[0]))
```

Yahan tum har step dekhte ho — tokenize, model.generate, decode — aur raw logits, sampling params, custom loops access kar sakte ho. Jab tum control chahte ho (research, custom generation, fine-tuning) → AutoModel; jab bas chalana hai → pipeline.

---

### §4. Tokenizers — text ↔ IDs

Tokenizer wo bridge hai jo text ko model ke numbers mein badalta hai (Module 17 §1). Do core ops: **encode** (text → token IDs) aur **decode** (IDs → text). Do cheezein samajhne layak. Ek — **special tokens**: `<bos>` (begin), `<eos>` (end), `<pad>` (padding) jaise markers jo model ko structure batate hain. Do — **chat templates**: instruct models ko messages ek specific format mein chahiye (system/user/assistant markers ke saath); `tokenizer.apply_chat_template(messages)` yeh sahi format bana deta hai (Module 01 ka `messages[]` ka open-model version). Galat template = model confuse. Round-trip property: `decode(encode(text))` lagभग original text wapas dena chahiye (tokenizer sahi kaam kar raha).

> **→ Practice A1** (`mini_tokenizer.py`) — ek chhota tokenizer scratch se (encode/decode + special tokens).

---

### §5. Local pe chalana + serving

**Local run.** Chhote models (0.5B–7B) laptop pe chal jaate hain, khaaskar **quantized** (4-bit) — memory kam. CPU pe slow, GPU (ya Apple Metal) pe fast. Dev ke liye **Ollama** sabse aasan — `ollama run llama3` aur ek local API mil jaati hai (OpenAI-compatible bhi), koi Python setup nahi.

**Serving at scale.** Production mein throughput chahiye — **vLLM** ya **TGI** (Text Generation Inference) use hote hain. Yeh continuous batching (kai requests ek saath) + PagedAttention (efficient KV cache — Module 17 §7) se ek GPU se bahut zyada requests nikaalते hain. Yeh tumhara Module 02/03 gateway ka backend ban sakta hai — API ki jagah apna vLLM endpoint. Interview point: "cost kam karne ke liye maine open model ko vLLM pe self-host kiya with quantization + continuous batching."

---

### §6. Open vs API — decision

Ek clean framework: **API (GPT/Claude) tab** jab best quality chahiye, volume moderate ho, aur infra nahi chalani (fastest to ship). **Open model (self-host) tab** jab volume high ho (cost), data private rehna chahiye (compliance), fine-tuning chahiye (custom behaviour), ya specific open model best fit ho. Bahut mature systems **hybrid** karte hain — complex/rare queries API pe (quality), high-volume simple queries self-hosted open model pe (cost) — bilkul Module 03 ke complexity-router ka extension. Yeh judgment dikhाना ("maine cost vs quality vs compliance trade kiya") tumhe senior engineer dikhाता hai.

> **→ Practice A3** (`MODEL_CHOICE.md`) — 4 scenarios: open vs API vs hybrid + reason.

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge.
> A1 offline — `python mini_tokenizer.py` → `_check()` pass. A2 model-dependent.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §4 | `mini_tokenizer.py` | `_check()` asserts pass (encode/decode round-trip + special tokens) |
| A2 | §3, §5 | `pipeline_run.py` | HF pipeline se ek open model chale (ya Ollama) |
| A3 | §6 | `MODEL_CHOICE.md` | 4 scenarios: open/API/hybrid + reason |

### Setup

```bash
cd modules/18-huggingface-open-models/practice
python3 -m venv .venv && source .venv/bin/activate
# A1 sirf stdlib. A2: pip install transformers torch  (ya Ollama install)
```

---

## Active recall (khud jawab likho NOTES mein)

1. pipeline vs AutoModel — kab kaunsa?
2. Model + tokenizer match kyun zaroori?
3. vLLM production mein ek GPU se zyada throughput kaise nikaalta hai?
4. Open vs API — 2-2 deciding factors?

**Chat drill** (optional): "Module 18 — cost kam karne ke liye open-model serving stack whiteboard."

---

## Progress checklist

- [ ] §0 terms clear
- [ ] Theory §1–§6 padha
- [ ] Practice A1–A3 pass
- [ ] Redraw challenge (HF ecosystem)
- [ ] Active recall NOTES mein
- [ ] NOTES session log

---

## Optional appendix

- [HuggingFace transformers docs](https://huggingface.co/docs/transformers)
- [Ollama](https://ollama.com/) · [vLLM](https://docs.vllm.ai/)
- Module 17 (transformers) · 14 (fine-tuning open models) · 03 (serve as gateway backend)
