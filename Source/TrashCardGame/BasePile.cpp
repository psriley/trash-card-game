// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePile.h"
#include "InteractableComponent.h"
#include "CardPlayerPlayerState.h"

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
		switch (InteractComp->CurState) 
		{
			case EPDiddyState::waiting:
				UE_LOG(LogTemp, Warning, TEXT("Can't interact with piles when it's not your turn!"));
				break;
			case EPDiddyState::drawing:
				UE_LOG(LogTemp, Warning, TEXT("Drawing!"));
				break;
			case EPDiddyState::playing:
				UE_LOG(LogTemp, Warning, TEXT("You've already drawn a card!"));
				// set state to waiting (need to conditionally check later if another move can be made before setting state)
				break;
			default:
				UE_LOG(LogTemp, Error, TEXT("This state does not exist!"));
				break;
		}
	}
	else 
	{
		// Return error that we need to call SetupInteraction on the InteractComponent?
	}
}
