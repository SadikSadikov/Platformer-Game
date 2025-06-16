#include "PlatformerGame/Public/Character/VoidBaseCharacter.h"


AVoidBaseCharacter::AVoidBaseCharacter(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

UAbilitySystemComponent* AVoidBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AVoidBaseCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void AVoidBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVoidBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

