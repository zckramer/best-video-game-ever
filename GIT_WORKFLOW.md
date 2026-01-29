# Git Workflow: Trunk-Based Development with Release Branches

## Overview

This project uses **Trunk-Based Development** for feature work and **Release Branches** for shipping.

**Core Principle:** `main` is always compilable, testable, and ready to ship.

## Branch Structure

### Active Development

```
main (trunk)
  ↑ (PR merge, auto-build verification)
feature/short-descriptive-name
  → Lifetime: Hours to 1 day max
  → Examples: feature/player-sprint, feature/enemy-ai, feature/inventory-ui
```

### Release Management

```
release/X.Y (created when ready to ship)
  ↑ (hotfixes only, never new features)
  → Examples: release/1.0, release/1.1
  → Lifetime: Duration of that version's support
```

## Workflow Rules

### ✅ REQUIRED for All Development

1. **Create a feature branch from `main`**
   ```bash
   git checkout main
   git pull origin main
   git checkout -b feature/descriptive-name
   ```

2. **Keep feature branches SHORT-LIVED** (1-3 days max)
   - Push commits daily
   - Merge back to main frequently
   - Don't let features diverge for weeks

3. **Commit messages follow Conventional Commits**
   ```
   feat(scope): brief description
   fix(scope): brief description
   docs(scope): brief description
   refactor(scope): brief description
   ```

4. **Create Pull Request** before merging to main
   - Code review required
   - Build verification required (must compile)
   - All CI/CD checks pass

5. **Delete feature branch after merge**
   ```bash
   git branch -d feature/descriptive-name
   git push origin --delete feature/descriptive-name
   ```

### ❌ NEVER DO THIS

