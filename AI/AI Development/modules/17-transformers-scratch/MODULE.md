# Module 17 — Transformers & Attention from Scratch

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 16](../16-dl-foundations/MODULE.md) · Next → [Module 18](../18-huggingface-open-models/MODULE.md)

> **Format**: Textbook — §0 terms zero se, prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`
> **Track 3 (internals):** Yeh wo module hai jo "LLM kaise kaam karta hai" ka jawab deta hai. Top-lab interviews mein sabse zyada poochha jaata hai.

## At a glance

| | |
|---|---|
| Prerequisites | Module 16 (NN, softmax), 00d (embeddings), NumPy |
| Duration | ~5–7 sessions (attention ko dheere samjho) |
| Project? | No (par "explain attention" har senior interview mein) |
| Exit test | Self-attention (Q/K/V) + causal mask + KV cache bina notes ke whiteboard karo |

## Yeh module kis baare mein hai

Yeh **poore course ka sabse important internals module** hai. Har LLM — GPT, Claude, Llama — andar se ek **transformer** hai, aur transformer ka dil **attention** hai. Ab tak tumne model ko API se use kiya; ab tum attention ko NumPy mein **scratch se** banaoge. Jab interviewer poochhega "attention explain karo" (aur senior/lab roles mein wo *zaroor* poochhega), tum white-board pe Q/K/V likhкar bata paoge — yahi tumhe "API user" se "engineer jo internals jaanता hai" banata hai.

Ek core intuition jo poore module ka anchor hai — **attention ek soft, learned lookup hai.** Har token poochhता hai "mujhe kya chahiye?" (query), har token batata hai "mere paas kya hai?" (key), aur jinke key query se match karte hain, unki value zyada weight se mix hoti hai. Bas — yahi Q/K/V hai. Baaki sab (multi-head, positional, block) is idea ke upar layers hain.

```
tokens → embeddings → [ SELF-ATTENTION: Q·Kᵀ → softmax → weighted sum of V ]
                       + multi-head + positional + FFN + residual + layernorm  (× N layers)
                     → next-token prediction
   Inference: KV cache (recompute bachao) · GQA/MLA (memory bachao)
