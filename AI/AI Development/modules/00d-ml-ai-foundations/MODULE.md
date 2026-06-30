# Module 00d — ML & AI Foundations (incl. TensorFlow intro)

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 00c](../00c-fastapi/MODULE.md) · Next → [Module 00e Go Platform](../00e-go-platform/MODULE.md)

> **Format**: Textbook — §0 AI/ML terms zero se (prose). Voice: `@MODULE-TEACHING-STANDARD.md`

## At a glance

| | |
|---|---|
| Prerequisites | Module 00b (Python). 00c helpful, required nahi |
| Duration | ~4–5 sessions (embedding + TF alag din) |
| Project? | No |
| Exit test | Training vs inference, embeddings, aur "tum kya ship karoge" — apne shabdon mein |

## Yeh module kis baare mein hai

Module 01 se aage tum baar-baar yeh shabd sunoge — token, embedding, model, training, inference, vector. Agar yeh dhundhle rahe, to RAG aur agents mein har cheez magic lagegi. Yeh module un sab ko zero se concrete bana deta hai, taaki aage sab "samajh ke" ho, ratta nahi.

Ek baat pehle hi saaf kar deta hoon (yeh tumhara time bachayega): **tumhara 2026 job path mostly inference hai — banana-banwana nahi, banaye hue models ko use karna.** Isliye embeddings, vectors, cosine similarity, aur inference-vs-training ka farak gehraai mein seekho; CNN architecture design ya ML-research ki gehraai *abhi* zaroori nahi. TensorFlow yahan sirf isliye hai ki tum training code **padh** sako aur interview mein trade-off bol sako — har din TF nahi likhoge.

---

## Read order

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms pehli baar | Analogies NOTES mein |
| 2 | Visual map + scope | Redraw challenge start |
| 3 | §1 AI/ML/DL/LLM + §2 training loop | **A2** diagram |
| 4 | §3 NumPy tensors + §4 Embeddings | — |
| 5 | §5 Cosine similarity | **A1** |
| 6 | §6 TensorFlow hello | **A3** |
| 7 | §7 API vs training + §8 HF hub | **A4**, **A5** |

**Unlocks**: Module 01 (LLM APIs), Module 05 (RAG) — embeddings familiar honge.

---

## Theory

### §0. AI/ML terms — pehli baar (45 min, diagram se pehle)

Tum zero AI background se aaye ho. In shabdon ko ek baar achhe se baith ke samajh lo — poora baaki course inhi par khada hai.

**Token.** Token text ka ek **chhota tukda** hai jise model padhता/likhता hai — poora word zaroori nahi, kabhi subword bhi (`ing` alag token ho sakta). Jaise WhatsApp message network packets mein todta hai, LLM text ko tokens mein todta hai — aur aksar billing bhi **per token** hoti hai. `"Return my money please"` model ke andar shायad `["Return", " my", " money", " please"]` — ~4 tokens. Tumhara daily contact ispे: API response mein `usage.prompt_tokens` batayega kitna input consume hua.

**Embedding.** Yeh sabse important concept hai is module ka. Embedding text ko **floats ki ek fixed-length list (vector)** mein badal deta hai, aise ki **meaning** numeric ban jaaye:

```
"refund policy"  →  [0.02, -0.11, 0.88, ...]   # e.g. 1536 numbers
"return money"   →  [0.01, -0.09, 0.85, ...]   # similar meaning → similar numbers
"banana bread"   →  [-0.4, 0.7, 0.1, ...]      # alag topic → door numbers
```

Soch aise: har sentence ka ek **GPS coordinate** mil gaya. Similar matlab waale sentences paas-paas, alag matlab waale door. Isi se "keyword match" ki jagah "**meaning match**" possible hota hai — `"refund"` search karo aur `"return money"` bhi mil jaaye. Yahi RAG ka dil hai (Module 05): docs ko embed karke DB mein rakho, user query ko embed karo, sabse paas waले vectors uthao, aur unka text LLM ko context do.

