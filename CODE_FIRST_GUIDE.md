# CODE-FIRST DEVELOPMENT GUIDE

## The Principle

**All gameplay systems, mechanics, and core logic are implemented in C++ first.** Blueprints are tools for extending, customizing, and visually iterating on C++ systems—not for implementing core logic.

This is the single most important architectural decision for fps_survival.

## Why CODE-FIRST?

### 1. **Performance**
- C++ is compiled to native machine code
- Blueprint VM adds overhead on every operation
- Frame-critical code (tick, physics, input) MUST be C++

### 2. **Maintainability**
- C++ code is text-based and version-controllable
- Easy code review, refactoring, and testing
- Comments and documentation are natural

### 3. **Collaboration**
- Text-based source merges are solvable
- Binary Blueprint conflicts are impossible to resolve
- Your Git history is clean and meaningful

### 4. **Professional Standards**
- AAA studios code-first (Naughty Dog, Rockstar, FromSoftware)
- Enterprise-level practices
- Industry-standard approach

### 5. **Scalability**
- Easy to implement unit tests in C++
- CI/CD pipelines work with code
- Performance profiling is straightforward

## The Pattern

### Core Systems → Blueprint Extension

```
┌─────────────────────────────────────┐
│  C++ Base Class (Core Logic)        │
│  • Gameplay mechanics                │
│  • Input handling                    │
│  • Physics/calculations              │
│  • Performance-critical code         │
└──────────────┬──────────────────────┘
               │ inherits from
               ↓
┌─────────────────────────────────────┐
│  Blueprint Child Class (Customization)
│  • Visual tuning                     │
│  • Damage values                     │
│  • Particle effects                  │
│  • Animation events                  │
└─────────────────────────────────────┘
```

### Real Example: Weapon System

**C++ (Core System):**
```cpp
UCLASS()
class FPS_SURVIVAL_API AWeapon : public AActor
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Weapon")
    void Fire();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float FireRate;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    float Damage;

private:
    // Implementation
    void ApplyDamage(AActor* Target);
    void PlayFireAnimation();
};
```

**Blueprint (Customization):**
```
BP_AssaultRifle extends AWeapon
  → Set FireRate = 0.1
  → Set Damage = 35.0
  → Bind Fire animation event
  → Set muzzle flash particle
```

## What Goes Where?

### ✅ MUST Be in C++
- Input handling and control schemes
- Player movement and physics
- Combat mechanics and damage calculation
- AI decision-making
- Save/load systems
- Game state management
- Performance-critical loops (Tick, Physics)
- Inventory and item systems
- Networking/replication logic

