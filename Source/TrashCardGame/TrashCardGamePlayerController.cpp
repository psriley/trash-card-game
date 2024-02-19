// Copyright Epic Games, Inc. All Rights Reserved.


#include "TrashCardGamePlayerController.h"
#include "EnhancedInputSubsystems.h"

void ATrashCardGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}

	// unlock cursor
	SetShowMouseCursor(true);
}