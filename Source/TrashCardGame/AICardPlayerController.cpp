// Fill out your copyright notice in the Description page of Project Settings.


#include "AICardPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TrashGameState.h" // also includes EGameState

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

void AAICardPlayerController::PlayAITurn()
{
	if (IsComputersTurn())
	{
		UE_LOG(LogTemp, Display, TEXT("Playing AI's turn..."));
		UE_LOG(LogTemp, Error, TEXT("Current state of the game before ending turn is: %i"), static_cast<uint8>(GStateObj->GetState()));
		GStateObj->EndTurn();
		UE_LOG(LogTemp, Error, TEXT("Current state of the game has changed to: %i"), static_cast<uint8>(GStateObj->GetState()));
	}
}
