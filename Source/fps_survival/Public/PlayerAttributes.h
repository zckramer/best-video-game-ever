// Copyright 1998-2024 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerAttributes.generated.h"

/**
 * Player character attributes for fps_survival.
 * Stores core player stats and gameplay parameters.
 */
USTRUCT(BlueprintType)
struct FPlayerAttributes
{
	GENERATED_BODY()

public:
	/** Movement speed in units per second */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeed = 600.0f;

	/** Jump force/height multiplier */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float JumpForce = 420.0f;

	/** Generic strength attribute for future use (carrying, combat, etc.) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	float Strength = 1.0f;
};
