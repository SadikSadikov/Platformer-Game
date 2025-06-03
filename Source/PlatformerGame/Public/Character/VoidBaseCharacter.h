// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VoidBaseCharacter.generated.h"

UCLASS(Abstract)
class PLATFORMERGAME_API AVoidBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	AVoidBaseCharacter();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;
	

};
