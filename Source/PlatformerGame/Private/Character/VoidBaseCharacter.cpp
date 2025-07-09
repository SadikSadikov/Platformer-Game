#include "PlatformerGame/Public/Character/VoidBaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"


AVoidBaseCharacter::AVoidBaseCharacter(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.f, 1.f, 0.f));
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

