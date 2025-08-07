// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/VoidAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UVoidAttributeSet::UVoidAttributeSet()
{
}

void UVoidAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UVoidAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UVoidAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)

	DOREPLIFETIME_CONDITION_NOTIFY(UVoidAttributeSet, Mana, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UVoidAttributeSet, MaxMana, COND_None, REPNOTIFY_Always)
}

void UVoidAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UVoidAttributeSet, Health, OldHealth);
}

void UVoidAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UVoidAttributeSet, MaxHealth, OldMaxHealth);
}

void UVoidAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UVoidAttributeSet, Mana, OldMana);
}

void UVoidAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UVoidAttributeSet, MaxMana, OldMaxMana);
}
