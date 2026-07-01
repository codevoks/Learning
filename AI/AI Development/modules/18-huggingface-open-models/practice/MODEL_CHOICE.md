# A3 — Open vs API vs Hybrid (tum bharoge)

> Har scenario ke liye chuno (Closed API / Open self-host / Hybrid) aur **kyun**
> (§6: quality, cost, privacy, volume, fine-tune ke factors use karo).

| # | Scenario | Choice | Reason (1-2 lines) |
|---|----------|--------|--------------------|
| 1 | Healthcare startup — patient data kabhi third-party ko nahi jaana chahiye | | |
| 2 | Weekend prototype — sabse achhi quality, jaldi ship, low volume | | |
| 3 | 50M requests/month, mostly simple classification, cost bachana hai | | |
| 4 | Product jisme rare complex queries + high-volume simple queries dono | | |

## Bonus

- Open model self-host karne mein 2 hidden costs kya hain (infra/ops)?
- vLLM/quantization cost kaise girate hain — 1 line each?
