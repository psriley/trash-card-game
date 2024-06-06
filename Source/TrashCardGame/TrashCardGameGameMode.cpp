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
#include "AICardPlayer.h"
#include "AICardPlayerController.h"

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
	UE_LOG(LogTemp, Display, TEXT("Begin Play of TrashCardGameGameMode called!"));

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

	SpawnAIActor();
	setupLayouts();
}

void ATrashCardGameGameMode::SpawnAIActor()
{
    // Spawn the AI actor
    AAICardPlayer* NewAIActor = GetWorld()->SpawnActor<AAICardPlayer>(AAICardPlayer::StaticClass(), FVector(-280, -80, 4), FRotator(0, 0, 180));

    if (NewAIActor)
    {
		// Get a reference to the AI Controller
		aiController = GetWorld()->SpawnActor<AAICardPlayerController>(AAICardPlayerController::StaticClass(), FVector::ZeroVector, FRotator(0,0,0));
		// aiController = GetWorld()->SpawnActor<AAICardPlayerController>(AAICardPlayerController::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

        if (aiController)
        {
            // Possess the AI actor with the AI Controller
            aiController->player = NewAIActor;

			// start behavior tree
			aiController->RunBehaviorTree(BTAsset);
        }
		// NewAIActor->AIController = 
	}
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
	ACardLayout* playerLayout{};
	bool playerLayoutCreated = getPlayerLayout(playerLayout);

	ACardLayout* aiLayout{};
	bool aiLayoutCreated = createAILayout(aiLayout, playerLayout->GetActorLocation());

	if (playerLayoutCreated && aiLayoutCreated)
	{
		SpawnLayoutCards(playerLayout);
		SpawnLayoutCards(aiLayout);
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Couldn't set up the layouts because player and ai layouts weren't both valid."));
	}

}

// Take in a ACardLayout pointer by reference so that I can change the value without having to copy it
bool ATrashCardGameGameMode::getPlayerLayout(ACardLayout*& layout)
{
	UE_LOG(LogTemp, Display, TEXT("Setting up the player's layout!"));
    controller->PlayerState;
    ABaseCardPlayer* playerPawn = Cast<ABaseCardPlayer>(controller->GetPawn());
    if (playerPawn)
    {
        layout = playerPawn->Layout;
        return true; // Layout retrieved successfully
    }
    else 
    {
        layout = nullptr;
        return false; // Unable to retrieve layout
    }
}

// Take in a ACardLayout pointer by reference so that I can change the value without having to copy it
bool ATrashCardGameGameMode::createAILayout(ACardLayout*& layout, FVector position)
{
	UE_LOG(LogTemp, Display, TEXT("Setting up the ai's layout!"));
	AAICardPlayer* AIActor {aiController->player};
	if (AIActor)
	{
		FActorSpawnParameters SpawnParams {};
		FString NameString = "Layout"; // Concatenate the strings
		// Convert the combined string to a FName
		FName SpawnName = FName(*NameString); // Convert the FString to FName using the * operator
		SpawnParams.Name = SpawnName;

		ACardLayout* aiCardLayout = GetWorld()->SpawnActor<ACardLayout>(layoutActorToSpawn, position + FVector(156,0,0), FRotator(0,0,0), SpawnParams);

		AIActor->Layout = aiCardLayout;
		layout = aiCardLayout;
		return true; // Layout created successfully
	}
	else
	{
		layout = nullptr;
        return false; // Unable to create layout
	}
}

void ATrashCardGameGameMode::SpawnLayoutCards(ACardLayout* layout)
{
	if (layout)
	{
		USceneComponent* layoutRoot = layout->GetRootComponent();

		if (layoutRoot)
		{
			TArray<ULayoutComponent*> CardArray {layoutRoot->GetAttachChildren()};

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
				// Check if the child component is a layout component
				if (cardComp && cardComp->IsA<ULayoutComponent>())
				{
					// Add the layout component to the array
					cardComps.Add(Cast<ULayoutComponent>(cardComp));
				}
			}
		}

		// Assert that the number of cards in the layout is 10 at the start
		int32 numCardComps{cardComps.Num()};
		if (numCardComps != 10)
		{
			UE_LOG(LogTemp, Error, TEXT("Incorrect number of layout components for card layout!: %i"), numCardComps);
			return;
		}

		// Spawn card actors in layout
		int32 cardCount {layout->GetLayoutCount()};
		for (int i = 1; i <= cardCount; ++i)
		{
			// FActorSpawnParameters SpawnParams {};
			// FString NameString = "Card" + i; // Concatenate the strings
			// // Convert the combined string to a FName
			// FName SpawnName = FName(*NameString); // Convert the FString to FName using the * operator
			// SpawnParams.Name = SpawnName;

			// Spawn cards into layout (flipped)
			ABaseCard* Card = GetWorld()->SpawnActor<ABaseCard>(cardLayoutActorToSpawn, cardComps[i - 1]->GetRelativeLocation(), FRotator(0,0,180));

			if (Card)
			{
				Card->NumPlaceInLayout = i;
				Card->AttachToActor(layout, FAttachmentTransformRules::KeepRelativeTransform);
				UCard* topCard {stockPile->cards.Pop()};
				Card->SetCard(topCard, true);
				layout->cards.Add(Card);
				// Card->SetCardText(topCard);

				// Or if you want to attach to a specific component of the parent actor:
				// NewActor->AttachToComponent(ParentActor->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
			}
		}

		// DebugCardLayout();
		cardComps.Empty();
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("Can only create cards if layout is valid."));
	}
}

void ATrashCardGameGameMode::DebugCardLayout()
{
	// TODO: Get how many cards for the player's layout (should be a variable on PlayerState)
	for (int i = 1; i <= 10; ++i)
	{
		UE_LOG(LogTemp, Log, TEXT("Card %i placed in player's layout!"), i);
	}
}
