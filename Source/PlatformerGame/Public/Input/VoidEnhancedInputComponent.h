// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "VoidInputConfig.h"
#include "VoidEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API UVoidEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UVoidInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
	
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UVoidEnhancedInputComponent::BindAbilityActions(const UVoidInputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{

	check(InputConfig);

	for (const FVoidInputAction& InputAction : InputConfig->AbilityInputActions)
	{
		if (InputAction.InputAction && InputAction.GameplayTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(InputAction.InputAction, ETriggerEvent::Started, Object, PressedFunc, InputAction.GameplayTag);
			}

			if (ReleasedFunc)
			{
				BindAction(InputAction.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, InputAction.GameplayTag);
			}

			if (HeldFunc)
			{
				BindAction(InputAction.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, InputAction.GameplayTag);
			}
		}
	}
}
