// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VoidEnemy.h"
#include "AbilitySystemComponent.h"
#include "AI/VoidAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


AVoidEnemy::AVoidEnemy(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	Tags.Add(FName("Enemy"));

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 360.f, 0);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MaxAcceleration = 1024.f;
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UAttributeSet>("AttributeSet");
}

void AVoidEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	VoidAIController = Cast<AVoidAIController>(NewController);
	VoidAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->GetBlackboardAsset());
	VoidAIController->RunBehaviorTree(BehaviorTree);
	
}

void AVoidEnemy::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
