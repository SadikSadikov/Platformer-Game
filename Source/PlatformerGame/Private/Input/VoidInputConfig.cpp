// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/VoidInputConfig.h"

const UInputAction* UVoidInputConfig::FindInputActionByTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FVoidInputAction& VoidInputAction : AbilityInputActions)
	{
		if (VoidInputAction.InputAction && VoidInputAction.GameplayTag == InputTag)
		{
			return VoidInputAction.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can`t find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
