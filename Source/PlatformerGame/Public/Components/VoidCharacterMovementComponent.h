// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "VoidCharacterMovementComponent.generated.h"


UCLASS()
class PLATFORMERGAME_API UVoidCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()


public:

	UVoidCharacterMovementComponent();

	// Make sure do you not already jumped
	void BeginCayoteTime();

	bool bCanCayoteTime = false;

	UFUNCTION(BlueprintCallable)
	void BeginDash();


protected:

	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;

	virtual void ProcessLanded(const FHitResult& Hit, float remainingTime, int32 Iterations) override;

	virtual void BeginPlay() override;

private:

	// Cayote Time
	
	FTimerHandle CayoteTimeTimerHandle;

	void DisableCayoteTime();

	UPROPERTY(EditDefaultsOnly, Category = "Cayote Time")
	float CayoteTimeRate = 0.2;
	

	// Dash

	void DashOverTime();

	void GetFurthestValidDashLocation(const FVector& Start, const FVector& End, FVector& FurthestValidLocation);

	void CalculateDashTargetLocation(FVector& TargetLocation);

	UFUNCTION()
	void UpdateDashTargetLocation(float DashValue);

	void IsValidDashTargetLocation(const FVector& Location,  const TArray<FHitResult>& Hit, bool& IsValid );

	UPROPERTY(VisibleAnywhere, Category = "Dash")
	TObjectPtr<UTimelineComponent> DashTimeline;

	FOnTimelineFloat DashTrack;

	UPROPERTY(EditDefaultsOnly, Category = "Dash")
	TObjectPtr<UCurveFloat> DashCurve;
	
	UPROPERTY(EditDefaultsOnly, Category = "Dash")
	float DashDuration = 0.3f;

	UPROPERTY(EditDefaultsOnly, Category = "Dash")
	float DashMaxDistance = 600.f;

	FVector DashTargetLocation;
	

	

	
	
	
};


