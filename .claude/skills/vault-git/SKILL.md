---
name: vault-git
description: >-
  Safely commit and push changes in Vansh's Learning vault when the iCloud
  "drama" strikes — git fetch/push/commit/rebase hanging or timing out. The
  Desktop copy (~/Desktop/Code/Learning) lives in an iCloud-synced folder where
  .git writes lock up; the canonical non-iCloud repo is ~/Code/Learning. Use
  this skill whenever Vansh says "commit", "push", "save to github", "git",
  "push kardo", or when any git operation hangs/times out in this repo. It
  routes the commit + push through the canonical repo so it never hangs.
---

# vault-git — iCloud-safe commit & push

Vansh's `Learning` vault exists in **two places**:

| Copy | Path | Role |
|------|------|------|
| **Desktop (iCloud)** | `/Users/vansh/Desktop/Code/Learning` | Where Vansh *edits* (Obsidian / Cursor). Usually the session cwd. **`.git` writes hang here** — iCloud holds a lock on index/packfiles. |
| **Canonical (non-iCloud)** | `/Users/vansh/Code/Learning` | The **git source of truth**. Clone'd fresh from GitHub, outside iCloud. All commits + pushes happen here — never hangs. |

The remote is `https://github.com/codevoks/Learning.git`, branch `main`.

**Golden rule: never fight the Desktop copy's git. Move the changed files to the canonical repo and do all git there.**

## When to use

- Vansh asks to commit / push / "save to github".
- Any `git fetch/push/commit/rebase` in the Desktop path hangs or times out (the classic symptom: command runs >60s with no output).

## Procedure

### 1. Find what changed (in the copy Vansh edited)

Usually edits are in the Desktop copy (session cwd). Identify the specific files you intend to ship — by what you just edited, or:

```bash
cd "/Users/vansh/Desktop/Code/Learning"
git status --porcelain        # READ ops usually work; if this hangs, rely on the files you know you touched
```

⚠️ **Only ship the files you deliberately changed.** The two copies have pre-existing divergence (e.g. an `HLD` rename, in-progress reorgs). Do **not** bulk-copy or `git add -A` — you'll sweep up unrelated work. List the exact paths.

### 2. Confirm the remote is reachable (instant, never hangs)

```bash
cd "/Users/vansh/Code/Learning"
git ls-remote --heads origin main
```

If this returns a SHA quickly, connectivity is fine and any earlier hang was the iCloud `.git` write lock — proceed. If it hangs too, it's a real network problem, not iCloud.

### 3. Make the canonical repo current

```bash
cd "/Users/vansh/Code/Learning"
git status -sb | head -1                 # confirm on main
git pull --ff-only origin main           # non-iCloud → safe & fast
```

If `pull` reports divergence (canonical has local commits), stop and inspect rather than force anything.

### 4. Copy the changed files Desktop → canonical

For each file you're shipping (same relative path in both):

```bash
cp "/Users/vansh/Desktop/Code/Learning/<relpath>" \
   "/Users/vansh/Code/Learning/<relpath>"
```

(If the edit was made directly in the canonical repo, skip this step.)

### 5. Stage exactly those files, commit, push — all in canonical

```bash
cd "/Users/vansh/Code/Learning"
git add "<relpath1>" "<relpath2>"
git diff --cached --stat                 # sanity: only the intended files
git commit -m "<message>

Co-Authored-By: Claude Opus 4.8 <noreply@anthropic.com>"
git push origin main
```

Verify the push line shows `oldsha..newsha  main -> main`.

### 6. (Optional) keep Desktop's local git from drifting

The Desktop copy may now be behind GitHub. That's fine — Vansh reads files there, and the files already hold the new content (he edited them). Don't try to `pull`/`rebase` the Desktop copy (it'll hang). If its local git ever truly corrupts, re-clone from GitHub into a non-iCloud path (see the `icloud-git-hang` memory).

## Hard-won rules (from past corruption)

- **One foreground git op at a time** on anything touching `.git`. Never run overlapping/background commits — they collide on the iCloud lock and corrupt the index ("index file smaller than expected").
- Canonical repo (`~/Code/Learning`) git ops are **safe in foreground** and fast.
- If a Desktop git op left junk: `rm -f .git/index.lock` and remove iCloud conflict copies (untracked files matching `' \d+\.(md|py)$'`, e.g. `Home 2.md`, `.git/index 3`).
- `git ls-remote` is your cheap "is it iCloud or the network?" probe.

## One-liner mental model

> Edit on Desktop → `cp` the changed files to `~/Code/Learning` → commit & push **there**. Desktop never touches the remote.
