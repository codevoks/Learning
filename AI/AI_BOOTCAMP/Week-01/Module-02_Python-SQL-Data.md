# Module 02 - Python + SQL + Data Pipeline Basics

## Learning Outcome
Tum raw dataset ko clean, transform, aur query karke decision-ready output de paoge.

## Part A: Python for Data Work
- Data load (`csv`, `json`)
- Basic profiling (`shape`, `dtypes`, nulls, unique counts)
- Cleaning operations:
  - missing values
  - duplicates
  - type corrections
  - outlier handling (rule-based initially)
- Reusable functions likhna for repeatability

## Part B: SQL for Analytics/ML Features
- `SELECT`, `WHERE`, `GROUP BY`, `ORDER BY`
- joins (`inner`, `left`) with business logic
- aggregations for KPI
- data sanity queries

## Part C: Mini Pipeline Blueprint
1. ingest raw data
2. validate schema
3. clean and transform
4. store cleaned output
5. run SQL metrics queries
6. export summary

## Common Mistakes (Avoid)
- Leakage-like transformations using future data
- Silent dtype conversion bugs
- Null handling without reason
- Query without checking duplicates after joins

## Interview Lens
Prepare to answer:
- "Aapne missing values ko kaise choose kiya: drop vs impute?"
- "Joins ke baad row count suddenly kyu change hua?"
- "Agar daily data schema change ho jaye to kya karoge?"

## Mini Challenge (Day 2-3)
Closed-book 30 min:
- Python script likho jo null summary aur duplicate summary de
- 5 SQL queries likho:
  - top categories
  - daily trend
  - anomaly candidate rows
