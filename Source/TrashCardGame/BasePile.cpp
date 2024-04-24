// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePile.h"
#include "InteractableComponent.h"
#include "CardPlayerPlayerState.h"
#include "Card.h"

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
		ACardPlayerPlayerState* PState{ InteractComp->PlayerState };
		if (PState) {
			switch (PState->GetState())
			{
			case EPState::waiting:
				UE_LOG(LogTemp, Warning, TEXT("Can't interact with piles when it's not your turn!"));
				break;
			// case has brackets so it can have it's own scope (for UCard local variable)
			case EPState::drawing:
			{
				UE_LOG(LogTemp, Warning, TEXT("Drawing!"));
				// Draw card if card exists
				if (cards.Num() > 0) 
				{
					UCard* DrawnCard {cards.Pop()};
					if (DrawnCard)
					{
						UE_LOG(LogTemp, Warning, TEXT("Card: %s"), *DrawnCard->GetDisplayName());
						PState->CardInHand = DrawnCard;
						PState->SetState(EPState::playing);
					}
				}
				else 
				{
					UE_LOG(LogTemp, Warning, TEXT("This pile is empty"));
				}
				break;
			}
			case EPState::playing:
				UE_LOG(LogTemp, Warning, TEXT("You've already drawn a card!"));
				break;
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
