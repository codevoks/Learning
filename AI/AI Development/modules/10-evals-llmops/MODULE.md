# Module 10 — Evals & LLMOps

> **Padho**: Isi file mein **Theory** — bahar mat jao.
> **Likho**: `practice/` folder. **Pucho**: Cursor chat `@MODULE.md`
> **Nav**: ← [Module 09](../09-multi-agent-hitl/MODULE.md) · Next → [Module 11](../11-project-agentic-workflow/MODULE.md)

> **Format**: Textbook — §0 terms zero se, prose mein. Voice: `@MODULE-TEACHING-STANDARD.md`

## At a glance

| | |
|---|---|
| Prerequisites | Modules 05–09 (RAG + agents). 00a Git basics |
| Duration | ~4–6 sessions |
| Project? | No (par Project A/B/C sab mein eval harness — Module 11 M6) |
| Exit test | Golden dataset + trajectory eval + CI threshold bina notes ke samjhao |

## Yeh module kis baare mein hai

Ab tak tum LLM apps bana rahe the. Yeh module poochhta hai: **kaise pata chalega ki tumhara change behtar hai ya bura?** LLM apps probabilistic hain — same prompt, alag jawab — to `assert response == "hello"` jaisा test flaky hai aur model update pe toot jaata hai. Iska jawab **evals** hain: ek golden dataset pe systematic scoring, jise tum CI mein gate ki tarah lagate ho taaki regression ship hone se pehle ruk jaaye. **LLMOps** is poore loop ka naam hai — eval + tracing + deploy gates.

Tumhare payment days se seedha parallel: nightly reconciliation golden files — known input → expected output, mismatch → alert, deploy block. Yahan wahi, par "golden prompts/workflows" pe.

```
code/prompt change → golden dataset pe eval → scores + traces → CI: pass rate ≥ baseline?
                                                                  yes → deploy / no → fix loop
```

**Redraw challenge**: Build → eval → trace → CI gate loop; fail arrow wapas build pe; offline vs online alag box.

---

## Read order (strict)

| Session | Padho | Karo |
|---------|-------|------|
| 1 | §0 Terms + §1 Problem | Socho: tumhare Zapier clone ke "golden cases" kya the |
| 2 | §2 Outcome vs trajectory | **A1** — `golden_dataset.json` (10 cases) |
| 3 | §3 Scorers | **A2** — `trajectory_scorer.py` |
| 4 | §4 Langfuse traces | **A2** complete |
| 5 | §5 CI regression + §6 Online/offline | **A3** — `ci_eval.sh` |
| 6 | §7 SLIs + §8 setup | Recall + checklist |

---

## Theory

### §0. Terms pehli baar — evals, LLMOps

**Eval** ek systematic test hai jo ek score distribution deta hai, na ki single pass/fail — jaise 100 questions → 92% pass. Iske parts: **golden dataset** (curated input + expected-output pairs), **scorer** (pass/fail ya 0–1 compute — exact match, JSON schema, ya LLM-judge), aur **trajectory** (steps ki list — kaunse tools, kis order mein, jaise `["search", "hitl", "refund"]`). **LLMOps** is poore system ka ops hai (CI eval + traces + deploy gates), aur **regression** matlab naya change purana score gira de (prompt v2: 87% vs baseline 92%).

Classic ML se farak: wahan tum model weights train karke accuracy validate karke deploy karte the; LLMOps mein tum prompt/graph **config** change karte ho (weights aksar vendor-managed), aur eval pass-rate gate banta hai. Ek mini golden record aisा dikhta hai:

```json
{ "id": "case_01", "input": "Refund order o_123 if amount under 500",
  "expected_output": "Refund initiated for o_123",
  "expected_steps": ["get_order", "propose_refund", "hitl", "execute_refund"] }
```

Yahan `expected_output` outcome eval ka target hai, aur `expected_steps` trajectory eval ka — aur is list mein **order matter karta hai** (HITL refund se pehle aana chahiye).

> **Ruko, socho:** Eval aur ek normal unit test mein farak kya hai? (Jawab: unit test deterministic hota hai — ek exact answer pass/fail. Eval probabilistic output ko handle karta hai — ek dataset pe score *distribution* deta hai (jaise 92% pass) aur fuzzy scorers (similarity, judge) use karta hai, taaki ek paraphrase se test toot na jaaye.)

**§0 checkpoint:** (1) Eval vs unit test? (2) Trajectory eval agent apps mein kyun zaroori? (3) Golden dataset production logs se seedha copy karna safe hai?

---

### §1. Problem pehle — "lagता hai theek hai" ship karna

