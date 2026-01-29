// Copyright 1998-2024 Epic Games, Inc. All Rights Reserved.

#include "SurvivalGameMode.h"
#include "PlayerCharacter.h"

ASurvivalGameMode::ASurvivalGameMode()
{
	// Set the player character class to spawn
	DefaultPawnClass = APlayerCharacter::StaticClass();
	
	// Don't spawn players as spectators
	bStartPlayersAsSpectators = false;
}

void ASurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Survival Game Mode initialized"));
}
