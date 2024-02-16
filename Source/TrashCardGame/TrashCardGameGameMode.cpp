// Copyright Epic Games, Inc. All Rights Reserved.

#include "TrashCardGameGameMode.h"
#include "TrashCardGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATrashCardGameGameMode::ATrashCardGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
