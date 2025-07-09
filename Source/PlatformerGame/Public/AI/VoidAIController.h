// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "VoidAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API AVoidAIController : public AAIController
{
	GENERATED_BODY()

public:
	AVoidAIController();

protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	
};
