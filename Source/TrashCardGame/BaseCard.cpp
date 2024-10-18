// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCard.h"
#include "InteractableComponent.h"
#include "TrashGameState.h"
#include "Kismet/GameplayStatics.h"
#include "TrashCardGameGameMode.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "BaseCardPlayer.h"
#include "CardLayout.h"
#include "AICardPlayer.h"

#include "Card.h"

// Sets default values
ABaseCard::ABaseCard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComp;

	InteractComp = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interactable"));
}

// Called when the game starts or when spawned
void ABaseCard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// void ABaseCard::AssignCard()
// {
// 	ATrashCardGameGameMode* GameMode {Cast<ATrashCardGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()))};
// 	GameMode->Cards
// }

void ABaseCard::Interact() 
{
	if (GetWorld())
	{
		ATrashGameState* GState {GetWorld()->GetGameState<ATrashGameState>()};

		if (GState)
		{
			ABaseCardPlayer* Player{};
			
			switch (GState->GetState())
			{
				case EGameState::p1Turn:
					// can't make actions with this selected card if it is faceUp
					if (faceUp && !CardObject->IsWild)
					{
						UE_LOG(LogTemp, Warning, TEXT("Can't do anything face up cards!"));
						break;
					}

					Player = Cast<ABaseCardPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());

					if (!Player)
					{
						UE_LOG(LogTemp, Error, TEXT("Player doesn't exist while interacting with card!"));
						return;
					}

					if (Player->CardInHand)
					{
						if (Player->CardInHand->IsWild) 
						{
							SwapCardInHand<ABaseCardPlayer>(Player);
							Player->CardInHandModel->SetCardText(Player->CardInHand);
							UE_LOG(LogTemp, Display, TEXT("Placed wild in position %i!"), NumPlaceInLayout);
							CheckIfRoundOver(Player, GState);
							break;
						}

						if (Player->CardInHand->Rank == NumPlaceInLayout || (CardObject->IsWild && Player->CardInHand->Rank == NumPlaceInLayout))
						{
							UCard* PlacedCard = Player->CardInHand; // temporary variable so it can be printed later after card in hand is swapped
							SwapCardInHand<ABaseCardPlayer>(Player);
							Player->CardInHandModel->SetCardText(Player->CardInHand);
							UE_LOG(LogTemp, Display, TEXT("Placed %s in position %i!"), *PlacedCard->GetDisplayName(), NumPlaceInLayout);
							CheckIfRoundOver(Player, GState);
							break;
						}
						
						UE_LOG(LogTemp, Warning, TEXT("Can't place %s in position %i!"), *Player->CardInHand->GetDisplayName(), NumPlaceInLayout);
					}

					break;
				default:
					break;
			}

			// if (GState->GetState() != EGameState::p1Turn) 
			// {
			// 	UE_LOG(LogTemp, Warning, TEXT("State is NOT p1Turn!"));
			// 	return; // player can't do anything if it isn't their turn
			// }
			// else 
			// {
			// 	// if card in hand...
			// 	UE_LOG(LogTemp, Warning, TEXT("State is p1Turn!"));
			// 	return;
			// }
		}
	}
	
		
		// if (GState) {
		// 	switch (GState->GetState())
		// 	{
		// 	case EGameState::computerTurn:
		// 		UE_LOG(LogTemp, Warning, TEXT("Can't interact with deck when it's not your turn!"));
		// 		break;
		// 	case EGameState::computerTurn:
		// 		UE_LOG(LogTemp, Warning, TEXT("Can't interact with deck when it's not your turn!"));
		// 		break;
		// 	case EGameState::drawing:
		// 		UE_LOG(LogTemp, Warning, TEXT("You must draw a card first!"));
		// 		break;
		// 	case EGameState::playing:
		// 		UE_LOG(LogTemp, Warning, TEXT("Playing!"));
				
		// 		// can't make actions with this selected card if it is faceUp
		// 		if (faceUp)
		// 		{
		// 			UE_LOG(LogTemp, Warning, TEXT("Can't do anything face up cards!"));
		// 			break;
		// 		}

		// 		if (PState->CardInHand->IsWild)
		// 		{
		// 			SwapCardInHand(PState);
		// 			UE_LOG(LogTemp, Display, TEXT("Placed wild in position %i!"), NumPlaceInLayout);
		// 			break;
		// 		}

		// 		if (PState->CardInHand->Rank == NumPlaceInLayout)
		// 		{
		// 			UCard* PlacedCard = PState->CardInHand; // temporary variable so it can be printed later after card in hand is swapped
		// 			SwapCardInHand(PState);
		// 			UE_LOG(LogTemp, Display, TEXT("Placed %s in position %i!"), *PlacedCard->GetDisplayName(), NumPlaceInLayout);
		// 			break;
		// 		}
				

		// 		UE_LOG(LogTemp, Warning, TEXT("Can't place %s in position %i!"), *PState->CardInHand->GetDisplayName(), NumPlaceInLayout);
		// 		break;
		// 		// // set state to waiting (need to conditionally check later if another move can be made before setting state)
		// 		// if (!(PState->HasMoreMoves())) 
		// 		// { 
		// 		// 	PState->SetState(EPState::playing); 
		// 		// 	UE_LOG(LogTemp, Display, TEXT("State changed to playing"));
		// 		// }
		// 	default:
		// 		UE_LOG(LogTemp, Error, TEXT("This state does not exist!"));
		// 		break;
		// 	}
		// }
}

void ABaseCard::CheckIfRoundOver(AActor* Player, ATrashGameState* GState)
{
	if (Player)
	{
		ABaseCardPlayer* CardPlayer {Cast<ABaseCardPlayer>(Player)};
		if (CardPlayer)
		{
			bool RoundOver {};

			if (CardPlayer->Layout->IsLayoutCompleted())
			{
				if (CardPlayer->Layout->GetLayoutCount() <= 1)
				{
					GState->FinishGame();
				}

				GState->FinishHand();
			}
		}
		else 
		{
			AAICardPlayer* AIPlayer {Cast<AAICardPlayer>(Player)};
			
			if (AIPlayer)
			{
				bool RoundOver {};

				if (AIPlayer->Layout->IsLayoutCompleted())
				{
					if (AIPlayer->Layout->GetLayoutCount() <= 1)
					{
						GState->FinishGame();
					}

					GState->FinishHand();
				}
			}
		}
	}
}

// void ABaseCard::FinishRound()
// {
// 	// set the state to "round over" (to show round result UI), then to "setup" to setup the next round
// }

// void ABaseCard::FinishGame()
// {
// 	// set the state to "game over" and then restart game (and layouts)
// }

void ABaseCard::SetCard(UCard* newCard, bool initializing = false)
{
	// UE_LOG(LogTemp, Warning, TEXT("Your message"));
	CardObject = newCard;
	SetCardText(CardObject);
	if (!initializing)
	{
		if (!faceUp)
		{
			FlipCard(); // set faceUp to true and flip actor 180 degrees
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Card has already been flipped..."));
			return;
		}
	}
}

const UCard* ABaseCard::GetCard()
{
	return CardObject;
}

void ABaseCard::SetCardText(UCard* newCard)
{
	if (newCard)
	{
		// MeshComp->GetAttachChildren<UTextRenderComponent>();
		// MeshComp->GetChildrenComponents<UTextRenderComponent>
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

void ABaseCard::FlipCard()
{
	
	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Roll += 180.0f; // flip card 180 degrees
	SetActorRotation(CurrentRotation);

	faceUp = true; // toggle faceUp value
}
