# Module 16 — DL Foundations & the Road to Transformers

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 15](../15-voice-multimodal/MODULE.md) · Next → [Module 17](../17-transformers-scratch/MODULE.md)

> **Format**: Textbook — §0 terms zero se, prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`
> **Track 3 (foundations & internals):** LLM ko black-box API se aage — andar kya chal raha hai. Top labs (OpenAI/Anthropic) yeh depth poochhte hain.
> ⏭️ **SKIP for application/product jobs** — products build karne ke liye nahi chahiye; "kaise kaam karta" curiosity / lab-interview ke liye. Priority: [PRIORITY.md](../../PRIORITY.md).

## At a glance

| | |
|---|---|
| Prerequisites | 00d (ML terms), 00b (Python), NumPy comfort |
| Duration | ~4–6 sessions |
| Project? | No (Module 17 transformers ki neev) |
| Exit test | Backprop + gradient descent + "recurrence se attention tak kyun" bina notes ke samjhao |

## Yeh module kis baare mein hai

Ab tak tumne LLM ko ek **API** ki tarah use kiya — andar kya hai, pata nahi tha. 01–15 ke liye wo theek tha (application eng). Par jab interviewer (khaaskar top labs) poochhta hai "attention actually kaam kaise karta hai?" ya "model seekhta kaise hai?" — wahan yeh track kaam aata hai. Yeh module us neev ko banata hai: neural network kya hai, wo **seekhता kaise** hai (backprop + gradient descent), aur **kyun** hum RNN/LSTM se transformers tak pahunche. Module 17 mein isi neev pe attention scratch se banaoge.

Ek bada arc jo poore module ko baandhta hai: **"AI" ka matlab pehle hardcoded rules the → phir ML (data se seekho) → phir DL (neural nets, features khud seekho) → phir NLP mein sequence models (RNN/LSTM) → phir transformers (attention).** Har step pichle ki ek seemा tod ke aaya. Yeh kahani samajhna tumhe har cheez ko "kyun aisा" ke saath samajhने deta hai.

```
Rules (if/else) → ML (learn from data) → DL (neural nets, learn features)
   → RNN/LSTM (sequences, but slow + short memory) → Transformers (attention: parallel + long-range)
