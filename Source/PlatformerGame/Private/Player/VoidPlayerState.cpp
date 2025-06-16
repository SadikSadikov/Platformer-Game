// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VoidPlayerState.h"

#include "AbilitySystemComponent.h"

AVoidPlayerState::AVoidPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");

	AttributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AVoidPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AVoidPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