```

**Redraw challenge**: ek token ke liye Q/K/V → attention scores → softmax → value mix — bina dekhe banao.

---

## Read order (strict — jaldi mat karna)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + §1 Tokens → vectors | Terminal pe embedding shape socho |
| 2 | §2 Self-attention (dheere) | **A1** — `attention.py` |
| 3 | §3 Multi-head + §4 Positional | — |
| 4 | §5 Transformer block + §6 Causal mask | **A2** — `causal_mask.py` |
| 5 | §7 KV cache, GQA, MLA | **A3** — `kv_cache.py` |

---

## Theory

### §0. Terms pehli baar — Q/K/V, attention, KV cache

**Token embedding.** Har token (Module 00d) ek learnable vector ban jaata hai — ek bade "embedding matrix" se lookup. Yeh vector hi network ke andar chalta hai.

**Query, Key, Value (Q/K/V).** Attention ka dil. Har token ke embedding se teen alag vectors bante hain (teen learned weight matrices se): **query** (yeh token "kya dhoondh raha"), **key** ("yeh token kya offer karta"), **value** ("yeh token aage kya info pass karega"). Library analogy: query = tumhari search request, key = har kitab ka title/tag, value = kitab ka content. Query jis key se match kare, us value ko zyada lo.

**Attention score.** Ek token ki query aur doosre token ki key ka **dot product** — kitna match karte hain. Zyada dot product = zyada relevant.

**Scaled dot-product attention.** Poora attention ek formula mein: `softmax(Q·Kᵀ / √d) · V`. Q·Kᵀ saare token-pairs ke scores; `√d` se divide (scaling — bade d pe dot products bade ho jaate, softmax ko saturate karne se rokta); softmax scores ko probabilities banata (har query ke liye rows sum to 1); phir un weights se values ka **weighted average**. Yeh ek line poore transformer ka core hai.

**Multi-head.** Ek attention ke bajaye kai "heads" parallel — har head alag Q/K/V projections, alag tarah ke relationships pakadta hai (ek head syntax, ek coreference, etc.). Sab heads ka output jod ke aage bhejا jaata.

**Positional encoding.** Attention **order-blind** hai (weighted average mein order nahi) — to token ki position alag se inject karni padti hai (sinusoidal ya RoPE).

**Causal mask.** Decoder-only LLMs (GPT-style) mein ek token sirf **apne aur pichle** tokens ko dekh sakta hai, future ko nahi (kyunki wo next token predict kar raha, future dekhna cheating). Mask future positions ke scores ko `-∞` kar deta hai (softmax mein 0).

**KV cache / GQA / MLA.** Inference speedups (§7). **KV cache** — generation mein har naye token pe purane K,V dobara compute mat karo, cache karo. **GQA (Grouped-Query Attention)** — kai query heads ek KV set share karein (memory bachao). **MLA (Multi-head Latent Attention)** — KV ko compress karke store karo (DeepSeek).

> **Ruko, socho:** Attention mein `√d` se divide kyun karte hain? (Jawab: `d` (head dimension) bada hone pe Q·K dot products magnitude mein bade ho jaate hain, jisse softmax bahut "peaky"/saturated ho jaata (ek pe ~1, baaki ~0) aur gradients chhote. `√d` se scale karne se scores reasonable range mein rehte, training stable.)

**§0 checkpoint:** (1) Q/K/V ek line mein each? (2) Causal mask kyun chahiye? (3) KV cache kya bachata hai?

---

### §1. Tokens se vectors tak

Text pehle **tokens** mein tut-ta hai (Module 00d — BPE-style subwords), phir har token ID ek **embedding matrix** se ek vector uthata hai (matrix ki shape `[vocab_size, d_model]`). Yeh embeddings learnable hain — training inhe aisा arrange karti hai ki similar-meaning tokens paas aayein. Ab poora sentence ek matrix ban gaya: `[seq_len, d_model]` (har row ek token ka vector). Sab kuch aage isi shape mein chalega — attention isi matrix pe operate karta hai. Bas yaad rakho: raw text → token IDs → vectors matrix → (attention layers) → output.

---

### §2. Self-attention scratch se — THE core

Yeh section slow padho, yahi poora module hai. Har token ke vector se teen projections banao (teen weight matrices `Wq, Wk, Wv`): `Q = X·Wq`, `K = X·Wk`, `V = X·Wv` — teeno shape `[seq, d]`. Ab magic:

```
scores   = Q · Kᵀ            # [seq, seq] — har token-pair ka match
scores   = scores / √d        # scaling (§0)
weights  = softmax(scores)    # har row (query) ke weights sum = 1
output   = weights · V        # har token ka naya vector = values ka weighted mix
```

Ise intuition se todo. `Q·Kᵀ` ek `[seq, seq]` matrix deta hai — row `i`, column `j` = token `i` ki query aur token `j` ki key ka match. Softmax har row ko probability distribution banata hai ("token i apna attention kaise baante saare tokens pe"). Phir `weights · V` — token `i` ka naya representation = saare tokens ki values ka weighted average, jinke saath wo zyada attend karta unki zyada. Result: har token ab **context-aware** ho gaya — usme us sentence ke relevant doosre tokens ki info mix ho gayi. "Bank" ka vector ab "river" ke paas alag hai vs "money" ke paas — kyunki attention ne context mix kiya.

Yahi **self**-attention hai (Q,K,V sab same sequence se). Poore sentence ke saare tokens ke liye yeh ek saath (parallel) hota hai — yahi wo parallelism hai jisne transformers ko scale karne diya (Module 16 §6).

> **Ruko, socho:** Agar tum `Q·Kᵀ` ke baad softmax **na** karo aur seedhe `scores·V` kar do, to kya toot jaayega? (Jawab: weights probabilities nahi rahenge (sum≠1, negative bhi) — "weighted average" ka matlab hi chala jaayega, output scale explode/collapse ho sakta. Softmax scores ko clean attention-distribution mein badalta hai.)

> **→ Practice A1** (`attention.py`) — scaled dot-product attention NumPy mein.

---

### §3. Multi-head attention — kai rishtे parallel

Ek single attention ek tarah ka relationship pakadta hai. Par language mein kai tarah ke rishtे hote hain ek saath — grammar, coreference ("it" kis cheez ko refer karta), topic. **Multi-head** isliye: `d_model` ko `h` heads mein baanto, har head apni chhoti Q/K/V projections se **independent** attention kare (alag rishtे seekhे), phir sab heads ke outputs concatenate karke ek final projection se guzaro. Practically — ek matrix operation mein reshape karke saare heads parallel compute hote hain. Faayda: model ek layer mein hi kai "views" of relationships capture karता hai, ek single averaged view ke bajaye.

---

### §4. Positional encoding — order kaise inject karein

Ek subtle par critical baat: attention **order nahi jaanता**. `weights·V` ek weighted *set* operation hai — agar tum tokens ko shuffle kar do (aur positions ke saath), output same aayega. Par "dog bites man" ≠ "man bites dog" — order matter karta hai. Isliye har token ke embedding mein uski **position** ki info add ki jaati hai.

Do common tareeke: **sinusoidal** (original — har position ka ek fixed sin/cos pattern, embedding mein add), aur **RoPE (Rotary Position Embedding)** (aaj popular — Q/K ko position ke hisaab se "rotate" karta, relative positions naturally aate). Tumhe abhi math implement nahi karna — samajhना ki attention ko position batani padti hai warna wo bag-of-words jaisा ho jaata, aur RoPE aaj default hai (Llama/most modern LLMs).

---

### §5. Transformer block — attention ke aas-paas kya

Attention akela transformer nahi. Ek **transformer block** mein attention ke saath teen aur cheezein hoti hain, aur yeh N baar stack hoti hain:

- **Feed-forward network (FFN)** — attention ke baad har token pe ek chhota MLP (do linear layers + activation). Attention tokens ke *beech* info mix karta hai; FFN har token ke *andar* processing karta hai. Dono zaroori.
- **Residual connections** — har sub-layer ka input uske output mein add hota hai (`x + attention(x)`). Yeh deep networks ko trainable banata hai (gradient ka "shortcut" — Module 16 vanishing-gradient ka fix).
- **Layer normalization** — har sub-layer ke aas-paas normalize (stable training).

Poora ek block: `x → x + attention(norm(x)) → x + ffn(norm(x))`. Yeh block 12, 32, 80+ baar stack hota hai (model size). Aakhir mein ek linear layer vocab pe project karke **next-token probabilities** deta hai. Yahi poora GPT-style transformer hai — attention + FFN + residual + norm, bar-bar.

---

### §6. Causal masking + autoregressive generation

Modern LLMs **decoder-only** hain aur **autoregressive** — ek-ek token generate karte hain, aur har token predict karte waqt sirf **pichle** tokens dekh sakte hain (future nahi — wo to abhi bana hi nahi, aur training mein future dekhna cheating hoti). Ise **causal mask** enforce karta hai: attention scores matrix mein, har query ke liye future positions (jo uske right mein hain) ko `-∞` set kar do — softmax unhe 0 kar dega, to wo attend nahi honge.

```
scores (before softmax), causal mask laga:
        t0    t1    t2
 t0 [  s00  -∞    -∞  ]      t0 sirf t0 dekhta
 t1 [  s10  s11   -∞  ]      t1 t0,t1 dekhta
 t2 [  s20  s21   s22 ]      t2 sab dekhta
