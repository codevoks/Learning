# Module 02 — SQL Mastery 🔥

> **Agent spawn**: `@Memory.md` + `@Prompt.md` + this file + `@NOTES.md`
> **Nav**: ← [01 Relational & ER](../01-relational-model-er/MODULE.md) · Next → [03 Normalization](../03-normalization/MODULE.md)

## At a glance
| | |
|---|---|
| Prerequisites | 01 |
| Duration | ~3+ sessions (query practice heavy) |
| Exit test | 2nd-highest 3 ways + window vs GROUP BY + recursive CTE |

## Visual map
```
JOINS (Venn):
  INNER  : A ∩ B          LEFT : all A + matching B
  RIGHT  : all B + match A FULL : A ∪ B

WINDOW vs GROUP BY:
  GROUP BY  → collapses rows (1 row per group)
  WINDOW    → keeps all rows, adds computed column over PARTITION
```
```mermaid
flowchart LR
    Q[Query] --> FROM --> WHERE --> GROUP[GROUP BY] --> HAVING --> SELECT --> ORDER[ORDER BY] --> LIMIT
```
**Mental model**: SQL logical order ≠ written order. FROM→WHERE→GROUP BY→HAVING→SELECT→ORDER→LIMIT. Window functions = "GROUP BY jaisa compute, par rows nahi gira-te".

**Redraw challenge**: Query execution order + window vs GROUP BY difference.

## Objectives
1. All joins + subqueries + CTEs
2. Aggregation + HAVING; window functions
3. Set ops, NULL handling, UPSERT
4. Logical query processing order

## Topics
- SELECT/WHERE/ORDER/LIMIT/DISTINCT
- JOINs: INNER, LEFT/RIGHT/FULL OUTER, CROSS, SELF
- GROUP BY + HAVING; COUNT/SUM/AVG/MIN/MAX
- Subqueries: scalar, correlated, EXISTS/IN/ANY/ALL
- CTEs (WITH) + recursive CTE
- Window functions: ROW_NUMBER/RANK/DENSE_RANK, LAG/LEAD, running totals, PARTITION BY
- CASE; UNION/INTERSECT/EXCEPT; NULL (3-valued logic); INSERT/UPDATE/DELETE/UPSERT; views

## Assignments (SQL — khud likho + run karo)
| # | Task | Passing criteria |
|---|------|------------------|
| A1 | Join + aggregation report (e.g. revenue per category) | Correct result on sample data |
| A2 | 2nd-highest salary — 3 ways (subquery, LIMIT/OFFSET, window) | All 3 give same answer, handle ties |
| A3 | Running total + RANK per group (window) | Correct per-partition output |
| A4 | Recursive CTE — org hierarchy / category tree | Full tree traversal |
| A5 | Find + delete duplicates keeping one | Only dups removed |
| A6 | Gaps-and-islands (consecutive ranges) | Correct islands |

## Active recall bank
1. Window function vs GROUP BY — kab kya?
2. Correlated subquery normal subquery se kaise alag (execution)?
3. LEFT JOIN + WHERE on right table — kya galat ho sakta?
4. NULL = NULL kya return karta?

## Progress checklist
- [ ] Query order + joins from memory
- [ ] A1–A6 run + pass
- [ ] NOTES.md updated
