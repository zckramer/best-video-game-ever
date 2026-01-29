// Copyright 1998-2024 Epic Games, Inc. All Rights Reserved.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputConfig.h"

APlayerCharacter::APlayerCharacter()
{
	// Don't rotate character with camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 300.0f;

	// Don't rotate pawn with camera
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create first-person camera
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(RootComponent);
	FirstPersonCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f)); // Roughly head height
	FirstPersonCamera->bUsePawnControlRotation = true;

	// Create third-person camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create third-person camera
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	ThirdPersonCamera->bUsePawnControlRotation = false;

	// Start in first-person
	bIsFirstPerson = true;
	UpdateActiveCamera();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputConfig && InputConfig->DefaultMappingContext)
			{
				Subsystem->AddMappingContext(InputConfig->DefaultMappingContext, 0);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("InputConfig or DefaultMappingContext is not set!"));
			}
		}
	}

	// Apply attribute values to movement
	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->MaxWalkSpeed = Attributes.MoveSpeed;
	}

	UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter spawned in %s mode"), bIsFirstPerson ? TEXT("First-Person") : TEXT("Third-Person"));
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!InputConfig)
	{
		UE_LOG(LogTemp, Error, TEXT("InputConfig is not set on PlayerCharacter!"));
		return;
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = 
		Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		if (InputConfig->MoveAction)
		{
			EnhancedInputComponent->BindAction(InputConfig->MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		}

		// Looking
		if (InputConfig->LookAction)
		{
			EnhancedInputComponent->BindAction(InputConfig->LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		}

		// Jumping
		if (InputConfig->JumpAction)
		{
			EnhancedInputComponent->BindAction(InputConfig->JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
			EnhancedInputComponent->BindAction(InputConfig->JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}

		// Camera toggle (V key)
		if (InputConfig->CameraToggleAction)
		{
			EnhancedInputComponent->BindAction(InputConfig->CameraToggleAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ToggleCameraMode);
		}
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Move forward/backward
		if (MovementVector.Y != 0.0f)
		{
			AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		}

		// Move left/right
		if (MovementVector.X != 0.0f)
		{
			AddMovementInput(GetActorRightVector(), MovementVector.X);
		}
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::ToggleCameraMode()
{
	bIsFirstPerson = !bIsFirstPerson;
	UpdateActiveCamera();
	UE_LOG(LogTemp, Warning, TEXT("Camera switched to %s mode"), bIsFirstPerson ? TEXT("First-Person") : TEXT("Third-Person"));
}

void APlayerCharacter::UpdateActiveCamera()
{
	if (bIsFirstPerson)
	{
		FirstPersonCamera->Activate();
		ThirdPersonCamera->Deactivate();
	}
	else
	{
		FirstPersonCamera->Deactivate();
		ThirdPersonCamera->Activate();
	}
}
