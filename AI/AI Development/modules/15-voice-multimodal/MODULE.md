# Module 15 — Voice & Multimodal Agents

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 14](../14-finetuning/MODULE.md) · End

> **Format**: Textbook — §0 terms zero se, prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`
> **Track 2 (advanced):** text/backend se aage — vision + voice.

## At a glance

| | |
|---|---|
| Prerequisites | Module 01 (LLM APIs), 05/13 (RAG), 02 (latency/infra) |
| Duration | ~3–4 sessions |
| Project? | No (par voice agent ek strong portfolio piece hai) |
| Exit test | Voice pipeline (STT→LLM→TTS) + latency budget + multimodal message bina notes ke samjhao |

## Yeh module kis baare mein hai

Ab tak sab text tha. Par 2026 mein do cheezein tez badh rahi hain aur high-paying roles inhe maangte hain: **vision** (image samajhna — invoices, screenshots, documents) aur **voice** (bolkar baat karne wale agents — YC mein bahut hot). Yeh module dono ka practical foundation deta hai: image ko LLM ko kaise bhejo, voice pipeline kaise banti hai, aur — sabse important interview angle — **latency**, kyunki voice mein latency hi make-or-break hai.

Ek core idea: **multimodal LLM sirf text nahi, image/audio bhi input le sakta hai** — par voice ke liye aksar ek *pipeline* banani padti hai (speech→text→LLM→text→speech), aur us pipeline ka har hop latency jodता hai. Voice agent achha lagta hai ya nahi, yeh 90% latency pe depend karta hai.

```
VISION:  image (URL/base64) + text  → multimodal LLM → text

VOICE pipeline (classic):
  mic → [STT/ASR] → text → [LLM] → text → [TTS] → speaker
        ~300ms          ~500ms TTFT      ~200ms      = latency budget

