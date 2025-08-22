// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "VoidAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API UVoidAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	void AbilityActorInfoSet();

	void AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>> StartupAbilities);

protected:

private:

	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	
	
};
