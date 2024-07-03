// Fill out your copyright notice in the Description page of Project Settings.


#include "AICardPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TrashGameState.h" // also includes EGameState
#include "BasePile.h"
#include "BaseCard.h"
#include "AICardPlayer.h"
#include "Card.h"
#include "CardLayout.h"

// make moves for AI if the game state becomes "AI's Turn"

// Sets default values
AAICardPlayerController::AAICardPlayerController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAICardPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// set game state object
	GStateObj = Cast<ATrashGameState>(UGameplayStatics::GetGameState(GetWorld()));

	UE_LOG(LogTemp, Error, TEXT("The state of the game from the AI's perspective is: %i"), static_cast<uint8>(GStateObj->GetState()));
	// PlayAITurn();
	
}

// Called every frame
void AAICardPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AAICardPlayerController::IsComputersTurn()
{
	if (GStateObj)
	{
		if (GStateObj->GetState() != EGameState::computerTurn)
		{
			UE_LOG(LogTemp, Display, TEXT("Not the computer's turn"));
			return false;
		}
		else 
		{
			return true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GStateObj not set"));
		return false;
	}
}

void AAICardPlayerController::DrawCard()
{
	if (player)
	{
		// TODO: should determine which pile to draw from here
		if (GStateObj->DiscardPileReference->cards.Num() > 0)
		{
			UCard* topCard {GStateObj->DiscardPileReference->cards.Last()};
			if 
			(
				topCard->Rank == 11 || 
				(player->Layout->cards.Num() >= topCard->Rank && !player->Layout->cards[(topCard->Rank) - 1]->faceUp)
			)
			{
				player->CardInHand = GStateObj->DiscardPileReference->AIDrawCard();
				return;
			}
		}

		if (GStateObj->StockPileReference)
		{
			player->CardInHand = GStateObj->StockPileReference->AIDrawCard();
		}
	}
}

void AAICardPlayerController::PlayAITurn()
{
	if (IsComputersTurn())
	{
		UE_LOG(LogTemp, Display, TEXT("Playing AI's turn..."));

		if (GStateObj->StockPileReference)
		{
			if (player)
			{
				player->CardInHand = GStateObj->StockPileReference->AIDrawCard();
			}
		}

		if (player->CardInHand)
		{
			if (player->Layout)
			{
				PlaceCardsInLayout();
			}
		}

		

		// UE_LOG(LogTemp, Error, TEXT("Current state of the game before ending turn is: %i"), static_cast<uint8>(GStateObj->GetState()));
		// GStateObj->EndTurn();
		// UE_LOG(LogTemp, Error, TEXT("Current state of the game has changed to: %i"), static_cast<uint8>(GStateObj->GetState()));
	}
}

void AAICardPlayerController::PlaceCardsInLayout()
{
	// walk the layout to find the cards that are needed
	// player->Layout->cards

	// 1. If wild place the lowest number that isn't face up
	// 2. If not wild check if layout position matching rank is face up.
		// If it is face up, discard
		// If it is not face up, swap cards and repeat above steps

	// Cache cards for this current turn for efficiency
	TArray<ABaseCard*>& CurTurnCards {player->Layout->cards};

	for (ABaseCard* card : CurTurnCards)
	{
		const UCard* cardObj {card->GetCard()};

		if (card->faceUp)
		{
			if (!(cardObj->IsWild))
			{
				CurTurnCards.Remove(card);
			}
		}
	}

	

	// bool TurnOver {false};
	// do 
	// {
	// 	if (CurTurnCards.Num() > 0)
	// 	{
	// 		if (player->CardInHand->IsWild)
	// 		{
	// 			// delay a second or two
	// 			// TODO: make this random instead of hardcoding 0
	// 			CurTurnCards[0]->SwapCardInHand<AAICardPlayer>(player);
	// 			CurTurnCards.RemoveAt(0);
	// 			UE_LOG(LogTemp, Display, TEXT("AI is placing wild card..."));
	// 		}
	// 		else
	// 		{
	// 			// if rank of card in hand is > than the num cards in layout, return (already know it isn't a wild because this is the else)
	// 			if (player->CardInHand->Rank > player->Layout->GetLayoutCount())
	// 			{
	// 				TurnOver = true;
	// 				continue;
	// 			}

	// 			// get the card in the layout that matches the rank of the card in hand
	// 			int32 LayoutIndex {(player->CardInHand->Rank)-1};
	// 			ABaseCard* CardToReplace {player->Layout->cards[LayoutIndex]};

	// 			if (CardToReplace && (!CardToReplace->faceUp || CardToReplace->GetCard()->IsWild))
	// 			{
	// 				// delay a second or two
	// 				CurTurnCards[LayoutIndex]->SwapCardInHand<AAICardPlayer>(player);
	// 				CurTurnCards.RemoveAt(LayoutIndex);
	// 				UE_LOG(LogTemp, Display, TEXT("AI is placing rank card..."));
	// 			}
	// 			else 
	// 			{
	// 				TurnOver = true;
	// 			}
	// 		}
	// 	}
		
	// 	TurnOver = true;
	// } while (!TurnOver);

	// Discard();
}

void AAICardPlayerController::Discard()
{
	if (player->CardInHand)
	{
		GStateObj->DiscardPileReference->AIDiscardCard(player->CardInHand);
		player->CardInHand = nullptr;
	}

	GStateObj->EndTurn();
}
