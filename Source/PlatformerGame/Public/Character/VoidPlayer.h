// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/VoidBaseCharacter.h"
#include "VoidPlayer.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

UCLASS()
class PLATFORMERGAME_API AVoidPlayer : public AVoidBaseCharacter
{
	GENERATED_BODY()

public:

	AVoidPlayer(const FObjectInitializer& ObjectInitializer);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Landed(const FHitResult& Hit) override;

	virtual void CheckJumpInput(float DeltaTime) override;
	

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;
	

protected:
	
	virtual void BeginPlay() override;

private:

	void InitAbilityActorInfo();

	// Input

	void Move(const FInputActionValue& ActionValue);

	void StartJump();

	void StopJump();

	void FastFallPressed();

	void FastFallReleased();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> MainContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> FastFallAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float FastFallGravityScale = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float CustomGravityScale = 3;

	bool bIsJumped = false;

	bool bCanFirstJump = true;

	bool bCanDoubleJump = false;


	
};
