// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VoidCharacterMovementComponent.h"

#include "GameFramework/Character.h"

void UVoidCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode,
                                                            uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);

	if (MovementMode == MOVE_Falling)
	{
		bCanCayoteTime = true;
	
		GetWorld()->GetTimerManager().SetTimer(CayoteTimeTimerHandle, this, &UVoidCharacterMovementComponent::DisableCayoteTime, CayoteTimeRate, false);
	}

	
}

void UVoidCharacterMovementComponent::ProcessLanded(const FHitResult& Hit, float remainingTime, int32 Iterations)
{
	Super::ProcessLanded(Hit, remainingTime, Iterations);
	
	DisableCayoteTime();
	
}

void UVoidCharacterMovementComponent::DisableCayoteTime()
{
	bCanCayoteTime = false;

	GetWorld()->GetTimerManager().ClearTimer(CayoteTimeTimerHandle);
}

void UVoidCharacterMovementComponent::StartCayoteTime()
{
	if (bCanCayoteTime)
	{
		GetCharacterOwner()->LaunchCharacter(FVector(0.f, 0.f,
				CharacterOwner->JumpMaxHoldTime != 0.f ? JumpZVelocityOverride : JumpZVelocity), false, false);
	}
}