**Model aur weights.** Model ek **function** hai jiske andar **learned numbers (weights)** hain — input aata hai, layers se guzarta hai, output nikalता hai. Weights wo millions/billions floats hain jo training ne set kiye. Soch: model = compiled program, weights = wo internal state jo training se aaya. "Pre-trained" matlab koi pehle hi train kar chuka (GPT, BGE) — tum use download/use karte ho.

**Training vs inference — sabse zaroori farak.** Yeh ek line mein gaanth baandh lo: training mein weights **badalte** hain (model seekhता hai), inference mein weights **fixed** rehte hain (model sirf predict karta hai). Analogy bilkul exam jaisी — **training = exam ki taiyari** (notes padhke dimaag update), **inference = exam ka din** (dimaag fixed, sirf answer do).

```
TRAINING:   data → model.fit() → weights change → save file   (offline, GPU, hours)
INFERENCE:  input → model.predict()/API → output             (online, ms, weights untouched)
```

Tumhara kaam ~95% inference hai — OpenAI ko `chat.completions` call karna *inference* hai. Training sirf awareness ke liye.

**Loss.** Training ke dauran "model kitna galat hai" ka score — ek number jo training kam karne ki koshish karta hai (prediction vs sahi answer compare). Inference mein loss nahi hota, sirf output chahiye.

**Cosine similarity** (detail §5). Do embeddings kitne similar hain, yeh unke beech ke **angle** se naapते hain — `~1.0` matlab same direction (bahut similar meaning), `~0.0` matlab unrelated. RAG mein query vector ko har doc vector se cosine karke top-k uthate hain.

> **Ruko, socho:** "1536-dimensional embedding" ka matlab 1536 *words* hai? (Jawab: nahi — 1536 *numbers* (features). Ek vector ki length hai, words se koi seedha relation nahi.)

#### §0 common galatfehmiyaan

| Galat soch | Sach |
|-----------|------|
| "Har AI project mein training karni padti hai" | Mostly pre-trained + inference |
| "Embedding = keyword search" | Semantic — synonyms paas aate hain |
| "1536 = 1536 words" | 1536 numbers (features), words nahi |
| "Token = character" | Subword — `ing` alag token ho sakta |

#### §0 checkpoint (NOTES mein)

1. Training aur inference ka ek-ek example (API call vs `fit`)?
2. 1536-dim embedding practically kya store karta hai?
3. Token cost mein kyun matter karta hai?

---

## Visual map (§0 ke baad)

```
TRAINING (awareness)              INFERENCE (tumhara daily job)
────────────────────              ─────────────────────────────
labeled data → fit → weights      text → embed → vector → cosine search / RAG / chat API
        ↑                                  (no local training)
   TF / PyTorch (optional)
```

**Mental model**: Training weights **banata** hai; inference un weights (ya hosted API) se **output** deta hai. Tumhara ship-path zyadातar inference + embeddings hai.

**Redraw challenge**: Training vs inference split + text→embedding→vector + API-path vs TF-path — bina dekhe banao.

---

### §1. AI vs ML vs DL vs LLM — umbrella se specific

"AI" ek marketing shabd ban gaya hai, par interview aur docs mein precise terms chahiye. Yeh ek nesting hai, har andar wali pichli ka subset hai: **AI** sabse bahari chhata hai (machines jo "smart" kaam karein). Uske andar **ML** — wo systems jo data se *seekhते* hain, hardcoded `if/else` nahi. Uske andar **DL** — ML par neural networks (layers) ke saath, jo images/text/speech sambhalta hai. Aur uske andar **LLM** — massive text pe trained DL model jo agla token predict karta hai (GPT, Claude, Llama).

```
AI
 └── ML (data se seekho)
      └── DL (neural nets, kai layers)
           └── LLM (GPT, Claude — text in, text out)
```

Example se: self-driving broadly AI hai, email spam filter ML, image recognition DL, aur ChatGPT LLM. Tumhara daily kaam sabse andar wale layer pe hai — LLM API + RAG + agents, yaani inference layer, lab training nahi.

---

### §2. Model, weights, training loop — intuition

