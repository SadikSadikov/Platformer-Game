// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/VoidEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/VoidAttributeSet.h"
#include "Components/SphereComponent.h"

AVoidEffectActor::AVoidEffectActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	Sphere->SetupAttachment(GetRootComponent());

}


void AVoidEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AVoidEffectActor::OnSphereBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AVoidEffectActor::OnSphereEndOverlap);
}

void AVoidEffectActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Change this to apply a Gameplay Effect. For now using const_cast as a hack?
	if (IAbilitySystemInterface* ASInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UVoidAttributeSet* VoidAS = Cast<UVoidAttributeSet>(ASInterface->GetAbilitySystemComponent()->GetAttributeSet(UVoidAttributeSet::StaticClass()));
		UVoidAttributeSet* MutableVoidAS = const_cast<UVoidAttributeSet*>(VoidAS);
		MutableVoidAS->SetHealth(VoidAS->GetHealth() + 25.f);
		Destroy();
	}
}

void AVoidEffectActor::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}



