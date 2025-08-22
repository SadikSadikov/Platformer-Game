// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "VoidInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FVoidInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag GameplayTag = FGameplayTag();
	
};

UCLASS()
class PLATFORMERGAME_API UVoidInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	const UInputAction* FindInputActionByTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVoidInputAction> AbilityInputActions;
	
};
