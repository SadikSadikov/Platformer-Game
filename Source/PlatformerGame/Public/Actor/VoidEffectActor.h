// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoidEffectActor.generated.h"

class UGameplayEffect;
class USphereComponent;

UCLASS()
class PLATFORMERGAME_API AVoidEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AVoidEffectActor();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> EffectToApply);


	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;





};
