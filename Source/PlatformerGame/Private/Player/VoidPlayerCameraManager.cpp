// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VoidPlayerCameraManager.h"
#include "Character/VoidPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

AVoidPlayerCameraManager::AVoidPlayerCameraManager()
{	
	MinCameraZoomOffset = FVector(0.f, 600.0f, 0.0f);
	MaxCameraZoomOffset = MinCameraZoomOffset * 4.0f;
	CurrentZoomAlpha = 0.1f;

	DesiredCameraOffsetZ = 0.0f;
	CurrentCameraOffsetZ = 0.0f;
	CameraOffsetInterpSpeedZ = 5.0f;

	CameraFixedRotation = FRotator(0.0f, -90.0f, 0.0f);
	FixedCameraOffsetZ = 130.0f;

	CameraOffsetX = 240.f;
	DesiredCameraOffsetX = 0.f;
	CurrentCameraOffsetX = 0.f;
	CameraOffsetInterpSpeedX = 2.f;
}

void AVoidPlayerCameraManager::UpdateViewTargetInternal(FTViewTarget& OutVT, float DeltaTime)
{
	FVector ViewLoc;
	FRotator ViewRot;
	OutVT.Target->GetActorEyesViewPoint(ViewLoc, ViewRot);
	ViewLoc.X += CalcCameraOffsetX(DeltaTime); // Camera offset X
	ViewLoc.Z = CalcCameraOffsetZ(DeltaTime);
	ViewLoc.Z += FixedCameraOffsetZ;

	FVector CurrentCameraZoomOffset = MinCameraZoomOffset + CurrentZoomAlpha * (MaxCameraZoomOffset - MinCameraZoomOffset);
	OutVT.POV.Location = ViewLoc + CurrentCameraZoomOffset;
	OutVT.POV.Rotation = CameraFixedRotation;
}

void AVoidPlayerCameraManager::SetFixedCameraOffsetZ(float InOffset)
{
	FixedCameraOffsetZ = InOffset;
}

void AVoidPlayerCameraManager::SetCameraZoom(float ZoomAlpha)
{
	CurrentZoomAlpha = FMath::Clamp(ZoomAlpha, 0.0f, 1.0f);
}

float AVoidPlayerCameraManager::GetCameraZoom() const
{
	return CurrentZoomAlpha;
}

float AVoidPlayerCameraManager::CalcCameraOffsetZ(float DeltaTime)
{
	AVoidPlayer* MyPawn = PCOwner ? Cast<AVoidPlayer>(PCOwner->GetPawn()) : nullptr;
	if (MyPawn)
	{
		float LocZ = MyPawn->GetActorLocation().Z;
		if (MyPawn->GetCharacterMovement() && MyPawn->GetCharacterMovement()->IsFalling())
		{
			if (LocZ < DesiredCameraOffsetZ)
			{
				DesiredCameraOffsetZ = LocZ;
			}
			else if (LocZ > DesiredCameraOffsetZ + MyPawn->GetCameraHeightChangeThreshold())
			{
				DesiredCameraOffsetZ = LocZ;
			}
		}
		else
		{
			DesiredCameraOffsetZ = LocZ;
		}
	}

	if (CurrentCameraOffsetZ != DesiredCameraOffsetZ)
	{
		CurrentCameraOffsetZ = FMath::FInterpTo(CurrentCameraOffsetZ, DesiredCameraOffsetZ, DeltaTime, CameraOffsetInterpSpeedZ);
	}

	return CurrentCameraOffsetZ;
}


float AVoidPlayerCameraManager::CalcCameraOffsetX(float DeltaTime)
{

	AVoidPlayer* MyPawn = PCOwner ? Cast<AVoidPlayer>(PCOwner->GetPawn()) : nullptr;
	if (MyPawn)
	{
		float ForwardX = MyPawn->GetActorForwardVector().X;
		
		DesiredCameraOffsetX = CameraOffsetX * ForwardX;
		
	}
	

	if (CurrentCameraOffsetX != DesiredCameraOffsetX)
	{
		CurrentCameraOffsetX = FMath::FInterpTo(CurrentCameraOffsetX, DesiredCameraOffsetX, DeltaTime, CameraOffsetInterpSpeedX);
	}
	
	return CurrentCameraOffsetX;
}


