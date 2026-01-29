// Copyright 1998-2024 Epic Games, Inc. All Rights Reserved.

#include "SurvivalGameMode.h"
#include "GameFramework/Character.h"

ASurvivalGameMode::ASurvivalGameMode()
{
	// Set the default pawn class to a basic character for now
	// This will be updated to APlayerCharacter once it's created
	// For now, use the engine's default character
	DefaultPawnClass = ACharacter::StaticClass();
	
	// Don't spawn players as spectators
	bStartPlayersAsSpectators = false;
}

void ASurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Survival Game Mode initialized"));
}
