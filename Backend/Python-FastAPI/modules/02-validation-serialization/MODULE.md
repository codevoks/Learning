# Module 02 — Validation & Serialization (Pydantic)

> **Agent**: `@Memory.md` + `@Prompt.md` + this + `@NOTES.md` · ← [01](../01-routing-handlers/MODULE.md) · Next → [03 Middleware](../03-middleware/MODULE.md)

## Visual map
```
class ItemIn(BaseModel):           class ItemOut(BaseModel):
    name: str = Field(min_length=1)    id: int
    price: float = Field(gt=0)         name: str
    # validators run on parse          # response_model = ItemOut (hides internals)

request JSON --validate--> ItemIn --handler--> ORM obj --serialize--> ItemOut --> JSON
```
**Mental model**: Pydantic = tumhara **Zod** Python mein. Request model (input contract) aur response model (output contract) alag rakho — security + clarity. Validation parse pe hoti, fail → 422 auto.

**Redraw**: input model → handler → output model pipeline.

## Objectives
1. `BaseModel`, fields, `Field` constraints
2. Validators (`field_validator`, `model_validator`)
3. Request vs response model split
4. `BaseSettings` for config

## Topics
- Types, defaults, `Field(gt/min_length/...)`; nested models; `Optional`/unions; aliases
- `field_validator` / `model_validator`; `ConfigDict`
- Input vs output models (why split); `model_dump`
- `BaseSettings` (env config)

## Assignments
| # | Task | Passing criteria |
|---|------|------------------|
| A1 | Input/output model pair + constraint + custom validator | Bad input → 422; output shaped |
| A2 | `BaseSettings` reading env | Config typed + loaded |

## Active recall
1. Pydantic = ? (Node analogy)
2. Request vs response model alag kyun?
3. Validator vs Field constraint?

## Checklist
- [ ] Input/output pipeline from memory · [ ] A1,A2 · [ ] NOTES updated
