// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCard.h"
#include "InteractableComponent.h"
#include "CardPlayerPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "TrashCardGameGameMode.h"
#include "GameFramework/Actor.h"
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
				// set state to waiting (need to conditionally check later if another move can be made before setting state)
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


void ABaseCard::SetCard(UCard* newCard)
{
	CardObject = newCard;
}

const UCard* ABaseCard::GetCard()
{
	return CardObject;
}
