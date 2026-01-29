// Copyright 1998-2024 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerAttributes.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UCharacterMovementComponent;

/**
 * Player character for fps_survival.
 * Handles movement, camera control, and basic gameplay.
 * Supports both first-person and third-person camera modes.
 */
UCLASS()
class FPS_SURVIVAL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// ===== Components =====
	
	/** First-person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* FirstPersonCamera;

	/** Spring arm for third-person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;

	/** Third-person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* ThirdPersonCamera;

	// ===== Enhanced Input System =====

	/** Enhanced Input System mapping context */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	/** Movement input action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	/** Look input action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	/** Jump input action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;

	/** Camera toggle input action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* CameraToggleAction;

	// ===== Attributes =====

	/** Player attributes (movement, jump, strength, etc.) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FPlayerAttributes Attributes;

	// ===== Camera State =====

	/** Whether we're in first-person mode (true) or third-person mode (false) */
	UPROPERTY(BlueprintReadOnly, Category = "Camera")
	bool bIsFirstPerson = true;

	// ===== Input Callbacks =====

	/** Called when movement input is received */
	void Move(const FInputActionValue& Value);

	/** Called when look input is received */
	void Look(const FInputActionValue& Value);

	/** Toggle between first-person and third-person camera */
	void ToggleCameraMode();

	/** Update which camera is active */
	void UpdateActiveCamera();
};
