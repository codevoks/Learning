# Module 00d — Assignments (ek jagah)

> **Theory**: `../MODULE.md` · **Learnings**: `../NOTES.md` · **Doubt**: `@MODULE.md`

Order: A1 → A5. Code files mein `TODO` search karo.

---

## Progress checklist

- [ ] A1 — `cosine_similarity.py`
- [ ] A2 — training vs inference diagram (paper/Excalidraw)
- [ ] A3 — `tf_hello.py`
- [ ] A4 — `embeddings_stub.py`
- [ ] A5 — TF kahan nahi chahiye (NOTES, ~200 words)
- [ ] Active recall → NOTES
- [ ] Redraw challenge

---

## Setup

```bash
cd modules/00d-ml-ai-foundations/practice
python3 -m venv .venv && source .venv/bin/activate
pip install numpy
```

### Per assignment (optional)

```bash
pip install tensorflow          # A3 — or tensorflow-macos on Apple Silicon
pip install openai python-dotenv   # A4 option A
pip install sentence-transformers  # A4 option B (local)
```

---

## A1 — Cosine similarity

| | |
|---|---|
| **File** | `cosine_similarity.py` |
| **Kya** | Cosine function TODO |
| **Pass** | Manual formula se match on test vectors |

### Run

```bash
python cosine_similarity.py
```

### Hints

- `np.linalg.norm` for magnitude
- Identical vectors → 1.0; orthogonal → 0.0

---

## A2 — Diagram (no code)

| | |
|---|---|
| **Where** | Paper / Excalidraw → `../NOTES.md` or `diagrams/` |
| **Kya** | Training vs inference flow |
| **Pass** | Self-check / coach |

---

## A3 — TensorFlow hello

| | |
|---|---|
| **File** | `tf_hello.py` |
| **Kya** | Tiny Keras model TODO |
| **Pass** | `predict()` on new input works |

### Run

```bash
python tf_hello.py
```

### Hints

- XOR ya simple AND enough
- `epochs=50`, `verbose=1` — loss dekho

---

## A4 — Embeddings

| | |
|---|---|
| **File** | `embeddings_stub.py` |
| **Kya** | 3 sentences → top similar pair |
| **Pass** | Similar pair ranks highest |

### Run

```bash
python embeddings_stub.py
```

### Hints

- **Option A:** OpenAI API + cosine
- **Option B:** `sentence-transformers` local
- 2 similar topic sentences + 1 random

---

## A5 — Written (NOTES)

| | |
|---|---|
| **File** | `../NOTES.md` |
| **Kya** | ~200 words: TensorFlow kahan **nahi** chahiye daily ship path mein |
| **Pass** | Gateway, RAG, agents name karo |

---

## Active recall (NOTES)

1. Embedding dimension 1536 practically kya mean karta hai?
2. Training GPU kyun; inference kab CPU ok?
3. TensorFlow vs GPT-4 API — 3 bullet trade-off?

---

## Files

| File | Assignment |
|------|------------|
| `cosine_similarity.py` | A1 |
| `tf_hello.py` | A3 |
| `embeddings_stub.py` | A4 |

**Stuck?** `@modules/00d-ml-ai-foundations/MODULE.md` + error paste.
