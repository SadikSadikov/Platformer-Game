// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/VoidAbilitySystemComponent.h"

#include "VoidGameplayTags.h"

void UVoidAbilitySystemComponent::AbilityActorInfoSet()
{

	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UVoidAbilitySystemComponent::EffectApplied);

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("MaxMana [%s]"), *FVoidGameplayTags::Get().Attributes_Secondary_MaxHealth.ToString()));

}

void UVoidAbilitySystemComponent::AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>> StartupAbilities)
{
	for (TSubclassOf<UGameplayAbility> Ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UVoidAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, TEXT("EffectApplied"));
}
