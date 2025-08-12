// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/VoidPlayer.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/VoidCharacterMovementComponent.h"
#include "Player/VoidPlayerState.h"

AVoidPlayer::AVoidPlayer(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer.SetDefaultSubobjectClass<UVoidCharacterMovementComponent>(CharacterMovementComponentName))
{
	Tags.Add(FName("Player"));
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.3f;
	GetCharacterMovement()->MaxAcceleration = 2500.f;
	JumpMaxHoldTime = 0.4f;
	JumpMaxCount = 2;
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
	bCanDoubleJump = false;
	bCanFirstJump = true;
}

void AVoidPlayer::CheckJumpInput(float DeltaTime)
{
	Super::CheckJumpInput(DeltaTime);

	if (bPressedJump)
	{
		bIsJumped = true;
	}
}



void AVoidPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Ability Actor Info for the Server
	InitAbilityActorInfo();
}

void AVoidPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init Ability Actor Info for the Client
	InitAbilityActorInfo();
}

float AVoidPlayer::GetCameraHeightChangeThreshold() const
{
	return CameraHeightChangeThreshold;
}

void AVoidPlayer::InitAbilityActorInfo()
{
	AVoidPlayerState* VoidPlayerState = GetPlayerState<AVoidPlayerState>();
	check(VoidPlayerState);
	
	VoidPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(VoidPlayerState, this);
	AbilitySystemComponent = VoidPlayerState->GetAbilitySystemComponent();
	AttributeSet = VoidPlayerState->GetAttributeSet();
	
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
	
	if (UVoidCharacterMovementComponent* VoidMovComp = Cast<UVoidCharacterMovementComponent>(GetCharacterMovement()))
	{
		if (VoidMovComp->bCanCayoteTime && !bIsJumped)
		{
			VoidMovComp->BeginCayoteTime();
		}
		else if (!bIsJumped && bCanFirstJump && !VoidMovComp->IsFalling())
		{
			bCanFirstJump = false;
			bCanDoubleJump = true;
			Jump();
		}
		else if (bCanDoubleJump)
		{
			Jump();
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
	GetCharacterMovement()->GravityScale = CustomGravityScale;
}

