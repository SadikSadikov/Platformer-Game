// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/VoidAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AVoidAIController::AVoidAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
	check(Blackboard);

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
	check(BehaviorTreeComponent);
}
