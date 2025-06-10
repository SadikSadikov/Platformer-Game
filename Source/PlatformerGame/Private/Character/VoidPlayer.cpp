// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VoidPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/VoidCharacterMovementComponent.h"

AVoidPlayer::AVoidPlayer(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer.SetDefaultSubobjectClass<UVoidCharacterMovementComponent>(CharacterMovementComponentName))
{
	DefaultGravityScale = GetCharacterMovement()->GravityScale;
}

void AVoidPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AVoidPlayer::Move);
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AVoidPlayer::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AVoidPlayer::StopJump);

		EnhancedInputComponent->BindAction(FastFallAction, ETriggerEvent::Started, this, &AVoidPlayer::FastFallPressed);
		EnhancedInputComponent->BindAction(FastFallAction, ETriggerEvent::Completed, this, &AVoidPlayer::FastFallReleased);
	}
}

void AVoidPlayer::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	bIsJumped = false;
}

void AVoidPlayer::CheckJumpInput(float DeltaTime)
{
	Super::CheckJumpInput(DeltaTime);

	if (bPressedJump)
	{
		bIsJumped = true;
	}
}

void AVoidPlayer::BeginPlay()
{
	Super::BeginPlay();

	check(MainContext)

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			LocalPlayerSubsystem->AddMappingContext(MainContext, 0);
		}
	}
	
}

void AVoidPlayer::Move(const FInputActionValue& ActionValue)
{

	const float Value = ActionValue.Get<float>();

	FVector RightVector = FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X);

	AddMovementInput(RightVector, Value);
}

void AVoidPlayer::StartJump()
{
	Jump();
	if (UVoidCharacterMovementComponent* VoidMovComp = Cast<UVoidCharacterMovementComponent>(GetCharacterMovement()))
	{
		if (!bIsJumped)
		{
			VoidMovComp->StartCayoteTime();
		}
			
			
	}
}

void AVoidPlayer::StopJump()
{
	StopJumping();
}

void AVoidPlayer::FastFallPressed()
{
	if (!GetCharacterMovement()->IsMovingOnGround())
	{
		GetCharacterMovement()->GravityScale = FastFallGravityScale;
	}
}

void AVoidPlayer::FastFallReleased()
{
	GetCharacterMovement()->GravityScale = DefaultGravityScale;
}

