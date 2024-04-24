// Copyright Epic Games, Inc. All Rights Reserved.


#include "TrashCardGamePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "CardPlayerPlayerState.h"
#include "BaseCardPlayer.h"
#include "CardLayout.h"
#include "Card.h"

ATrashCardGamePlayerController::ATrashCardGamePlayerController()
{

}

ACardPlayerPlayerState* ATrashCardGamePlayerController::GetPlayerState() const { return Cast<ACardPlayerPlayerState>(PlayerState); }

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

	PlayerPawn = GetPawn<ABaseCardPlayer>();
}

int32 ATrashCardGamePlayerController::GetNumberMoves()
{
	if (PlayerPawn)
	{
		ACardLayout* PlayerLayout { PlayerPawn->Layout };
		UCard* CurrentCard = { GetPlayerState()->CardInHand };

		if (CurrentCard && !(CurrentCard->IsWild)) 
		{
			// TODO: check layout for current card place
			return 1;
		}
		else 
		{
			return 0;
		}
	}
	else 
	{
		return 0;
		UE_LOG(LogTemp, Error, TEXT("Controller can't find player pawn"));	
	}
}