"Model train karo" sunke magic lagta hai, par actually yeh ek **repeat loop** hai jo weights ko thoda-thoda adjust karta hai jab tak galti kam na ho jaaye:

```
1. (input, sahi_answer) ka ek batch lo
2. Forward pass: prediction = model(input)
3. Loss = error(prediction, sahi_answer)
4. Backprop: loss se pata karo kaunse weights "blame" hain
5. Optimizer: un weights ko thoda update karo
6. Repeat — jab tak loss acceptable
7. model.save() — weights disk pe
```

Inference loop chhota hai — sirf step 1–3 ka aadha: saved weights load karo (frozen), input do, forward pass se output lo. Step 4–5 (weights update) inference mein hote hi nahi. Isiliye training GPU-heavy hai (millions of updates) jabki ek inference sirf ek forward pass hai — aur API path mein wo bhi provider ke GPU pe hota hai, tumhare laptop pe nahi.

> **→ Practice A2** (pass): Training vs inference diagram paper/Excalidraw pe — labels §0 + is section se.

---

### §3. Tensor — multi-dimensional array (NumPy)

Embeddings aur weights dono **numbers ki lists** hain, isliye NumPy se inhe handle karna seekho — yeh TensorFlow se pehle ka foundation hai.

```python
import numpy as np

v = np.array([0.1, 0.5, -0.3])      # 1D — embedding jaisा
m = np.array([[1, 2], [3, 4]])      # 2D matrix
v.shape   # (3,)  → 3 elements
np.dot(np.array([1, 2]), np.array([3, 4]))   # 1*3 + 2*4 = 11
```

`np.array(...)` Python list ko numeric array banata hai; `.shape` uske dimensions batata hai (`(3,)` matlab 3-length 1D); aur `np.dot(a, b)` dot product deta hai — yahi cosine similarity (§5) mein use hoga. TensorFlow ke "tensors" inhi NumPy arrays jaise hain, bas GPU placement aur autograd (training gradients) ke saath.

#### §3 common errors

| Error | Kyun | Fix |
|-------|------|-----|
| `ModuleNotFoundError: numpy` | Install nahi | `pip install numpy` (venv mein) |
| `ValueError: shapes not aligned` | Dot product dimension mismatch | Vectors same length check |

---

### §4. Embeddings — text → vector (RAG ka foundation)

Keyword search `"refund"` ko `"return money"` nahi milegा — alag words hain. Iska ilaaj **semantic search** hai: text ko aise dense vectors mein badlo ki similar matlab waले vectors **paas** ho high-dimensional space mein.

```
"refund policy"  → [0.02, -0.11, 0.88, ...]   # 1536 dims
"return money"   → [0.01, -0.09, 0.85, ...]   # upar wale se high cosine
"banana bread"   → [-0.4, 0.7, 0.1, ...]      # refund pair se low cosine
```

Do practical baatein yaad rakho. Ek, jo bhi dimension model deta hai (jaise 1536) wo tumhare DB ke `vector` column ki length ban jaata hai (pgvector, Module 05). Do — query aur docs ko **same embedding model** se banao, warna unke vectors compare karna invalid hai (alag GPS systems ko compare nahi kar sakte). Andar yeh hota hai: text → tokenize → neural net forward → ek single vector mein pool → DB mein store ya query se compare.

Use cases: semantic search, RAG retrieval, clustering, dedup, recommendations — sabki neev yahi "meaning ko vector banao" hai.

> **→ Practice A4** (prep): 3 sentences embed karke similar pair dhoondho — §5 cosine ke baad full pass.

---

### §5. Cosine similarity

Do vectors "kitne similar" hain — iska standard measure text embeddings ke liye **cosine** hai, jo vectors ke beech ka **angle** dekhta hai (direction matter karti hai, length nahi):

```
cosine(A, B) = (A · B) / (||A|| × ||B||)
```

Range -1 se 1 (similar docs pe aksar 0–1). Code:

