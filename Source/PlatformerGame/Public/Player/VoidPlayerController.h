// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VoidPlayerController.generated.h"


struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class PLATFORMERGAME_API AVoidPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AVoidPlayerController();

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> MainContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> FastFallAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float FastFallGravityScale = 4;;

	void Move(const FInputActionValue& ActionValue);

	void StartJump();

	void StopJump();

	void FastFallPressed();

	void FastFallReleased();
	
};


