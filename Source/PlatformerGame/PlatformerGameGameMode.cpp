// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatformerGameGameMode.h"
#include "PlatformerGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

APlatformerGameGameMode::APlatformerGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