Tumne planner prompt badla, demo pe ek baar chal gaya, ship kar diya. Production mein: 30% workflows galat tool-order use kar rahe, destructive actions pe HITL skip ho raha, RAG answers sahi *lagte* hain par citations missing. Bina eval ke yeh sab customer complaint → firefight → blind rollback ban jaata hai. Eval se yeh PR pe hi pakda jaata: `ci_eval.sh` chalta hai, pass rate 87% baseline 92% se kam, merge block. Yahi tumhara nightly recon golden file ka dimaag hai — mismatch pe deploy nahi.

> **→ Practice A1** (pass: 10 valid golden cases committed).

---

### §2. Outcome eval vs trajectory eval

Yeh distinction agent apps ke liye critical hai. **Outcome eval** poochhता hai "end result sahi hai?". **Trajectory eval** poochhता hai "process sahi tha?" — sahi tools, sahi order mein. Khatra yahan hai: agent ne *sahi jawab* de diya, par **bina HITL ke refund execute** kar diya — outcome pass, par yeh ek serious incident hai. Isliye agent apps mein outcome-only eval khatarnak hai; trajectory bhi chahiye.

```python
def score_trajectory(actual: list[str], expected: list[str]) -> bool:
    return actual == expected                 # strict order (practice A2)

def score_outcome(actual: str, expected: str) -> bool:
    return expected.lower() in actual.lower() # simple contains — prod mein behtar scorer
```

> **Ruko, socho:** Tumhara agent ne refund process kiya, final answer "Refund done for o_123" bilkul sahi hai, outcome eval pass. Phir bhi yeh fail hona chahiye — kyun? (Jawab: agar usne `hitl` step skip karke `execute_refund` kiya, to process galat tha — bina approval ke paisा bhejа. Trajectory eval yeh pakadta hai jo outcome miss karta.)

> **→ Practice A2** (pass: trajectory scorer report).

---

### §3. Scorers — exact match se LLM-as-judge

Scorer choose karna trade-off hai. **Exact match** classification/fixed strings ke liye, par paraphrase pe flaky. **Regex/JSON schema** structured output ke liye, par sirf syntax check karta hai, semantics nahi. **Embedding similarity** paraphrase handle karta hai, par threshold tune karna padta hai. **LLM-as-judge** open-ended quality ke liye sabse flexible, par bias laata hai.

```python
JUDGE_PROMPT = """Score 1-5: Does ANSWER correctly address QUESTION given CONTEXT?
Return JSON: {"score": int, "reason": str}"""
```

LLM-judge ka bias interview mein poochha jaata hai, to yaad rakho: judge verbose answers ko zyada score deta hai; agar judge aur generator same model family hain to judge lenient hota hai; aur position bias (pehla option prefer). Mitigations: alag judge model use karo, blind A/B karo, aur 5% sample ka human audit. (Aur judge ko bhi structured output do, warna uska JSON toot sakta hai; judge model version pin karo taaki scores drift na karein.)

---

### §4. Langfuse — traces, scores, datasets

**Langfuse** LLM-app observability deta hai — har run ka trace, scores attach karna, aur dataset pe batch eval. Ek production trace ek tree hai:

```
trace_id: abc
  span: planner.llm_call    (tokens, latency, prompt hash)
  span: tool.search_orders  (args, result summary)
  span: hitl.wait           (duration)
  span: executor.refund     (idempotency_key)
  score: trajectory_match = 1.0
  score: cost_usd = 0.04
```

```python
trace = langfuse.trace(name="workflow_run", user_id="tenant_1")
trace.generation(name="planner", model="claude-sonnet", input=prompt, output=plan)
trace.score(name="valid_json", value=1.0)
```

Trace poori request ka tree hai, span ek step (LLM call/tool/DB), score ek eval result jo attach hota hai, aur dataset golden cases jinpe batch run hota hai. Asli faayda debugging mein: user complaint aaye → `trace_id` se trace kholo → spans dekho → exactly kaunsा step fail hua. (Ek tip: `user_id` ko stable tenant-id rakho, har call pe random nahi — warna high cardinality.)

---

### §5. CI regression — prompt change ko gate karo

Yeh poore module ka payoff hai — eval ko ek **automated gate** banao taaki regression merge hi na ho:

```bash
BASELINE=0.92
MIN_PASS=0.87                                    # baseline − allowed delta
PASS_RATE=$(python trajectory_scorer.py --json | jq .pass_rate)
if (( $(echo "$PASS_RATE < $MIN_PASS" | bc -l) )); then
  echo "REGRESSION: $PASS_RATE < $MIN_PASS"; exit 1   # merge block
fi
echo "OK: $PASS_RATE"; exit 0
```

