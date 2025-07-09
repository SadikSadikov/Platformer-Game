// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/VoidBaseCharacter.h"
#include "VoidEnemy.generated.h"

class UBehaviorTree;
class AVoidAIController;
/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API AVoidEnemy : public AVoidBaseCharacter
{
	GENERATED_BODY()

public:
	
	AVoidEnemy(const FObjectInitializer& ObjectInitializer);

	virtual void PossessedBy(AController* NewController) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<AVoidAIController> VoidAIController;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	
};
