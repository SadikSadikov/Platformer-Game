#include "PlatformerGame/Public/Character/VoidBaseCharacter.h"


AVoidBaseCharacter::AVoidBaseCharacter(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AVoidBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVoidBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

