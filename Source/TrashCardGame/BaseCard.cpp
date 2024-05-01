// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCard.h"
#include "InteractableComponent.h"
#include "CardPlayerPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "TrashCardGameGameMode.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"

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
	if (InteractComp)
	{
		ACardPlayerPlayerState* PState{ InteractComp->PlayerState };
		if (PState) {
			switch (PState->GetState())
			{
			case EPState::waiting:
				UE_LOG(LogTemp, Warning, TEXT("Can't interact with deck when it's not your turn!"));
				break;
			case EPState::drawing:
				UE_LOG(LogTemp, Warning, TEXT("You must draw a card first!"));
				break;
			case EPState::playing:
				UE_LOG(LogTemp, Warning, TEXT("Playing!"));
				
				// can't make actions with this selected card if it is faceUp
				if (faceUp)
				{
					UE_LOG(LogTemp, Warning, TEXT("Can't do anything face up cards!"));
					break;
				}

				if (PState->CardInHand->IsWild)
				{
					SwapCardInHand(PState);
					UE_LOG(LogTemp, Display, TEXT("Placed wild in position %i!"), NumPlaceInLayout);
					break;
				}

				if (PState->CardInHand->Rank == NumPlaceInLayout)
				{
					UCard* PlacedCard = PState->CardInHand; // temporary variable so it can be printed later after card in hand is swapped
					SwapCardInHand(PState);
					UE_LOG(LogTemp, Display, TEXT("Placed %s in position %i!"), *PlacedCard->GetDisplayName(), NumPlaceInLayout);
					break;
				}
				

				UE_LOG(LogTemp, Warning, TEXT("Can't place %s in position %i!"), *PState->CardInHand->GetDisplayName(), NumPlaceInLayout);
				break;
				// // set state to waiting (need to conditionally check later if another move can be made before setting state)
				// if (!(PState->HasMoreMoves())) 
				// { 
				// 	PState->SetState(EPState::playing); 
				// 	UE_LOG(LogTemp, Display, TEXT("State changed to playing"));
				// }
			default:
				UE_LOG(LogTemp, Error, TEXT("This state does not exist!"));
				break;
			}
		}
	}
	else 
	{
		// Return error that we need to call SetupInteraction on the InteractComponent?
	}
}

void ABaseCard::SwapCardInHand(ACardPlayerPlayerState* PState)
{
	if (!PState)
	{
		UE_LOG(LogTemp, Error, TEXT("PState doesn't exist when swapping card in hand"));
		return;
	}

	UCard* temp{CardObject}; // temp set to card in hand before placing
	SetCard(PState->CardInHand); // card card object to wild card
	PState->CardInHand = temp;
	faceUp = true;
}

void ABaseCard::SetCard(UCard* newCard)
{
	CardObject = newCard;
	SetCardText(CardObject);
	FlipCard(); // set faceUp to true and flip actor 180 degrees
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
					FText newText = FText::AsNumber(newCard->Rank);
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
	faceUp = !faceUp; // toggle faceUp value

	// flip card 180 degrees
	FRotator CurrentRotation = GetActorRotation();
    CurrentRotation.Roll += 180.0f;
    SetActorRotation(CurrentRotation);
}