```

**Redraw challenge**: yeh evolution timeline + har step ki jo seemा agle ne todi — bina dekhe banao.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + §1 AI→ML→DL history | Timeline NOTES mein |
| 2 | §2 Neural network from scratch | **A1** — `neuron_forward.py` |
| 3 | §3 Backprop + gradient descent | **A2** — `gradient_descent.py` |
| 4 | §4 NLP: word2vec → RNN → LSTM | **A3** — `softmax_ce.py` |
| 5 | §5 CNN (brief) + §6 Road to transformers | Recall + redraw |

---

## Theory

### §0. Terms pehli baar — neuron, backprop, gradient

**Neuron.** DL ka sabse chhota unit. Ek neuron kuch inputs leta hai, har ko ek **weight** se multiply karta hai, sab jodता hai, ek **bias** add karta hai, aur phir ek **activation function** se guzarta hai. Bas — `output = activation(Σ(input·weight) + bias)`. Yeh ek line ka math poore deep learning ka atom hai.

**Weights & bias.** Yeh wo **learnable numbers** hain jo training badalti hai (00d ka "weights"). Weight batata hai ek input kitna important hai; bias ek offset hai. Model "seekhna" = in numbers ko adjust karna.

**Activation function.** Ek non-linear function (sigmoid, ReLU, tanh) jo neuron ke output pe lagta hai. **Kyun zaroori?** Bina non-linearity ke, kitni bhi layers stack karo, poora network sirf ek linear function reh jaata hai (matrices multiply ho ke ek matrix) — curves/complex patterns seekh hi nahi sakta. Non-linearity hi networks ko powerful banati hai.

**Forward pass.** Input ko layer-by-layer aage bhejकar output nikalना (inference, 00d).

**Loss.** Output kitna galat hai — ek number (00d). Training ise kam karti hai.

**Gradient.** Loss ka har weight ke respect mein "slope" — batata hai us weight ko badhाने se loss badhega ya ghatega, aur kitna. Yeh direction hai jisme weight ko move karna hai.

**Backpropagation (backprop).** Gradient ko output se peeche ki taraf layer-by-layer compute karne ka algorithm (chain rule se). Yeh "kaunse weight ne kitni galti ki" ka blame-assignment hai.

**Gradient descent.** Learning ka actual step: `weight = weight - learning_rate · gradient`. Gradient ke ulat direction mein chhota step lo (kyunki gradient loss badhने ki direction hai, hume ghatani hai). Baar-baar karo → loss girta hai → model seekhता hai.

> **Ruko, socho:** Agar activation function hataake sirf `Σ(input·weight)+bias` rakho aur 100 layers stack karo, to network ki power kya hogi? (Jawab: sirf ek linear function jitni — 100 linear layers = ek linear layer (math se collapse ho jaati hain). Isliye non-linearity ke bina depth ka koi faayda nahi. Yahi DL ka core insight hai.)

**§0 checkpoint:** (1) Neuron ek line mein? (2) Activation non-linear kyun zaroori? (3) Gradient descent mein minus sign kyun?

---

### §1. AI → ML → DL — hum yahan tak kaise aaye

Shuru mein **AI = hardcoded rules** thi — "if email mein 'lottery' hai to spam". Problem: duniya bahut complex hai, har case ke rules likhna impossible. Phir **ML** aaya — rules likhne ke bajaye, data do aur system khud pattern seekhe (spam emails ke examples se). Par classic ML mein tumhe **features** haath se banane padte the ("word count", "capital letters %") — feature engineering ek bada kaam tha.

Phir **DL (neural networks)** ne yeh bhi automate kar diya — enough data + compute do, aur network **features khud seekh** leta hai (raw pixels se "edge → shape → face"). Yahi 2012 ke baad ka revolution tha (ImageNet, GPUs). DL ka trade: bahut data + bahut compute chahiye, par feature engineering gayi aur performance chhat pe. Isके teen ingredients the jo saath aaye: **data** (internet), **compute** (GPUs), aur **algorithms** (backprop scale pe). Tumhare liye takeaway — DL ne "insaan features batayega" ko "model features seekhega" mein badla, aur yahi soch aage transformers tak le gayi.

---

### §2. Neural network scratch se — ek neuron se network tak

Ek neuron (§0) ko code mein dekho — yahi poore DL ka atom hai:

```
output = activation( x1·w1 + x2·w2 + ... + b )
```

Ek **layer** = kai neurons parallel, sab same inputs pe. Ek **network** = layers stacked — pehli layer raw input pe, agli uske output pe, aant tak. Beech ki layers "hidden layers" hain. Forward pass poori input ko in layers se guzारता hai. Matrix form mein yeh efficient hota hai: ek layer ka output = `activation(W·x + b)` jahan `W` weight matrix hai — isliye NumPy/GPU pe fast.

Activation choices matter: **sigmoid** (0–1, purana, chhote networks), **tanh** (-1 to 1), **ReLU** (`max(0,x)` — aaj default, fast, deep networks mein gradient achha rehta). Yeh choice network ke seekhne ki speed/quality pe asar daalti hai.

> **→ Practice A1** (`neuron_forward.py`) — ek neuron ka forward pass + sigmoid, NumPy se.

---

### §3. Backprop + gradient descent — model seekhta kaise hai

Yeh module ka dil hai. Network ko seekhna hai matlab weights ko aise adjust karna ki loss kam ho. Yeh do steps ka loop hai (00d ka training loop, ab andar se):

1. **Forward pass** — input se prediction nikaalो.
2. **Loss** — prediction vs sahi answer ka error.
3. **Backprop** — loss ka gradient har weight ke respect mein nikaalो (output se peeche ki taraf, chain rule se). Yeh batata hai har weight ne error mein kitna contribute kiya.
4. **Gradient descent** — har weight ko uske gradient ke ulat chhota step move karo: `w = w - lr·grad`.
5. Repeat — loss dheere-dheere girta hai.

Intuition ke liye: loss ek pahaadi landscape hai jahan tum sabse neechi jagah (minimum loss) dhoondh rahe ho, ankhon par patti baandhे. Gradient batata hai "yahan se dhalान kis taraf hai". Tum ulat (neeche) ki taraf chhota kadam lete ho. `learning_rate` kadam ka size hai — bahut bada to minimum ke upar se kood jaoge (diverge), bahut chhota to bahut slow. Yeh "chain rule se blame peeche bhejना" hi backprop hai, aur yahi har neural net (LLMs समेत) ko train karta hai.

> **Ruko, socho:** `learning_rate` bahut bada rakhne pe loss up-down oscillate karne lagta hai ya badhता hai. Kyun? (Jawab: har step minimum ke aar-paar bade jump maar raha hai — dhalान ke neeche settle hone ke bajaye doosri taraf overshoot kar raha. Chhota lr chahiye. Yeh training ka #1 practical issue hai.)

> **→ Practice A2** (`gradient_descent.py`) — ek chhote function pe gradient descent se minimum dhoondho.

---

### §4. NLP ka safar — bag-of-words se LSTM tak

Text ko network mein daalne ke liye pehle **numbers** chahiye. Shuru mein **bag-of-words / one-hot** — har word ek index, order ignore. Problem: "dog bites man" aur "man bites dog" same dikhte the, aur "king"/"queen" ka koi relation capture nahi hota tha. Phir **word2vec/embeddings** (00d) — words ko dense vectors mein daalा jahan meaning geometry ban gaya ("king - man + woman ≈ queen"). Yeh bada jump tha.

Par sentences **sequences** hain — order matter karta hai. **RNN (Recurrent Neural Network)** aaya: ek word process karo, ek "hidden state" (memory) rakho, agle word ke saath wo state carry karo. Theory mein yeh poori history yaad rakh sakta tha. Practice mein do problem the: **vanishing gradients** (lambe sequences mein peeche ka signal kho jaata — model "long-range" dependencies bhool jaata), aur **sequential** processing (ek-ek word, parallelize nahi hota — slow training). **LSTM** (Long Short-Term Memory) ne gates (forget/input/output) daalke vanishing-gradient ko kaafi theek kiya, aur ML translation/text mein years tak raaj kiya. Par **sequential-processing** ki problem LSTM mein bhi thi — aur yahi wo deewar thi jo transformers ne todi (§6).

---

### §5. CNN — images ke liye (brief awareness)

Ek quick detour, kyunki interview mein aata hai aur pattern samajhne layak hai. **CNN (Convolutional Neural Network)** images ke liye design hua. Idea: poori image ko ek saath process karne ke bajaye, ek chhota "filter" (kernel) image pe slide karta hai aur local patterns (edges, corners) detect karta hai. Yeh filters weights hain jo seekhे jaate hain. Layers gehri hote jaate hain: pehli layer edges, agli shapes, agli objects — features ki hierarchy. CNN ka core insight **weight sharing** hai (same filter poori image pe) aur **locality** (paas ke pixels related hote hain), jisse yeh images pe efficient aur powerful hai. Tumhare inference-focused path ke liye yeh awareness kaafi — par "vision transformers" ab CNN ko bhi replace kar rahe, jo dikhata hai attention kitni general hai (§6).

---

### §6. Road to transformers — recurrence se attention

Ab poori kahani jud-ti hai. LSTM strong tha par do cheezein khaल rahi thi: (1) **sequential** — har word pichle ka wait karta, GPUs ka parallel power waste; (2) **long-range** — bahut lambे sequences mein bhi info bottleneck se guzarti (ek fixed hidden state).

2017 mein "Attention is All You Need" ne dono todi. Insight: recurrence ki zaroorat hi nahi — har word ko **direct** har doosre word se "attend" karne do (attention). Isse (a) poora sequence **parallel** process hota hai (koi step-by-step wait nahi → GPUs par bahut fast training), aur (b) koi bhi word kisi bhi doosre word se **direct** connection bana sakta hai (long-range problem gayab — do words ke beech "distance" ka koi penalty nahi). Yahi transformer hai, aur yahi wajah hai ki LLMs itne bade scale pe train ho paaye — parallelism ne massive data + compute ko possible banaya.

Attention *exactly* kaam kaise karta hai — Q/K/V, scaled dot-product, multi-head — wo Module 17 mein scratch se banaoge. Abhi yeh samajhो ki attention **kyun** aaya: recurrence ki sequential + long-range deewar todne.

> **Ruko, socho:** Transformer LSTM se "smarter" tha isliye jeeta, ya kisi aur wajah se? (Jawab: primarily **parallelism** — attention poore sequence ko ek saath process karta hai, isliye kahin zyada data/params pe train ho sakta hai. Scale ne jeetа, sirf architecture cleverness ne nahi. Yahi "scaling" ka poora daur shuru hua.)

> **→ Practice A3** (`softmax_ce.py`) — softmax + cross-entropy (yeh attention aur classification dono mein core hai).

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge.
> A1–A3 offline (NumPy) — `python <file>.py` → `_check()` pass.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §2 | `neuron_forward.py` | `_check()` asserts pass (forward + sigmoid) |
| A2 | §3 | `gradient_descent.py` | `_check()` asserts pass (minimum tak converge) |
| A3 | §4 | `softmax_ce.py` | `_check()` asserts pass (softmax + cross-entropy) |

### Setup

```bash
cd modules/16-dl-foundations/practice
python3 -m venv .venv && source .venv/bin/activate
pip install numpy
```

---

## Active recall (khud jawab likho NOTES mein)

1. Activation non-linear na ho to deep network ki power kya?
2. Backprop + gradient descent — model seekhने ka loop 4 steps mein?
3. RNN/LSTM ki 2 seemाyein jo transformers ne todi?
4. Transformer ne LSTM ko primarily kis wajah se replace kiya?

**Chat drill** (optional): "Module 16 — recurrence se attention tak ka safar whiteboard."

---

## Progress checklist

- [ ] §0 terms clear
- [ ] Theory §1–§6 padha
- [ ] Practice A1–A3 pass
- [ ] Redraw challenge (evolution timeline)
- [ ] Active recall NOTES mein
- [ ] NOTES session log

---

## Optional appendix

- [3Blue1Brown — Neural Networks (visual)](https://www.youtube.com/watch?v=aircAruvnKk)
- [Attention is All You Need](https://arxiv.org/abs/1706.03762) — Module 17 se pehle skim
- Module 00d (ML terms) · Module 17 (attention scratch se)
