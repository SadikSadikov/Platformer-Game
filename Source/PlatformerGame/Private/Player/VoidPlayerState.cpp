// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VoidPlayerState.h"

#include "AbilitySystem/VoidAbilitySystemComponent.h"
#include "AbilitySystem/VoidAttributeSet.h"

AVoidPlayerState::AVoidPlayerState()
{
	SetNetUpdateFrequency(100.f);
	
	AbilitySystemComponent = CreateDefaultSubobject<UVoidAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UVoidAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AVoidPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AVoidPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