```python
import numpy as np

def cosine_sim(a: np.ndarray, b: np.ndarray) -> float:
    a_norm = a / np.linalg.norm(a)   # unit vector — sirf direction
    b_norm = b / np.linalg.norm(b)
    return float(np.dot(a_norm, b_norm))

cosine_sim(np.array([1.0, 0.0]), np.array([0.9, 0.1]))   # ~0.99 (almost same direction)
```

Idea seedha hai: pehle dono vectors ko unit-length banao (`/ norm`) taaki sirf direction bache, phir dot product le lo — yahi cosine hai. (Euclidean distance physical coordinates ke liye theek hai, par high-dim text embeddings ke liye cosine standard hai.)

RAG retrieval poora flow:

```
1. query_vec = embed(user_question)
2. har doc_vec ke liye: score = cosine(query_vec, doc_vec)
3. scores ko descending sort → top-k docs
4. un docs ka text → LLM prompt ka context
```

> **Ruko, socho:** Agar tum cosine nikalne se pehle vectors ko normalize karna bhool jao, to result 1 se zyada aa sakta hai — galat. Kyun? (Jawab: bina normalize ke tum `A·B` to le rahe ho par `||A||×||B||` se divide nahi — to wo cosine nahi, raw dot product hai, jiska magnitude bound nahi.)

#### §5 common errors

| Bug | Kyun | Fix |
|-----|------|-----|
| `ZeroDivisionError` | Zero vector | Embedding non-empty check |
| Similarity > 1 | Normalize skip kiya | Pehle normalize karo |
| Wrong pair wins (A4) | Alag embed models | Teeno sentences same model se |

> **→ Practice A1** (pass): `cosine_similarity.py` — identical → 1.0, orthogonal → ~0.0.

---

### §6. TensorFlow/Keras — minimal hello (training ki awareness)

Interview ya docs mein `model.fit`, `Dense`, `Sequential` dikhega — ek baar haath se chala lo taaki training code **padh sako**. Yeh daily kaam nahi, sirf literacy. Ek toy AND-gate model:

```python
import numpy as np, tensorflow as tf

X = np.array([[0,0],[0,1],[1,0],[1,1]], dtype=float)
y = np.array([[0],[0],[0],[1]], dtype=float)

model = tf.keras.Sequential([
    tf.keras.layers.Dense(4, activation="relu", input_shape=(2,)),
    tf.keras.layers.Dense(1, activation="sigmoid"),
])
model.compile(optimizer="adam", loss="binary_crossentropy", metrics=["accuracy"])
model.fit(X, y, epochs=50, verbose=0)        # TRAINING — weights update hote hain
pred = model.predict([[1, 1]], verbose=0)    # INFERENCE — sirf forward → ~[[1.0]]
```

Yahan `Sequential([...])` layers ka stack hai; `Dense(4, ...)` ek fully-connected layer hai 4 neurons ke saath; `compile(...)` optimizer aur loss set karke training ka setup karta hai. Ab gaur karo wahi training-vs-inference farak code mein dikh raha hai: `model.fit()` **training** hai (weights badle), `model.predict()` **inference** (sirf forward pass). Yahi do lines is poore module ka saar hain. (Apple Silicon pe `tensorflow-macos` + `tensorflow-metal`, ya Google Colab use karo.)

#### §6 common errors

| Error | Kyun | Fix |
|-------|------|-----|
| `No module named 'tensorflow'` | Install nahi | `pip install tensorflow` / macos variant |
| Loss not decreasing | Shapes/LR | Toy AND chalna chahiye — `X,y` shapes check |

> **→ Practice A3** (pass): Tiny Keras model — `predict()` naye input pe kaam kare.

---

### §7. API path vs training path — tum kya ship karoge

Team poochhegi "model banayein kya?" — aur tumhara default jawab clear hona chahiye: **API + embeddings; training exception hai.** Do raste hain:

- **API path (tumhara default):** prompt/text → OpenAI/Anthropic API → tokens/embeddings. Best quality, zero ML-ops, par cost + vendor dependency.
- **Training path (awareness):** dataset → TF/PyTorch train → weights file → khud host karke inference. Control deta hai par data + GPU + skill maangता hai.