Flow: PR khulti hai → GitHub Actions `ci_eval.sh` chalata hai → scorer golden dataset pe chalta hai → agar `pass_rate` baseline-minus-delta se kam hua → `exit 1` → merge block; warna allowed. Ek must-do: eval runs `temperature=0` pe karo, warna CI khud flaky ho jaayega (random output, random pass-rate). Aur baseline ko sirf jaanboojhke (intentional PR mein) badhao jab tum sach mein improve karo — accidental drift se nahi.

> **→ Practice A3** (pass: `bash ci_eval.sh` regression pe exit 1 de).

---

### §6. Online vs offline evals

Do jagah eval hota hai. **Offline** pre-deploy CI mein chalता hai — golden/synthetic data pe, batch (predictable cost), full privacy control, aur *known* regressions pakadta hai. **Online** post-deploy production mein — live traffic ka sample, ongoing cost, PII risk (careful), aur *drift* + naye user patterns pakadta hai. Online examples: random 1% traces ko LLM-judge pe bhejo, user thumbs up/down (weak par useful signal), aur weekly pass-rate 5% gire to alert.

Ek **bahut zaroori rule**: eval data production PII nahi honi chahiye — synthetic invoices banao, sanitized subset (names/card numbers mask), aur prod DB ko wholesale git mein kabhi copy mat karo.

---

### §7. SLIs — dashboard pe kya rakho

Production mein yeh signals track karo, har ek ka apna reason: latency p50/p99 (UX + timeout tuning), cost per request/task (margin per tenant), eval pass rate (quality trend), HITL approval rate (UX friction signal), tool error rate (MCP/integration health), aur cache hit rate (gateway savings — Project C). Project B ki interview line yahi se banti hai: "trajectory eval CI gate + Langfuse cost-per-task — ship se pehle regressions block hote hain."

---

### §8. Eval workflow — pehli baar CI setup

Ek pattern jo har naya banda galat karta hai: "eval baad mein karenge" = kabhi nahi. Pehle din se golden file + scorer banao. Steps: `golden_dataset.json` commit karo (10 cases minimum, badhate jao) → `trajectory_scorer.py` har case pe pass/fail de → locally run karke pass-rate dekho → `ci_eval.sh` mein baseline set karo → GitHub Actions/pre-push mein exit-code check → prompt change pe eval → compare → merge ya fix.

```bash
cd modules/10-evals-llmops/practice
python3 -m venv .venv && source .venv/bin/activate
pip install pydantic python-dotenv
python trajectory_scorer.py      # Pass rate: 0.XX (N/N cases)
bash ci_eval.sh; echo $?         # 0 = OK, 1 = regression
```

Achhe golden cases ki nishani: `id` unique, `input` realistic, `expected_output` measurable, `expected_steps` mein order tahan jahan safety matter karti hai (HITL before execute), aur kam se kam 2 failure-style inputs (invalid request → graceful error). Agar `pass_rate` hamesha 1.0 aata hai, to cases trivial hain — harder add karo.

---

## Practice

> **Saare assignments**: [`practice/README.md`](practice/README.md). Code **tum** likhoge.
> Stuck? `@modules/10-evals-llmops/MODULE.md` + error paste.

| # | Theory § | File | Pass when |
|---|----------|------|-----------|
| A1 | §0–§2 | `golden_dataset.json` | 10 valid cases, trajectory fields |
| A2 | §2–§4 | `trajectory_scorer.py` | Dataset pe pass/fail report |
| A3 | §5 | `ci_eval.sh` | Pass rate gire to exit 1 |

---

## Active recall (khud jawab likho NOTES mein)

1. LLM-as-judge bias — 3 types + 1 mitigation each?
2. Eval dataset ko production PII se alag kaise rakhoge?
3. Outcome pass + trajectory fail — ek real incident example?
4. CI baseline 92%, prompt change 87% — kya karoge?

**Chat drill** (optional): "Module 10 — outcome vs trajectory + CI gate."

---

## Progress checklist

- [ ] §0 — eval, golden, trajectory, LLMOps terms
- [ ] Session table follow
- [ ] Practice A1–A3 pass
- [ ] Redraw challenge
- [ ] Active recall NOTES
- [ ] NOTES session log

---

## Optional appendix

- [Langfuse Docs](https://langfuse.com/docs)
- [DeepEval Getting started](https://docs.confident-ai.com/docs/getting-started)
- Module 05 — RAG eval · Module 11 M6 — workflow eval harness
