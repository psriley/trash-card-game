// Copyright Epic Games, Inc. All Rights Reserved.

#include "TrashCardGameGameMode.h"
#include "TrashCardGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "CardDeck.h"
#include "BaseCardPlayer.h"
#include "CardLayout.h"
#include "BaseCard.h"
#include "Card.h"
#include "BasePile.h"
#include "TrashGameState.h"
#include "Algo/Sort.h"
#include "LayoutComponent.h"

ATrashCardGameGameMode::ATrashCardGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// cardDeck = CreateDefaultSubobject<UCardDeck>(TEXT("Standard 52 Card Deck"));
}

void ATrashCardGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Ensure the controller is properly set in BeginPlay as well
    controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    // Print the result of controller to debug
    if (controller)
    {
        UE_LOG(LogTemp, Warning, TEXT("Controller is valid: %s"), *controller->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Controller is NULL"));
    }
}

void ATrashCardGameGameMode::InitializeCards()
{
	cardDeckInstance = UCardDeck::InitializeDeck();
	if (cardDeckInstance)
	{
		if (controller)
		{
			setupPiles(); // sets reference properties on TrashGameState and calls startHand()
		}
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Card deck instance not found (probably has not been initialized)"));
	}
}

void ATrashCardGameGameMode::startHand()
{
	UE_LOG(LogTemp, Warning, TEXT("Starting hand"));

	setupLayouts();
}

void ATrashCardGameGameMode::setupPiles()
{
	stockPile = Cast<ATrashGameState>(GameState)->StockPileReference;
	discardPile = Cast<ATrashGameState>(GameState)->DiscardPileReference;

	// Set "cards" property on both piles
	if (stockPile && discardPile)
	{
		stockPile->cards = cardDeckInstance->cardDeck;
		stockPile->isDiscardPile = false;

		discardPile->isDiscardPile = true;

		startHand();
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Stock pile and/or discard pile not set in details (null)"));
	}
	// ABaseCardPlayer* playerPawn {Cast<ABaseCardPlayer>(controller->GetPawn())};
	// if (playerPawn)
	// {
	// 	ACardLayout* playerLayout = playerPawn->Layout;

	// 	if (playerLayout)
	// 	{
	// 		FVector LayoutPosition {playerLayout->GetActorLocation()};
	// 		FVector OffsetPosition {FVector(0, -10, 5)};

	// 		// Spawn cards into layout (flipped)
	// 		ABasePile* DiscardPile = GetWorld()->SpawnActor<ABasePile>(ABasePile::StaticClass(), LayoutPosition + OffsetPosition, FRotator(0,0,0));

	// 		OffsetPosition = FVector(0, 10, 5);
	// 		ABasePile* StockPile = GetWorld()->SpawnActor<ABasePile>(ABasePile::StaticClass(), LayoutPosition + OffsetPosition, FRotator(0,0,0));
	// 	}
	// }
}

void ATrashCardGameGameMode::setupLayouts()
{
	// Setup the player's layout for the start of the hand
	controller->PlayerState;
	ABaseCardPlayer* playerPawn {Cast<ABaseCardPlayer>(controller->GetPawn())};
	if (playerPawn)
	{
		ACardLayout* playerLayout = playerPawn->Layout;
		
		if (playerLayout)
		{
			// Get the RootComponent of the playerLayout actor
			USceneComponent* layoutRoot = playerLayout->GetRootComponent();

			if (layoutRoot)
			{
				TArray<ULayoutComponent*> CardArray {layoutRoot->GetAttachChildren()};
				// Algo::Sort(CardArray, [](const USceneComponent& A, const USceneComponent& B) 
				// {
				// 	return A.GetReadableName() < B.GetReadableName();
				// });

				// sort card layout components by "order" property
				if (CardArray.Num() > 1)
				{
					CardArray.Sort([](const ULayoutComponent& A, const ULayoutComponent& B) {
						return A.Order < B.Order;
					});
				}

				// Iterate through the child components of the RootComponent
				for (ULayoutComponent* cardComp : CardArray)
				{
					// Check if the child component is a scene component
					if (cardComp && cardComp->IsA<ULayoutComponent>())
					{
						// Add the scene component to the array
						cardComps.Add(Cast<ULayoutComponent>(cardComp));
					}
				}
			}

			int32 numCardComps{cardComps.Num()};
			if (numCardComps != 10)
			{
				UE_LOG(LogTemp, Error, TEXT("Incorrect number of layout components for card layout!: %i"), numCardComps);
				return;
			}

			int32 cardCount {playerPawn->GetLayoutCount()};
			for (int i = 1; i <= cardCount; ++i)
			{
				FActorSpawnParameters SpawnParams {};
				FString NameString = "Card" + i; // Concatenate the strings
				// Convert the combined string to a FName
				FName SpawnName = FName(*NameString); // Convert the FString to FName using the * operator
				SpawnParams.Name = SpawnName;

				// Spawn cards into layout (flipped)
				ABaseCard* Card = GetWorld()->SpawnActor<ABaseCard>(playerLayout->actorToSpawn, cardComps[i - 1]->GetRelativeLocation(), FRotator(0,0,0), SpawnParams);

				if (Card)
				{
					Card->NumPlaceInLayout = i;
					Card->AttachToActor(playerLayout, FAttachmentTransformRules::KeepRelativeTransform);
					UCard* topCard {stockPile->cards.Pop()};
					Card->SetCard(topCard);
					// Card->SetCardText(topCard);

					// Or if you want to attach to a specific component of the parent actor:
					// NewActor->AttachToComponent(ParentActor->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
				}
			}

			
			// GetWorld()->SpawnActor<ABaseCard>()
			// Attach the newly spawned actor to another actor in the scene
			

			// USceneComponent* root {playerLayout->GetRootComponent()};
			// TArray<USceneComponent*> cards {};
			// root->GetChildrenComponents(false, cards);

			// for (USceneComponent* card : cards)
			// {
			// 	FString name {card->GetReadableName()};
			// 	UE_LOG(LogTemp, Display, TEXT("Layout component: %s"), *name);
			// }
		}
		else 
		{
			UE_LOG(LogTemp, Error, TEXT("Player's card layout not set on player pawn"));
		}
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Can't set player's card layout when player pawn is not set"));
	}

	UE_LOG(LogTemp, Warning, TEXT("Setting up the player's layout!"));
	
	// TODO: Get how many cards for the player's layout (should be a variable on PlayerState)
	for (int i = 1; i <= 10; ++i)
	{
		UE_LOG(LogTemp, Log, TEXT("Card %i placed in player's layout!"), i);
	}

}

