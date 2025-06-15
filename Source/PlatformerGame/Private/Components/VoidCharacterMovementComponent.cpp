// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VoidCharacterMovementComponent.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

UVoidCharacterMovementComponent::UVoidCharacterMovementComponent()
{
	DashTimeline = CreateDefaultSubobject<UTimelineComponent>("DashTimelineComponent");
}

void UVoidCharacterMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode,
                                                            uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);

	if (MovementMode == MOVE_Falling)
	{
		bCanCayoteTime = true;
	
		GetWorld()->GetTimerManager().SetTimer(CayoteTimeTimerHandle, this, &UVoidCharacterMovementComponent::DisableCayoteTime, CayoteTimeRate, false);
	}

	
}

void UVoidCharacterMovementComponent::ProcessLanded(const FHitResult& Hit, float remainingTime, int32 Iterations)
{
	Super::ProcessLanded(Hit, remainingTime, Iterations);
	
	DisableCayoteTime();
	
}

void UVoidCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	DashTrack.BindDynamic(this, &UVoidCharacterMovementComponent::UpdateDashTargetLocation);
}

void UVoidCharacterMovementComponent::DisableCayoteTime()
{
	bCanCayoteTime = false;

	GetWorld()->GetTimerManager().ClearTimer(CayoteTimeTimerHandle);
}

void UVoidCharacterMovementComponent::UpdateDashTargetLocation(float DashValue)
{
	FVector DashStartLocation = GetCharacterOwner()->GetActorLocation();

	 GetCharacterOwner()->SetActorLocation(FMath::Lerp(DashStartLocation, DashTargetLocation, DashValue));
	
}

void UVoidCharacterMovementComponent::IsValidDashTargetLocation(const FVector& Location, const TArray<FHitResult>& Hit,
	bool& IsValid)
{
	FVector UnderCharacter = Location + FVector(0.f, 0.f, -500.f);

	FHitResult DashHit;
	bool bIsHit =  UKismetSystemLibrary::LineTraceSingle(GetCharacterOwner(), Location, UnderCharacter,
		TraceTypeQuery1, false, TArray<AActor*>(), EDrawDebugTrace::None, DashHit, true);

	if (bIsHit)
	{
		if (Hit.IsEmpty())
		{
			IsValid = true;
			
		}
		else
		{
			for (FHitResult Result : Hit)
			{
				if (Result.GetComponent()->GetCollisionResponseToChannel(ECC_Pawn) == ECR_Block)
				{
					IsValid = false;
					return;
				}
			}
			
			IsValid = true;
		}
	}
	else
	{
		IsValid = false;
	}
}

void UVoidCharacterMovementComponent::DashOverTime()
{
	if (DashTimeline && DashCurve)
	{
		float CalcPlayRate = 1.f / DashDuration;
		DashTimeline->SetPlayRate(CalcPlayRate);
		DashTimeline->AddInterpFloat(DashCurve, DashTrack);
		DashTimeline->PlayFromStart();
	}
	
}

void UVoidCharacterMovementComponent::GetFurthestValidDashLocation(const FVector& Start, const FVector& End,
	FVector& FurthestValidLocation)
{

	FVector Direction = (End - Start).GetSafeNormal();

	float CapsuleDiameter = GetCharacterOwner()->GetCapsuleComponent()->GetUnscaledCapsuleRadius() * 2.f;

	int32 CapsuleCount = (Start - End).Length() / CapsuleDiameter;

	FVector CurrentCapsuleLocation;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Vehicle));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Destructible));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

	TArray<FHitResult> HitResults;

	for (int32 i = 0; i < CapsuleCount; i++)
	{
		CapsuleCount = CapsuleCount - i;

		CurrentCapsuleLocation = Start + (CapsuleCount * Direction * CapsuleDiameter);

		
		UKismetSystemLibrary::CapsuleTraceMultiForObjects(GetCharacterOwner(), CurrentCapsuleLocation,
			CurrentCapsuleLocation, GetCharacterOwner()->GetCapsuleComponent()->GetUnscaledCapsuleRadius(),
			GetCharacterOwner()->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight(), ObjectTypes, false, TArray<AActor*>(),
			EDrawDebugTrace::ForDuration, HitResults, true);

		bool IsValid;
		IsValidDashTargetLocation(CurrentCapsuleLocation, HitResults, IsValid);

		if (IsValid)
		{
			FurthestValidLocation = CurrentCapsuleLocation;
			return;
		}

		
	}

	FurthestValidLocation = Start;

	
	
}

void UVoidCharacterMovementComponent::CalculateDashTargetLocation(FVector& TargetLocation)
{
	FVector Direction = GetPawnOwner()->GetLastMovementInputVector() == FVector::ZeroVector ? GetCharacterOwner()->GetActorForwardVector() : GetPawnOwner()->GetLastMovementInputVector();

	TargetLocation = (Direction * DashMaxDistance) + GetCharacterOwner()->GetActorLocation();
	
}



void UVoidCharacterMovementComponent::BeginCayoteTime()
{

	GetCharacterOwner()->Jump();
}

void UVoidCharacterMovementComponent::BeginDash()
{
	FVector ActorLocation = GetCharacterOwner()->GetActorLocation();

	FVector TargetLocation;
	CalculateDashTargetLocation(TargetLocation);
	
	GetFurthestValidDashLocation(ActorLocation, TargetLocation,DashTargetLocation);

	DashOverTime();
	
}