### ✅ CAN Be in Blueprint (Extended from C++)
- Visual effects (particles, decals)
- Animation state machines (using C++ events as triggers)
- UI layouts (but not logic)
- Content-specific behavior (this sword has fire effect, that one doesn't)
- Level-specific gameplay (boss mechanics extending gameplay base)
- Audio cues and dialogue

### ❌ NEVER Blueprint-Only
- Core gameplay systems
- Frequently-updated logic
- Performance-critical code
- Shared mechanics across multiple actors
- Any logic that affects game balance

## Guidelines for Implementation

### 1. When Adding a New Feature

**Ask yourself:**
> "Is this core to the game's mechanics or just a customization of existing mechanics?"

**If core:** Implement in C++
**If customization:** Implement C++ base, extend in Blueprint

### 2. Blueprint Property Exposure

Use `UPROPERTY()` macros strategically:

```cpp
// ✅ Expose for designer tuning
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
float SprintSpeedMultiplier = 1.5f;

// ✅ Expose for Blueprint events
UFUNCTION(BlueprintCallable, Category = "Gameplay")
void OnSprintStart();

// ❌ Don't expose internal implementation
private:
    float _currentSprintDuration;
    bool _bIsSprintingInternal;
```

### 3. Blueprint Event Binding

When you want Blueprint to react to C++ events:

```cpp
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFired);

UCLASS()
class AWeapon : public AActor
{
    UPROPERTY(BlueprintAssignable, Category = "Weapon")
    FOnWeaponFired OnWeaponFired;

    void Fire()
    {
        // Fire logic
        OnWeaponFired.Broadcast(); // Blueprint listens and does visual effects
    }
};
```

## Common Mistakes (Don't Make These)

### ❌ Mistake 1: Blueprint-Only Game Mechanics
```
// WRONG: Implementing game logic purely in Blueprint
BP_Player
  → Jump logic in Blueprint event
  → Movement calculation in Blueprint
  → Damage taken calculation in Blueprint
```

### ✅ Correct: C++ Logic with Blueprint Customization
```cpp
// APlayerCharacter (C++)
void Jump() { /* C++ implementation */ }
void TakeDamage(float Amount) { /* C++ calculation */ }

// BP_Player (Blueprint extends APlayerCharacter)
// → Binds animations to Jump event
// → Plays sound on TakeDamage event
```

### ❌ Mistake 2: "We'll do logic in Blueprint for now, refactor to C++ later"
- This never happens
- Technical debt compounds
- Refactoring is harder later

### ❌ Mistake 3: Avoiding C++ because "Blueprint is faster to prototype"
- Initial speed ≠ long-term velocity
- C++ is faster once patterns are established
- Maintainability = actual development speed

## For AI Assistants Reading This

**When implementing features:**

1. **Default to C++** - Unless explicitly told otherwise
2. **Create extensible base classes** - Design for Blueprint customization
3. **Use UPROPERTY/UFUNCTION wisely** - Expose tuning parameters, not logic
4. **Follow existing patterns** - Check MainPlayerController, other classes
5. **Prioritize performance** - C++ is faster; use it for hot paths
6. **Document the intent** - Why C++? Why not Blueprint?

**When you see a request like:**
- "Add a new weapon" → C++ base class + Blueprint child
- "Tweak damage numbers" → UPROPERTY editable in Blueprint
- "Add visual effects" → Blueprint event binding to C++ code
- "New game mode" → C++ implementation with Blueprint customization points

**Red flags that suggest rethinking:**
- "Just prototype this in Blueprint" → Implement in C++ immediately
- "Blueprint will be fine for this" → Probably won't, use C++
- "We can refactor later" → Do it right the first time

## Performance Considerations

### When C++ is Non-Negotiable
- **Per-frame operations** (Tick, Physics Ticks)
- **Large data processing** (inventory with 100+ items)
- **Network replication** (RPCs, property replication)
- **Collision/raycast queries** (hundreds per frame in combat)
- **AI pathfinding** (multiple agents calculating paths)

### When Blueprint is Acceptable
- **One-time events** (game start, level transition)
- **UI updates** (once per frame at UI tick rate)
- **Non-interactive sequences** (cutscenes)
- **Content customization** (specific weapon variants)

## Testing and Validation

### C++ Code
- Unit tests (using Catch2 or UE's testing framework)
- Performance profiling with Unreal Insights
- Static analysis with PVS-Studio

### Blueprint-Extended Code
- Manual testing in editor
- PIE (Play In Editor) validation
- Blueprint unit tests (if complex)

## Prototyping Mode: "Just Get the Shit Done"

Sometimes you need to **rapidly explore ideas** without worrying about perfect architecture. This is legitimate and encouraged.

### When to Prototype
- Exploring game feel (camera height, sprint speed, damage values)
- Testing a new mechanic concept before committing to architecture
- Quick iteration on level design or gameplay balance
- Validating a "what if" before investing engineering time
- Time-sensitive features with unclear requirements

### Prototyping Rules
1. **Use Blueprints liberally** - No architectural purity required
2. **Document it as prototype** - Add comments: `// PROTOTYPE: testing grappling feel`
3. **Iterate in PIE** - Fast feedback loop is the goal
4. **Plan refactoring** - When the approach is validated, plan C++ implementation
5. **Don't commit** - Keep prototype Blueprints out of Git until production decision
6. **Keep scope small** - Prototypes should be narrow and focused

### Prototype → Production Pipeline

```
PROTOTYPE PHASE (Blueprint)
  → Rapid iteration in editor
  → Test game feel and mechanics
  → Validate design decisions
           ↓
DECISION POINT
  → "This mechanic is good!" = Move to C++
  → "This doesn't work" = Delete and try different approach
           ↓
PRODUCTION PHASE (C++)
  → Port validated approach to C++
  → Optimize for performance
  → Integrate into systems
  → Commit to Git
```

### Example: Grappling Hook Prototype

**Day 1 - Prototype (Blueprint):**
```
BP_GrapplingHookTest
  → Trace from player to world
  → Swing physics (just a linear interpolation for now)
  → Attach to hit point
  → Adjust swing speed in editor, test feel
  
// Comment: "PROTOTYPE - testing grappling feel. Swapping to C++ once mechanics locked."
```

**Day 2 - Validation:**
- Test in game → "Feels good, but needs tighter controls"
- Adjust Blueprint → "Better!"
- Lock down requirements

**Day 3 - Production (C++):**
```cpp
// APlayerCharacter.h
UFUNCTION(BlueprintCallable, Category = "Movement")
void InitiateGrapple(FVector TargetPoint);

// APlayerCharacter.cpp
void APlayerCharacter::InitiateGrapple(FVector TargetPoint)
{
    // Optimized C++ implementation
    // Performance-critical calculations
    // Integrated with movement system
}
```

### Why This Matters

**Prototyping in Blueprint:**
- ✅ Fastest feedback loop
- ✅ Easy to iterate on feel and balance
- ✅ Designer-friendly
- ✅ Perfect for "does this feel fun?"

**Production in C++:**
- ✅ Optimized performance
- ✅ Version controllable
- ✅ Testable and maintainable
- ✅ Professional codebase
- ✅ Easy to extend

**Best of both:** Prototype fast, refactor deliberate

---

## Summary

**CODE-FIRST** means:
- Core logic lives in C++
- Performance is optimized at the source
- Collaboration is easier
- Version control actually works
- The codebase scales professionally

**Blueprints** extend C++:
- Customization and tweaking
- Visual iteration
- Designer-friendly parameters
- Content-specific behavior

**Prototyping** is pragmatic:
- Rapid exploration of ideas
- Temporary Blueprint implementations
- Validated approaches move to C++
- Plan refactoring from the start

---

**Questions?** Refer to `.copilot-context.md` or ask in code review.

**Confused if something should be C++ or Blueprint?** Default to C++. It's almost always the right choice.
