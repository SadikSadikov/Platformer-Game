// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "VoidPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMERGAME_API AVoidPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:

	AVoidPlayerCameraManager();

	/** sets new value of FixedCameraOffsetZ */
	UFUNCTION(BlueprintCallable, Category = "Game|Player")
	void SetFixedCameraOffsetZ(float InOffset);

	/** sets new value of CurrentZoomAlpha <0, 1> */
	UFUNCTION(BlueprintCallable, Category="Game|Player")
	void SetCameraZoom(float ZoomAlpha);

	/** gets current value of CurrentZoomAlpha */
	UFUNCTION(BlueprintCallable, Category="Game|Player")
	float GetCameraZoom() const;

protected:
	// APlayerCameraManager interface

	/** handle camera updates */
	virtual void UpdateViewTargetInternal(FTViewTarget& OutVT, float DeltaTime) override;

	// End of APlayerCameraManager interface

	/** calculates camera Z axis offset dependent on player pawn movement */
	float CalcCameraOffsetZ(float DeltaTime);

	//** Calculates Camera X axis offset dependent on player movement ( Left or Right ) */
	float CalcCameraOffsetX(float DeltaTime);

private:

	/** Camera X axis offset from Player  */
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float CameraOffsetX;
	
	float DesiredCameraOffsetX;
	
	float CurrentCameraOffsetX;

	/** Interpolation speed for changing Camera X axis Offset */
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float CameraOffsetInterpSpeedX;
	

	/** fixed maximal camera distance from player pawn ; used for zoom */
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	FVector MaxCameraZoomOffset;

	/** fixed minimal camera distance from player pawn ; used for zoom */
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	FVector MinCameraZoomOffset;

	/** interpolation speed for changing camera Z axis offset */
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float CameraOffsetInterpSpeedZ;

	/** fixed camera Z axis offset from player pawn */
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float FixedCameraOffsetZ;

	/** Fixed rotation of the camera relative to player pawn  */
	FRotator CameraFixedRotation;

	/** current value of zoom <0, 1> (0 means MinCameraZoomOffset will be used, 1 means MaxCameraZoomOffset will) */
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float CurrentZoomAlpha;

	/** currently used camera Z axis offset */
	float CurrentCameraOffsetZ;

	/** Z axis offset camera is supposed to achieve */
	float DesiredCameraOffsetZ;	
	
};


