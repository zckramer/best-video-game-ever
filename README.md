# fps_survival - Unreal Engine 5.7 FPS Survival Game

A C++ based FPS Survival game project built with Unreal Engine 5.7.

## Project Overview

- **Engine**: Unreal Engine 5.7
- **Language**: C++ (C++14 compatible)
- **Primary Platform**: Windows
- **Game Type**: FPS Survival
- **Development Approach**: **Code-First** (Core systems in C++, Blueprints for customization only)

See [`.copilot-context.md`](.copilot-context.md) for detailed code guidelines, architecture documentation, and the **CODE-FIRST methodology** that guides all development.

## Quick Start

### Prerequisites
- Unreal Engine 5.7 or later
- Visual Studio 2022 Community (or Pro/Enterprise)
- Windows 10/11

### Setup Instructions

1. **Clone the repository**
   ```bash
   git clone <your-repo-url> fps_survival
   cd fps_survival
   ```

2. **Generate Visual Studio project files**
   - Right-click on `fps_survival.uproject` → "Generate Visual Studio project files"

3. **Open the solution**
   - Open `fps_survival.sln` in Visual Studio 2022

4. **Build the project**
   - In Visual Studio, select `Development_Editor` configuration
   - Build → Build Solution (F7)

5. **Open in Unreal Engine**
   - Double-click `fps_survival.uproject` to launch the editor

## Project Structure

```
fps_survival/
├── Source/
│   ├── fps_survival/
│   │   ├── Public/           # Public headers (UCLASS declarations)
│   │   ├── Private/          # Implementation (.cpp files)
│   │   └── fps_survival.Build.cs
│   ├── fps_survival.Target.cs
│   └── fps_survivalEditor.Target.cs
├── Content/                  # Game assets, maps, blueprints
├── Plugins/                  # Project-specific plugins
├── .copilot-context.md       # AI Assistant guidelines
├── .gitignore
├── .gitattributes
├── .editorconfig             # Code style configuration
└── fps_survival.uproject     # Project definition
```

## Development Guidelines

See [`.copilot-context.md`](.copilot-context.md) for detailed code guidelines, architecture documentation, and the **CODE-FIRST methodology** that guides all development.

See [GIT_WORKFLOW.md](GIT_WORKFLOW.md) for **branching strategy, PR process, and release management** (Trunk-Based Development with Release Branches).

## Version Control

This project uses Git for version control with the following conventions:

### Important Files to Commit
- ✅ `Source/` directory (all C++ source code)
- ✅ `Content/` directory (game assets, maps, blueprints)
- ✅ `Plugins/` directory (custom plugins)
- ✅ `.uproject` file
- ✅ `.copilot-context.md` (development guidelines)
- ✅ Configuration files (`.editorconfig`, etc.)

### Files/Folders to Ignore
- ❌ `Binaries/` - Compiled executables
- ❌ `Intermediate/` - Intermediate build files
- ❌ `Saved/` - Runtime generated data
- ❌ `.vs/` - Visual Studio cache
- ❌ `*.sln.DotSettings.user` - IDE personal settings

See [`.gitignore`](.gitignore) and [`.gitattributes`](.gitattributes) for complete details.

### Recommended Workflow

```bash
# Feature branch development
git checkout -b feature/player-controller
# ... make changes ...
git add Source/fps_survival/Public/MyPlayerController.h
git commit -m "feat: implement player movement system"

# Keep main/master branch stable
git checkout main
git pull origin main
git merge feature/player-controller
git push origin main
```

### Commit Message Convention

Follow [Conventional Commits](https://www.conventionalcommits.org/):

```
type(scope): description

feat(player): add sprint ability
fix(weapon): correct reload animation timing
docs(readme): update setup instructions
refactor(controller): simplify input handling
```

**Types**: `feat`, `fix`, `docs`, `style`, `refactor`, `test`, `chore`

## Building & Testing

### Build Configurations
- **Development** - For active development with debugging
- **Shipping** - For final release builds
- **Test** - For automated testing

### Compiling C++ Code
```bash
# In Visual Studio
Build → Build Solution (F7)

# Or from command line
C:\UE_5.7\Engine\Build\BatchFiles\Build.bat fps_survivalEditor Win64 Development -Project="C:\path\to\fps_survival.uproject" -WaitMutex
```

### Known Issues

- **Live Coding conflicts**: If you get "Unable to build while Live Coding is active", close the UE5 editor and try again (Ctrl+Alt+F11 in editor to disable Live Coding)
- **UHT reflection errors**: Ensure all UCLASS/USTRUCT declarations follow guidelines in `.copilot-context.md`

## Contributing

1. Create a feature branch from `main`
2. Follow code guidelines in [`.copilot-context.md`](.copilot-context.md)
3. Ensure code compiles without warnings
4. Create a pull request with descriptive commit messages
5. Get code review before merging

## Resources

- [Unreal Engine 5.7 Documentation](https://docs.unrealengine.com/5.7/)
- [Unreal Engine C++ API](https://docs.unrealengine.com/5.7/en-US/API/)
- [GitHub Documentation](https://docs.github.com)

## License

[Specify your license here - e.g., MIT, Apache 2.0, etc.]

## Contact

For questions or issues, contact the development team.

---

**Last Updated**: 2024
