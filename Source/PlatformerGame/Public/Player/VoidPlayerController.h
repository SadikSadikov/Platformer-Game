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


private:


	
};


