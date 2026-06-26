# System Design (HLD) — Home

> HLD vault entry point. ← back to [[INTERVIEW-PREP|Master Index]]

## Quick links
| Doc | Kya hai |
|-----|---------|
| [[System Design(HLD)/Memory\|Memory]] | Coach rules, profile, CV→HLD hooks |
| [[System Design(HLD)/Prompt\|Prompt]] | Hinglish coach persona |
| [[System Design(HLD)/LEARNING-PLAN\|LEARNING-PLAN]] | **Full syllabus** + 12 case studies |
| [[System Design(HLD)/VISUAL-STUDY-GUIDE\|VISUAL-STUDY-GUIDE]] | Master diagrams + estimation cheat sheet |

## Modules
| # | Syllabus | Notes | Focus |
|---|----------|-------|-------|
| 00 | [[System Design(HLD)/modules/00-framework/MODULE\|The Framework]] | [[System Design(HLD)/modules/00-framework/NOTES\|NOTES]] | How to attack any design Q |
| 01 | [[System Design(HLD)/modules/01-fundamentals-estimation/MODULE\|Fundamentals & Estimation]] | [[System Design(HLD)/modules/01-fundamentals-estimation/NOTES\|NOTES]] | Latency, throughput, back-of-envelope |
| 02 | [[System Design(HLD)/modules/02-scaling-load-balancing/MODULE\|Scaling & Load Balancing]] | [[System Design(HLD)/modules/02-scaling-load-balancing/NOTES\|NOTES]] | Horizontal, LB, stateless |
| 03 | [[System Design(HLD)/modules/03-caching/MODULE\|Caching]] | [[System Design(HLD)/modules/03-caching/NOTES\|NOTES]] | Strategies, eviction, invalidation |
| 04 | [[System Design(HLD)/modules/04-databases-at-scale/MODULE\|Databases at Scale]] | [[System Design(HLD)/modules/04-databases-at-scale/NOTES\|NOTES]] | SQL/NoSQL, shard, replicate |
| 05 | [[System Design(HLD)/modules/05-messaging-async/MODULE\|Messaging & Async]] | [[System Design(HLD)/modules/05-messaging-async/NOTES\|NOTES]] | Queues, Kafka, outbox |
| 06 | [[System Design(HLD)/modules/06-consistency-consensus/MODULE\|Consistency & Consensus]] | [[System Design(HLD)/modules/06-consistency-consensus/NOTES\|NOTES]] | CAP, Raft, quorum |
| 07 | [[System Design(HLD)/modules/07-api-ratelimit-idempotency/MODULE\|API, Rate Limit, Idempotency]] | [[System Design(HLD)/modules/07-api-ratelimit-idempotency/NOTES\|NOTES]] | API design, limits |
| 08 | [[System Design(HLD)/modules/08-resilience-observability/MODULE\|Resilience & Observability]] | [[System Design(HLD)/modules/08-resilience-observability/NOTES\|NOTES]] | Circuit breaker, OTEL |
| 09 | [[System Design(HLD)/modules/09-case-studies/MODULE\|Case Studies]] 🔥 | [[System Design(HLD)/modules/09-case-studies/NOTES\|NOTES]] | 12 classic designs |
| 10 | [[System Design(HLD)/modules/10-interview-template/MODULE\|Interview Template]] | [[System Design(HLD)/modules/10-interview-template/NOTES\|NOTES]] | Mock framework |

## Reading workflow
1. **Module 00 (framework) pehle** — har design isi se attack karoge
2. Building blocks 01–08 padho — har ek ka diagram
3. Module 09: har case study khud design karo, phir compare
4. Redraw challenge → `NOTES.md → My diagrams`
5. Coach: `@Memory.md @Prompt.md @modules/XX/MODULE.md`

## Dependency order
```mermaid
flowchart TD
    M00[00 Framework] --> M01[01 Fundamentals]
    M01 --> M02[02 Scaling/LB]
    M02 --> M03[03 Caching]
    M02 --> M04[04 DB at Scale]
    M04 --> M05[05 Messaging]
    M04 --> M06[06 Consistency]
    M02 --> M07[07 API/RateLimit]
    M02 --> M08[08 Resilience/Obs]
    M03 --> M09[09 Case Studies]
    M05 --> M09
    M06 --> M09
    M07 --> M09
    M08 --> M09
    M09 --> M10[10 Interview Template]
    style M09 fill:#fef3cd,stroke:#b45309
```

## Vault path
```
/Users/vansh/Desktop/Code/Learning/System Design(HLD)
```
