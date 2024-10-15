// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePile.h"
#include "InteractableComponent.h"
#include "CardPlayerPlayerState.h"
#include "Card.h"
#include "TrashGameState.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCardPlayer.h"
#include "Components/TextRenderComponent.h"
#include "Components/DecalComponent.h"
#include "CardLayout.h"

// Sets default values
ABasePile::ABasePile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComp;

	InteractComp = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable"));
}

// Called when the game starts or when spawned
void ABasePile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePile::Interact()
{
	if (InteractComp) 
	{
		if (GetWorld())
		{
			ATrashGameState* GState {GetWorld()->GetGameState<ATrashGameState>()};
			
			if (GState)
			{
				ABaseCardPlayer* Player{};

				switch (GState->GetState())
				{
					case EGameState::setup:
						UE_LOG(LogTemp, Error, TEXT("Can't interact with piles in the setup state"));
						// TODO: Set TurnHighlight on player and AI layout's to false
						break;
					case EGameState::p1Turn:
						Player = Cast<ABaseCardPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());

						if (!Player)
						{
							UE_LOG(LogTemp, Error, TEXT("Player doesn't exist while interacting with pile!"));
							return;
						}

						if (isDiscardPile)
						{
							if (Player->CardInHand) 
							{
								PlayerDiscardCard(Player);
								
								GState->EndTurn();
								break;
							}

							UE_LOG(LogTemp, Warning, TEXT("Drawing from discard pile!"));
						}
						else 
						{
							if (Player->CardInHand) 
							{
								UE_LOG(LogTemp, Warning, TEXT("Player already has a card in hand, cannot draw again!"));
								break;
							}

							UE_LOG(LogTemp, Warning, TEXT("Drawing from stock pile!"));
						}

						// Draw card if card exists and player hasn't already drawn
						PlayerDrawCard(Player);
						
						break;
					default:
						break;
				}
			}
		}
	}
	// if (InteractComp)
	// {
	// 	ACardPlayerPlayerState* PState{ InteractComp->PlayerState };
	// 	if (PState) {
	// 		switch (PState->GetState())
	// 		{
	// 		case EPState::waiting:
	// 			UE_LOG(LogTemp, Warning, TEXT("Can't interact with piles when it's not your turn!"));
	// 			break;
	// 		// case has brackets so it can have it's own scope (for UCard local variable)
	// 		case EPState::drawing:
	// 		{
	// 			if (isDiscardPile)
	// 			{
	// 				UE_LOG(LogTemp, Warning, TEXT("Drawing from discard pile!"));
	// 			}
	// 			else 
	// 			{
	// 				UE_LOG(LogTemp, Warning, TEXT("Drawing from stock pile!"));
	// 			}

	// 			// Draw card if card exists
	// 			if (cards.Num() > 0) 
	// 			{
	// 				UCard* DrawnCard {cards.Pop()};
	// 				if (DrawnCard)
	// 				{
	// 					UE_LOG(LogTemp, Warning, TEXT("Card: %s"), *DrawnCard->GetDisplayName());
	// 					PState->CardInHand = DrawnCard;
	// 					PState->SetState(EPState::playing);
	// 				}
	// 			}
	// 			else 
	// 			{
	// 				UE_LOG(LogTemp, Warning, TEXT("This pile is empty"));
	// 			}
	// 			break;
	// 		}
	// 		case EPState::playing:
	// 			if (isDiscardPile)
	// 			{
	// 				// FOnEndTurn(true);
	// 				UE_LOG(LogTemp, Warning, TEXT("Ending turn because you discarded!"));
	// 			}
	// 			else 
	// 			{
	// 				UE_LOG(LogTemp, Warning, TEXT("You've already drawn a card!"));
	// 			}
	// 			break;
	// 		default:
	// 			UE_LOG(LogTemp, Error, TEXT("This state does not exist!"));
	// 			break;
	// 		}
	// 	}
	// }
	// else 
	// {
	// 	// Return error that we need to call SetupInteraction on the InteractComponent?
	// }
}

void ABasePile::PlayerDrawCard(ABaseCardPlayer* player)
{
	if (cards.Num() > 0) 
	{
		UCard* DrawnCard {cards.Pop()};
		if (DrawnCard)
		{
			UE_LOG(LogTemp, Warning, TEXT("Card: %s"), *DrawnCard->GetDisplayName());
			
			// set card in hand
			if (player)
			{
				player->CardInHand = DrawnCard;
				
				player->SetCardInHandText();

				if (isDiscardPile)
				{
					UCard* tempCard {cards.Last()};
					SetDiscardPileText(tempCard);
				}
			}
		}
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("This pile is empty"));
	}
}

void ABasePile::PlayerDiscardCard(ABaseCardPlayer* player)
{
	UE_LOG(LogTemp, Warning, TEXT("Discarding!"));
	cards.Add(player->CardInHand);
	SetDiscardPileText(player->CardInHand);
	// SetTurnHighlight(Player->Layout);
	player->CardInHand = nullptr;
	player->SetHandVisibility(false);

	// Trigger delegate to show the layout highlight to indicate whose turn it is
	OnPlayerDiscard.Broadcast(player);
}

UCard* ABasePile::AIDrawCard()
{
	// Draw card if card exists and player hasn't already drawn
	if (cards.Num() > 0) 
	{
		UCard* DrawnCard {cards.Pop()};
		if (DrawnCard)
		{
			UE_LOG(LogTemp, Warning, TEXT("Card: %s"), *DrawnCard->GetDisplayName());
			
			// set card in hand
			return DrawnCard;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("This pile is empty"));
	return nullptr;
}

void ABasePile::AIDiscardCard(UCard* Card)
{
	cards.Add(Card);
	SetDiscardPileText(Card);
	UE_LOG(LogTemp, Warning, TEXT("AI discarded!"));

	// Trigger delegate to show the layout highlight to indicate whose turn it is
	OnPlayerDiscard.Broadcast(nullptr);
}

void ABasePile::SetDiscardPileText(UCard* newCard)
{
	if (newCard)
	{
		if (MeshComp)
		{
			// Array to store all child components
			TArray<USceneComponent*> TextRenderComponents;

			// Get all child components
			MeshComp->GetChildrenComponents(true, TextRenderComponents);

			// Loop through each child component
			for (USceneComponent* TextRenderComponent : TextRenderComponents)
			{
				FString TextComponentName {TextRenderComponent->GetName()};
				if (TextComponentName == "SuitText")
				{
					FText newText = FText::FromString(newCard->Suit);
					Cast<UTextRenderComponent>(TextRenderComponent)->SetText(newText);
				}
				else if (TextComponentName == "RankText")
				{
					FText newText = FText::FromString(newCard->GetRankDisplayName());
					Cast<UTextRenderComponent>(TextRenderComponent)->SetText(newText);
				}
				else 
				{
					UE_LOG(LogTemp, Error, TEXT("TextRenderComponent on card actor does not have 'SuitText' or 'RankText' as its name"));
					return;
				}
				
				UE_LOG(LogTemp, Warning, TEXT("TextRenderComponent: %s"), *TextRenderComponent->GetName());
				// Cast<UTextRenderComponent>(TextRenderComponent)->Text = "Hello";
				// This is a TextRenderComponent attached to the mesh component
				// You can now use TextRenderComponent as needed
			}
		}
	}
}

// void ABasePile::FOnEndTurn(bool Test)
// {

// }
