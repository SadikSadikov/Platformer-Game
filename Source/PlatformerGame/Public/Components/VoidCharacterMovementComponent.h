// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "VoidCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API UVoidCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()


public:

	// Make sure do you not already jumped
	void StartCayoteTime();


protected:

	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;

	virtual void ProcessLanded(const FHitResult& Hit, float remainingTime, int32 Iterations) override;

private:

	// Cayote Time
	
	FTimerHandle CayoteTimeTimerHandle;

	void DisableCayoteTime();

	UPROPERTY(EditDefaultsOnly, Category = "Cayote Time")
	float CayoteTimeRate = 0.2;

	bool bCanCayoteTime = false;

	// Used only for Cayote Time not affected real JumpZVelocity
	UPROPERTY(EditDefaultsOnly, Category = "Cayote Time")
	float JumpZVelocityOverride = 1000.f;

	
	
	
};
