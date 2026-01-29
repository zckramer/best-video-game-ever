# Version Control Setup Guide

Complete guide for setting up GitHub (or other Git repositories) for your UE5.7 fps_survival project.

## Quick GitHub Setup

### 1. Create a GitHub Repository

1. Go to [github.com](https://github.com) and sign in
2. Click **+** (top right) → **New repository**
3. Name: `fps_survival`
4. Description: `Unreal Engine 5.7 FPS Survival Game`
5. Choose: **Private** (recommended for personal projects)
6. **DO NOT** initialize with README, .gitignore, or license (we already have these)
7. Click **Create repository**

### 2. Initialize Local Git Repository

Open PowerShell in your project root (`C:\UE_5.7\Projects\fps_survival\`) and run:

```powershell
# Initialize git repository
git init

# Configure user (do this once globally or per-project)
git config user.name "Your Name"
git config user.email "your.email@example.com"

# Add all tracked files
git add Source/ Content/ Plugins/ *.uproject *.md .gitignore .gitattributes .editorconfig

# Create first commit
git commit -m "chore: initial commit - project structure and documentation"

# Add remote repository (replace USERNAME and REPO_NAME)
git remote add origin https://github.com/USERNAME/fps_survival.git

# Push to GitHub (choose main or master based on GitHub default)
git branch -M main
git push -u origin main
```

### 3. Configure .gitignore and .gitattributes

These files are already created in your project root:
- `.gitignore` - Excludes generated/temporary files
- `.gitattributes` - Handles line endings and binary files correctly
- `.editorconfig` - Enforces code style consistency

**These are critical for Unreal Engine projects!** Without them:
- Your repository will become bloated with generated files
- Binary assets may get corrupted on different operating systems
- Line ending inconsistencies can cause merge conflicts

### 4. Verify What Will Be Committed

Before your first commit, check what's included:

```powershell
# See all files git plans to track
git status

# See actual files (filtered by .gitignore)
git add -n --all

# To exclude something not in .gitignore temporarily:
git add Source/ Content/ *.uproject *.md
```

## Authentication

### Option A: Personal Access Token (Recommended for CI/CD)

```powershell
# Clone using token
git clone https://YOUR_TOKEN@github.com/USERNAME/fps_survival.git
```

### Option B: SSH Keys (Most Secure)

1. Generate SSH key (if you don't have one):
   ```powershell
   ssh-keygen -t ed25519 -C "your.email@example.com"
   ```

2. Add to GitHub: Settings → SSH and GPG keys → New SSH key

3. Update remote to use SSH:
   ```powershell
   git remote set-url origin git@github.com:USERNAME/fps_survival.git
   ```

### Option C: Git Credential Manager (Windows)

1. Install [Git Credential Manager](https://github.com/git-ecosystem/git-credential-manager)
2. Run once:
   ```powershell
   git credential-manager configure
   ```
3. When prompted, authenticate via browser

## Daily Workflow

### Starting Work

```powershell
# Get latest changes
git pull origin main

# Create feature branch
git checkout -b feature/my-feature-name
```

### Making Changes

```powershell
# Check what changed
git status
git diff Source/fps_survival/Public/MyPlayerController.h

# Stage specific files (recommended)
git add Source/fps_survival/Public/MyPlayerController.h
git add Source/fps_survival/Private/MyPlayerController.cpp

# Or stage all changes (less safe)
git add .

# Commit with descriptive message
git commit -m "feat(player): implement movement controller"
```

### Pushing Changes

```powershell
# Push feature branch
git push origin feature/my-feature-name

# Create Pull Request on GitHub
# Then merge on GitHub (this is where code review happens)

# Switch back to main locally
git checkout main
git pull origin main
```

## Useful Git Commands

```powershell
# View commit history
git log --oneline

# View changes not yet committed
git diff

# View staged changes
git diff --cached

# Undo unstaged changes
git checkout -- Source/fps_survival/MyFile.h

# Undo staged changes
git reset HEAD Source/fps_survival/MyFile.h

# View branches
git branch -a

# Delete local branch
git branch -d feature/my-feature-name

# View remote origin
git remote -v
```

## Handling Large Files (Optional)

If your Content/ folder gets very large, consider Git LFS:

```powershell
# Install Git LFS
# (Windows: winget install git-lfs, or download from https://git-lfs.github.com)

# Initialize LFS in repository
git lfs install

# Track large file types
git lfs track "*.uasset"
git lfs track "*.umap"
git lfs track "*.fbx"
git lfs track "*.blend"

# Commit tracking file
git add .gitattributes
git commit -m "chore: configure git lfs for large assets"
```

## Troubleshooting

### "Permission denied (publickey)"

You likely need SSH authentication configured. See **Authentication** → **Option B** above.

### ".gitignore isn't working"

Files already tracked won't be ignored. Remove from tracking:

```powershell
# Don't delete local files, just untrack from git
git rm --cached Intermediate/ -r
git commit -m "chore: remove intermediate files from tracking"
```

Then these files will be properly ignored by `.gitignore`.

### Large commit sizes (>100MB)

GitHub has a file size limit of 100MB per file. If you exceed:
1. Use Git LFS (see above)
2. Or break the project into multiple repositories
3. Or use external storage (OneDrive, cloud storage, etc.)

### Line ending problems ("LF vs CRLF")

The `.gitattributes` file should handle this, but if you still have issues:

```powershell
# Normalize line endings
git add --renormalize .
git commit -m "chore: normalize line endings"
```

## GitHub Project Management (Optional)

For better organization:

1. **Issues** - Track bugs, features, tasks
2. **Projects** - Kanban board for sprint planning
3. **Milestones** - Group issues into releases
4. **Labels** - Categorize issues (bug, feature, documentation, etc.)

Example workflow:
```
Issue: "Implement player controller"
  → Create feature branch from issue
  → Create PR linking to issue
  → Merge PR (closes issue automatically)
```

## Recommended .gitignore Special Cases

If you need to track specific files normally ignored:

```bash
# Example: Track a specific DLL needed for development
!Binaries/Win64/UE4Editor-fps_survival.dll

# Example: Track Plugins public API
!Plugins/MyPlugin/Binaries/Win64/UE4Editor-MyPlugin.dll
```

Add these to `.gitignore` after the blanket exclude rule.

---

**For questions**: Refer to [Git Documentation](https://git-scm.com/doc) or [GitHub Help](https://docs.github.com)
