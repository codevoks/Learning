# A3 — SFT vs DPO vs GRPO vs "RL zaroorat nahi" (tum bharoge)

> Har scenario ke liye chuno aur **kyun** (§1, §4 use karo). Yaad rakho — pehle
> sasta/simple (prompt/RAG/SFT), RL sirf jab preferences/alignment sach mein chahiye.

| # | Scenario | Choice | Reason (1-2 lines) |
|---|----------|--------|--------------------|
| 1 | Model ko ek fixed JSON format sikhana hai (500 labelled examples) | | |
| 2 | Model helpful + polite bane; "achha jawab" subjective hai, preference data available | | |
| 3 | Math/coding reasoning model — jawab verifiable (sahi/galat), quality improve karni | | |
| 4 | Bas latest company FAQ answer karna hai (har hafte badalti) | | |

## Bonus

- Reward hacking ek example + 2 defenses.
- RL fine-tune ka result kaise defend karoge — kaunse 2 evals (loss kyun nahi)?
