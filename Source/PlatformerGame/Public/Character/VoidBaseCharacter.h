// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "VoidBaseCharacter.generated.h"

class UGameplayAbility;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class PLATFORMERGAME_API AVoidBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	AVoidBaseCharacter(const FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const;

protected:
	
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo();

	virtual void AddCharacterAbilities();

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

public:
	
	virtual void Tick(float DeltaTime) override;
	

};
