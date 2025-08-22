// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *
 * VoidGameplayTags
 *
 * Singleton containing native Gameplay Tags
 * 
 */

struct FVoidGameplayTags
{

public:
	static const FVoidGameplayTags& Get() { return GameplayTags;}

	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Secondary_MaxHealth;

	FGameplayTag Attributes_Secondary_MaxMana;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;

protected:

private:
	static FVoidGameplayTags GameplayTags;
	
};
