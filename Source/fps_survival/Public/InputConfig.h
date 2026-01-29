// Copyright 1998-2024 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputActionValue.h"
#include "InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * Input configuration data asset for fps_survival.
 * Holds references to all input actions and mapping contexts.
 * 
 * This asset is created once and referenced by the player character.
 * Input actions are created programmatically in code.
 */
UCLASS()
class FPS_SURVIVAL_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	/** Movement input action (WASD) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	/** Look input action (Mouse) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	/** Jump input action (Space) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;

	/** Camera toggle input action (V) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* CameraToggleAction;

	/** Default input mapping context */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;
};
