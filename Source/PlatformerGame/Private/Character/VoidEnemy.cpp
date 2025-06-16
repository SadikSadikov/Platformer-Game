// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VoidEnemy.h"
#include "AbilitySystemComponent.h"


AVoidEnemy::AVoidEnemy(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");

	AttributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");
}
