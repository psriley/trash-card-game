// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCard.h"
#include "InteractableComponent.h"
#include "CardPlayerPlayerState.h"

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

void ABaseCard::Interact() 
{
	if (InteractComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current state: %s. Can choose what to do for this: %s"), InteractComp->CurState, this);
	}
}