```

Generation mein: prompt process karo → next token predict → wo token append → dobara → jab tak stop. (Yahi wo `messages[]` loop hai jo tumne Module 01 mein bahar se dekha tha — ab andar se.)

> **→ Practice A2** (`causal_mask.py`) — lower-triangular causal mask banao.

---

### §7. Inference optimizations — KV cache, GQA, MLA

Yeh production LLM serving ka dil hai aur interview mein aata hai.

**KV cache — kyun.** Generation mein tum ek-ek token banate ho. Har naye token pe, agar tum poora attention dobara compute karo, to purane tokens ke K aur V bar-bar recompute honge — wasteful (O(n²) generation). Insight: purane tokens ke K,V badalte nahi. To unhe **cache** karo; har naye token pe sirf uska naya K,V compute karke cache mein append karo, aur query us poore cache pe attend kare. Isse generation O(n²) se O(n) ho jaati — LLM serving fast hoti hai. Trade: cache memory khata hai (har token, har layer, har head ka K,V), aur yahi memory bottleneck GQA/MLA ka reason hai.

**GQA (Grouped-Query Attention).** KV cache ki memory kam karne ka trick. Full multi-head mein har query head ka apna K,V hota hai. GQA mein kai query heads ek K,V set **share** karते hain (groups mein) — KV cache chhota, memory kam, thodi quality trade. Llama-2/3 GQA use karte hain — isliye wo long context efficiently serve karte hain.

**MLA (Multi-head Latent Attention).** DeepSeek ka approach — K,V ko ek chhote "latent" space mein **compress** karke store karo, use pe decompress. GQA se aur aggressive memory saving, quality bachाते hue. Yeh cutting-edge hai; tumhe naam + idea (KV compression) jaanna kaafi.

Teeno ka common thread: **attention ka core same, bas KV ko store/share/compress karne ke tricks** taaki long-context serving memory-efficient ho.

> **Ruko, socho:** Bina KV cache ke, 1000-token jawab generate karne mein har token pe kitne tokens ka attention recompute hota (roughly)? (Jawab: token `n` pe ~n tokens ka K,V — total ~1+2+...+1000 ≈ O(n²) recompute. KV cache is repeat compute ko hataता hai, sirf naye token ka K,V add hota. Yahi generation ko practical banata hai.)

> **→ Practice A3** (`kv_cache.py`) — KV cache append/grow logic.

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge.
> A1–A3 offline (NumPy) — `python <file>.py` → `_check()` pass.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §2 | `attention.py` | `_check()` asserts pass (scaled dot-product + weights sum 1) |
| A2 | §6 | `causal_mask.py` | `_check()` asserts pass (lower-triangular mask) |
| A3 | §7 | `kv_cache.py` | `_check()` asserts pass (append + grow) |

### Setup

```bash
cd modules/17-transformers-scratch/practice
python3 -m venv .venv && source .venv/bin/activate
pip install numpy
```

---

## Active recall (khud jawab likho NOTES mein)

1. Q/K/V — ek library analogy se samjhao.
2. `√d` scaling kyun?
3. Positional encoding kyun zaroori — attention ki kaunsi property?
4. KV cache generation ko O(n²) se O(n) kaise banata hai?
5. GQA vs MLA — dono kya bachate hain?

**Chat drill** (optional): "Module 17 — self-attention forward pass whiteboard, Q/K/V se output tak."

---

## Progress checklist

- [ ] §0 terms clear
- [ ] Theory §1–§7 padha (attention dheere)
- [ ] Practice A1–A3 pass
- [ ] Redraw challenge (Q/K/V → output)
- [ ] Active recall NOTES mein
- [ ] NOTES session log

---

## Optional appendix

- [Attention is All You Need](https://arxiv.org/abs/1706.03762) — original paper
- [The Illustrated Transformer](https://jalammar.github.io/illustrated-transformer/) — visual gold
- [Andrej Karpathy — Let's build GPT](https://www.youtube.com/watch?v=kCc8FmEb1nY) — scratch se, must-watch
- Module 16 (foundations) · 18 (HuggingFace — real models chalao)