- ❌ Commit directly to `main` (always use a PR)
- ❌ Keep a feature branch alive for >3 days without merging
- ❌ Create a `develop` branch (that's what short-lived features are for)
- ❌ Merge broken code to `main` (PR will catch it)
- ❌ Push untested changes to `main`
- ❌ Add new features to `release/X.Y` branches

## Daily Workflow

### Starting Work

```bash
# Get latest main
git checkout main
git pull origin main

# Create feature branch
git checkout -b feature/what-you-are-building
```

### During Development

```bash
# Commit frequently with meaningful messages
git add Source/
git commit -m "feat(player): implement sprint acceleration"

# Push to origin daily (even if not done)
git push -u origin feature/what-you-are-building

# Keep synced with main (if work takes >1 day)
git fetch origin
git rebase origin/main
# If conflicts occur, resolve and continue
git rebase --continue
git push -f origin feature/what-you-are-building
```

### Finishing Work

```bash
# Ensure latest main
git fetch origin
git rebase origin/main

# Push final version
git push origin feature/what-you-are-building

# Create Pull Request on GitHub
# → Describe what changed and why
# → Link any issues
# → Wait for review and build verification

# After approval and merge
git checkout main
git pull origin main

# Delete local feature branch
git branch -d feature/what-you-are-building
git push origin --delete feature/what-you-are-building
```

## Branch Naming Convention

```
feature/player-movement           ✅ Clear and specific
feature/enemy-ai-pathfinding     ✅ Descriptive
feature/ui-inventory-panel       ✅ Good scope

feature/stuff                     ❌ Too vague
feature/new-thing                ❌ Not descriptive
feature/everything               ❌ Too broad
```

## Handling Merge Conflicts

Conflicts are **opportunities to integrate**, not problems:

```bash
# While rebasing on main
git rebase origin/main
# Conflicts appear

# Fix conflicts in your editor
# Then continue
git add .
git rebase --continue
git push -f origin feature/your-branch
```

**Philosophy:** Frequent small rebases = fewer huge conflicts

## Release Process

### When You're Ready to Ship v1.0

```bash
# Create release branch from main
git checkout main
git pull origin main
git checkout -b release/1.0

# Push release branch
git push origin release/1.0

# Build and test release/1.0
# Fix critical bugs only
git checkout release/1.0
git commit -m "fix: critical bug in release 1.0"
git push origin release/1.0

# Tag the release
git tag -a v1.0 -m "Release version 1.0"
git push origin v1.0

# Development continues on main for v1.1
git checkout main
# New features → feature/X → main (continues as normal)
```

### Hotfixing a Released Version

```bash
# If a critical bug is found in v1.0
git checkout release/1.0
git pull origin release/1.0

# Create hotfix
git checkout -b hotfix/1.0-critical-bug
git commit -m "fix: critical server bug in 1.0"
git push origin hotfix/1.0-critical-bug

# Create PR to release/1.0
# After merge:
git checkout release/1.0
git pull origin release/1.0

# Tag the patch
git tag -a v1.0.1 -m "Hotfix patch 1.0.1"
git push origin v1.0.1

# Also merge back to main
git checkout main
git merge release/1.0
git push origin main
```

## CI/CD Integration Points

**When should the build run?**

1. ✅ **On every feature branch push** - Catch compilation errors early
2. ✅ **Before PR merge to main** - Verify it compiles with latest main
3. ✅ **After merge to main** - Ensure main is always buildable
4. ✅ **Before release tag** - Verify release is shippable

**What should the build verify?**
- Compilation succeeds
- No critical warnings
- Basic game loads without crashing
- (Optional) Automated tests pass

## Common Questions

### Q: What if I need to work on something for a week?

**A:** Break it into smaller feature branches:
```
feature/inventory-backend (day 1, merge to main)
  → feature/inventory-ui (day 2, merge to main)
    → feature/inventory-pickup-system (day 3, merge to main)
```

Each piece works and is integrated. Safer than one week-long branch.

### Q: What if develop branch would be useful?

**A:** It wouldn't. Short-lived feature branches + frequent merges = same safety without the staleness.

### Q: Can I have long-running branches for experimental work?

**A:** No. But you can:
- Use a separate repo for experiments
- Keep experiments local (don't push)
- Prototype in Blueprint first
- Integrate pieces to main as validated

### Q: What if someone pushes broken code to main?

**A:** The PR process catches it (build fails). If it somehow merged:
1. Revert immediately: `git revert <commit-hash>`
2. Create a hotfix: `git checkout -b fix/revert-broken-code`
3. Fix the issue properly
4. Create PR to main

## Enforcing This Workflow

### GitHub Settings (Recommended)

1. **Protect main branch:**
   - Require pull request reviews (≥1)
   - Require status checks to pass (build must succeed)
   - Require branches to be up to date before merging
   - Include administrators in restrictions

2. **Protect release branches:**
   - Same as above
   - Restrict to hotfix branches only

### Local Git Hooks (Optional)

Prevent accidental direct commits to main:
```bash
# .git/hooks/pre-commit
if [ "$(git rev-parse --abbrev-ref HEAD)" == "main" ]; then
  echo "❌ Direct commits to main are not allowed"
  exit 1
fi
```

## Monitoring Branch Health

### Keep it Clean

```bash
# List branches
git branch -a

# Delete old/merged branches
git branch -d feature/old-feature
git push origin --delete feature/old-feature

# Check status
git log --oneline -10
```

### Red Flags

- ⚠️ Feature branch >3 days old without merge
- ⚠️ `main` branch fails to compile
- ⚠️ Multiple unmerged branches from same person
- ⚠️ Release branch with new features

## Quick Reference

| Action | Command |
|--------|---------|
| Start feature | `git checkout -b feature/name && git push -u origin feature/name` |
| Sync with main | `git fetch origin && git rebase origin/main && git push -f` |
| Finish feature | Create PR → Merge → Delete branch |
| Create release | `git checkout -b release/1.0 && git push origin release/1.0` |
| Hotfix release | `git checkout release/1.0 && git checkout -b hotfix/1.0-bug` |
| Tag version | `git tag -a v1.0 -m "Message" && git push origin v1.0` |

## Questions?

- Unsure if your branch should be a feature branch? → Yes, it should be
- Want to create a develop branch? → Ask first
- Pushing directly to main? → I will stop you
- Feature branch >3 days old? → I will remind you to merge

---

**This is how we keep main stable, compilable, and always ready to ship.** 🚀