Practically tumhare projects mein: LLM Gateway, RAG app, aur agents — teeno mein TF training **nahi** chahiye (sab API/embeddings se chalте hain). Custom vision model jaisा kuch ho to *shayad* fine-tune — par wo early career mein rare hai. Bottom line: jaldi ship karna hai to API path; bade scale pe control chahiye to training, par wo bada upfront investment hai.

> **→ Practice A4** (pass): 3 sentences → top similar pair.
> **→ Practice A5** (pass): ~200 words NOTES — TF kahan **nahi** chahiye; Gateway, RAG, agents name karo.

---

### §8. Hugging Face hub — model card padhna

"Kaunsa model use karun?" — iska jawab Hugging Face pe **model cards** padhke milta hai. Models hub pe publish hote hain apni size, license, aur task ke saath. Embedding ke liye `bge-small` ya `all-MiniLM-L6-v2` jaise search karoge. Card mein chaar cheezein dekho: **task** (`sentence-similarity` chahiye, `text-generation` nahi), **dimensions** (DB schema se match kare), **license** (commercial use OK?), aur **size** (laptop pe chalega?).

Local embedding banane ka flow:

```
1. pip install sentence-transformers
2. model = SentenceTransformer('all-MiniLM-L6-v2')
3. vectors = model.encode(["sentence1", "sentence2", ...])
4. A1 ka cosine_sim → best_pair()
```

Yahan bhi tum **train nahi** kar rahe — bas ek pre-trained artifact download karke `encode` kar rahe ho. Yeh OpenAI embeddings API jaisा hi kaam hai, bas local. Pehli baar model download GB mein ho sakta hai (`~/.cache/huggingface` mein cache hota hai).

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge.
> Stuck? `@modules/00d-ml-ai-foundations/MODULE.md` + error paste.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §5 | `cosine_similarity.py` | identical → 1.0; orthogonal → ~0.0 |
| A2 | §0, §2 | Paper / Excalidraw | Training vs inference diagram, labelled |
| A3 | §6 | `tf_hello.py` | `predict()` naye input pe kaam kare |
| A4 | §4,§5,§8 | `embeddings_local.py` / `_api.py` + `_common.py` | Similar pair sabse upar rank kare |
| A5 | §1, §7 | `NOTES.md` | ~200 words: TF kahan nahi chahiye |

### Setup

```bash
cd modules/00d-ml-ai-foundations/practice
python3 -m venv .venv && source .venv/bin/activate
pip install numpy
# A3: pip install tensorflow (ya tensorflow-macos)
# A4 Option A: pip install openai python-dotenv
# A4 Option B: pip install sentence-transformers (recommended, no API key)
```

### Hints
- A1: `np.linalg.norm` for magnitude; identical → 1.0, orthogonal → 0.0.
- A4: Option A = OpenAI embeddings API; Option B = local `sentence-transformers`; `best_pair()` A1 cosine import kare. 3 sentences: 2 similar, 1 random.

---

## Active recall (khud jawab likho NOTES mein)

1. Embedding dimension 1536 ka practical matlab kya hai?
2. Training GPU kyun chahiye, inference kab CPU pe theek hai?
3. TensorFlow train karna vs GPT-4 API call — trade-off 3 bullets mein?

**Chat drill** (optional): "Module 00d recall — 3 questions mujhse poochh."

---

## Progress checklist

- [ ] §0 terms + checkpoint NOTES mein
- [ ] Scope samjha
- [ ] Visual map redraw challenge
- [ ] Theory §1–§8 padha
- [ ] Practice A1–A5 pass
- [ ] Active recall NOTES mein
- [ ] NOTES session log updated

---

## Optional appendix (zarurat ho tab)

- [NumPy Quickstart](https://numpy.org/doc/stable/user/quickstart.html)
- [OpenAI — Embeddings guide](https://platform.openai.com/docs/guides/embeddings)
- [TensorFlow — Quickstart for beginners](https://www.tensorflow.org/tutorials/quickstart/beginner)
- [3Blue1Brown — Neural Networks Ch.1](https://www.youtube.com/watch?v=aircAruvnKk)
