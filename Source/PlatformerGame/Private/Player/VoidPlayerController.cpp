// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VoidPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

AVoidPlayerController::AVoidPlayerController()
{
}

void AVoidPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(MainContext)
	if (UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		LocalPlayerSubsystem->AddMappingContext(MainContext, 0);
	}
}

void AVoidPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVoidPlayerController::Move);
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AVoidPlayerController::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AVoidPlayerController::StopJump);

		EnhancedInputComponent->BindAction(FastFallAction, ETriggerEvent::Started, this, &AVoidPlayerController::FastFallPressed);
		EnhancedInputComponent->BindAction(FastFallAction, ETriggerEvent::Completed, this, &AVoidPlayerController::FastFallReleased);
	}
	
}

void AVoidPlayerController::Move(const FInputActionValue& ActionValue)
{
	const float Value = ActionValue.Get<float>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(FVector(1.f, 0.f, 0.f), Value);
		
	}
}

void AVoidPlayerController::StartJump()
{
	if (ACharacter* ControlledPawn = GetPawn<ACharacter>())
	{
		ControlledPawn->Jump();
		
	}
}

void AVoidPlayerController::StopJump()
{
	if (ACharacter* ControlledPawn = GetPawn<ACharacter>())
	{
		ControlledPawn->StopJumping();
		
	}
}

void AVoidPlayerController::FastFallPressed()
{
	if (ACharacter* ControlledPawn = GetPawn<ACharacter>())
	{
		if (!ControlledPawn->GetCharacterMovement()->IsMovingOnGround())
		{
			ControlledPawn->GetCharacterMovement()->GravityScale = FastFallGravityScale;
		}
	}
}

void AVoidPlayerController::FastFallReleased()
{
	if (ACharacter* ControlledPawn = GetPawn<ACharacter>())
	{
		ControlledPawn->GetCharacterMovement()->GravityScale = 1.f;
	}
}
