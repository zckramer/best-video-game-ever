// Copyright 1998-2024 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SurvivalGameMode.generated.h"

/**
 * Game mode for survival gameplay in fps_survival.
 * Handles game state, player spawning, and survival-specific logic.
 * 
 * This is a generic game mode that can be extended for different game states
 * (menu, gameplay, etc.) but maintains core gameplay logic for survival mode.
 */
UCLASS()
class FPS_SURVIVAL_API ASurvivalGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASurvivalGameMode();

	virtual void BeginPlay() override;
};