VOICE (realtime API): mic ⇄ single speech-to-speech model ⇄ speaker  (low latency, barge-in)
```

**Redraw challenge**: voice pipeline ke 3 hops + har ka latency, aur realtime API ka single-hop — bina dekhe banao.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + §1 Vision | **A2** — `image_message_builder.py` |
| 2 | §2 Audio (STT/TTS) + §3 Voice pipeline | **A3** — `latency_budget.py` |
| 3 | §4 Realtime API + §5 Multimodal RAG | **A1** — `voice_pipeline.py` (stub) |
| 4 | §6 Production concerns | Recall + NOTES |

---

## Theory

### §0. Terms pehli baar — multimodal, ASR, TTS, realtime

**Multimodal.** Ek model jo ek se zyada "modality" handle kare — text + image (aur ab audio/video). Jo `gpt-4o`, `claude` jaise models tum use karte ho, wo vision-capable hain — tum ek image bhej ke uske baare mein poochh sakte ho.

**Vision / image tokens.** Model image ko bhi **tokens** mein todता hai (text ki tarah bill hota hai). Ek image apni resolution ke hisaab se sau-hazaron tokens le sakti hai — isliye vision requests text se mehenge ho sakte hain, aur `detail: low/high` se tum resolution/cost trade karte ho.

**ASR / STT (Automatic Speech Recognition / Speech-to-Text).** Audio → text. Whisper (OpenAI) sabse common. Yeh voice pipeline ka pehla hop hai.

**TTS (Text-to-Speech).** Text → audio. Voice pipeline ka aakhri hop — model ka text jawab bolkar sunaana.

**Voice agent pipeline.** Classic voice agent teen models jodta hai: STT (bola hua → text) → LLM (text → jawab text) → TTS (jawab → bola hua). Teen hops = teen latencies = challenge.

**Realtime / speech-to-speech API.** Naye realtime APIs (OpenAI Realtime, etc.) ek hi model mein audio-in → audio-out karte hain — teen hops ki jagah ek, isliye bahut kam latency aur natural conversation (interrupt kar sakte ho).

**Barge-in.** User agent ke bolte-bolte beech mein bol de (interrupt) — natural conversation ke liye zaroori. Realtime APIs ise handle karti hain; pipeline mein manually manage karna padta hai.

**Multimodal RAG.** RAG par images bhi — image+text ko ek shared embedding space (CLIP-style) mein daalke image se ya text se dono retrieve karna (jaise "yeh chart dikhta hai us jaisा doc dhoondo").

> **Ruko, socho:** Voice agent banane mein sabse bada engineering challenge kya hai — accuracy ya latency? (Jawab: latency. Insaan conversation mein ~500ms se zyada gap awkward lagta hai. STT+LLM+TTS teeno mila ke 2-3s ho jaaye to agent "slow/robotic" feel hota hai — isliye streaming + realtime APIs ka poora focus latency pe hai.)

**§0 checkpoint:** (1) Vision request text se mehenga kyun ho sakta hai? (2) STT vs TTS? (3) Realtime API 3-hop pipeline se behtar kyun?

---

### §1. Vision — image LLM ko bhejना

Multimodal LLM ko image do tareeke se bhejte ho: ek **public URL**, ya **base64-encoded** bytes (private/local images ke liye). Message format text se thoda alag — `content` ek string nahi, balki parts ka array hota hai (text part + image part):

```python
message = {
    "role": "user",
    "content": [
        {"type": "text", "text": "Is invoice ka total amount kya hai?"},
        {"type": "image_url", "image_url": {"url": "data:image/png;base64,iVBOR...", "detail": "high"}},
    ],
}
```

`detail` matter karta hai — `low` kam tokens/cost (thumbnail-level, quick), `high` zyada tokens (fine detail — chhoti text/numbers padhne ke liye). Use cases jo interview/product mein aate hain: invoice/receipt se data extract (OCR + structure), screenshot debugging, document understanding, image describe/moderate. Ek production tip — vision output ko bhi structured output (Module 04) + guardrails (Module 12) se guzaro, kyunki OCR/extraction galat ho sakti hai.

> **→ Practice A2** (`image_message_builder.py`) — multimodal message payload sahi shape mein banao.

---

### §2. Audio — STT aur TTS

Do alag steps hain. **STT (Whisper)** audio file/stream leke text deta hai — accents, noise handle karta hai, par ek latency + cost hota hai. **TTS** text leke natural-sounding audio deta hai (alag voices/styles). Dono API calls hain:

```python
# STT (audio → text)
text = client.audio.transcriptions.create(model="whisper-1", file=audio_file).text
# TTS (text → audio)
audio = client.audio.speech.create(model="tts-1", voice="alloy", input="Aapka refund process ho gaya.")
```

Inhe alag samajhna zaroori hai kyunki voice pipeline inhi ko LLM ke saath jodta hai (§3), aur har ek latency budget mein add hota hai.

---

### §3. Voice agent pipeline — teen hops, teen latencies

Classic voice agent teen models ko chain karta hai, aur yahin asli engineering hai:

```
user bolta hai → STT (~300ms) → LLM (~500ms to first token) → TTS (~200ms) → user sunta hai
```

Total latency in sabka sum + network. Agar naive karo (har step poora khatam ho phir agla), user ko 2-3s ka awkward gap milega — agent robotic lagega. Ilaaj **streaming + overlap** hai: LLM ka output token-by-token stream karo (Module 01), aur jaise-jaise sentences bante hain, unhe **turant TTS** ko bhej do (poore jawab ka wait mat karo). Isse "time to first audio" bahut gir jaata hai — user pehla word jaldi sunта hai bhale poora jawab abhi ban raha ho. Yeh wahi perceived-latency trick hai jo Module 01 mein text streaming mein tha, ab audio pe.

Ek aur challenge — **barge-in**: user beech mein bol de to agent ko rukna chahiye (TTS cancel + naya STT start). Pipeline mein yeh manually handle karna padta hai (realtime API ye built-in deti hai, §4).

> **→ Practice A3** (`latency_budget.py`) — pipeline ka latency budget compute karo aur bottleneck pakdo.

---

### §4. Realtime / speech-to-speech APIs

Naye **realtime APIs** teen-hop pipeline ki jagah ek hi model mein audio-in → audio-out karti hain, ek persistent (WebSocket) connection pe. Faayde: bahut kam latency (ek hop, no STT/TTS round-trips), natural barge-in (model interruption samajhता hai), aur emotion/tone preserve (audio directly, text ke through nahi jaata). Trade-off: kam control (tum beech mein text nahi dekhte, to logging/guardrails/tool-calls thode alag handle karne padte hain), aur cost model alag.

Rule of thumb: agar sabse natural low-latency conversation chahiye (customer voice bot) → realtime API. Agar tumhe beech mein control chahiye (har turn pe RAG, guardrails, tool calls, transcripts log) → classic pipeline (STT→LLM→TTS) with streaming. Bahut production systems hybrid karte hain.

---

### §5. Multimodal RAG

RAG ab sirf text nahi. Image+text ko ek **shared embedding space** (CLIP-style models) mein daala jaata hai, taaki tum text se image retrieve kar sako ya image se image/text. Use cases: product catalog ("is jaisा dikhne wala item dhoondo"), technical docs jinme diagrams/charts hain (chart ka meaning retrieve karna), medical/insurance (image + report). Pipeline Module 05 jaisा hi hai — bas embedding model multimodal, aur chunks mein image references. Awareness ke liye kaafi; jab zaroorat ho tab depth.

---

### §6. Production concerns — latency, cost, kab worth hai

Voice mein **latency budget** sabse important design tool hai. Har hop ka target rakho aur total ko conversational threshold (~800ms–1s time-to-first-audio) ke neeche laao. Agar total zyada hai, bottleneck pakdo (aksar LLM TTFT ya STT) aur wahi optimize karo — chhota/faster model, streaming, ya realtime API. Cost bhi jodo: STT + LLM (with image tokens if vision) + TTS — teeno bill hote hain, to per-minute cost nikalо.

Aur ek honest product question — **voice worth hai ya nahi?** Voice tab jeetता hai jab hands/eyes busy hon (driving, cooking, accessibility) ya phone-based support ho. Bahut jagah text hi behtar (skim-able, cheap, precise). Interview mein yeh judgment dikhाna — "voice added latency + cost, ROI tabhi jab UX genuinely voice-first ho" — tumhe engineer-jo-product-sochta-hai dikhाता hai.

> **Ruko, socho:** Tumhare voice bot ka total latency 2.2s hai aur breakdown: STT 400ms, LLM-TTFT 1400ms, TTS 400ms. Pehla lever? (Jawab: LLM TTFT (1400ms) sabse bada bottleneck — chhota/faster model ya streaming se first-token jaldi laao, aur sentence-by-sentence TTS ko feed karo. Bottleneck pe kaam karo, sab pe barabar nahi.)

> **→ Practice A1** (`voice_pipeline.py`) — STT→LLM→TTS orchestration stub (streaming-aware).

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge.
> A2, A3 offline — `python <file>.py` → `_check()` pass. A1 API-dependent (stub/structural).

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §3 | `voice_pipeline.py` | STT→LLM→TTS orchestration (streaming-aware) chale |
| A2 | §1 | `image_message_builder.py` | `_check()` asserts pass (multimodal message shape) |
| A3 | §6 | `latency_budget.py` | `_check()` asserts pass (total + bottleneck + target) |

### Setup

```bash
cd modules/15-voice-multimodal/practice
python3 -m venv .venv && source .venv/bin/activate
# A2, A3 sirf stdlib. A1: pip install openai (vision/audio API)
```

---

## Active recall (khud jawab likho NOTES mein)

1. Vision request text se mehenga kyun, aur `detail` kaise cost control karta hai?
2. Voice pipeline latency kaise girate hain (2 techniques)?
3. Realtime API vs classic pipeline — kab kaunsa?
4. Voice kis case mein worth nahi hai?

**Chat drill** (optional): "Module 15 — voice bot latency budget + bottleneck whiteboard."

---

## Progress checklist

- [ ] §0 terms clear
- [ ] Theory §1–§6 padha
- [ ] Practice A1–A3 pass
- [ ] Redraw challenge (pipeline + latencies)
- [ ] Active recall NOTES mein
- [ ] NOTES session log

---

## Optional appendix

- [OpenAI Vision guide](https://platform.openai.com/docs/guides/vision)
- [OpenAI Realtime API](https://platform.openai.com/docs/guides/realtime)
- [Whisper (STT)](https://platform.openai.com/docs/guides/speech-to-text)
- Module 01 (streaming) · 02 (latency) · 12 (guardrails on vision output)
