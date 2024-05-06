// Fill out your copyright notice in the Description page of Project Settings.


#include "AICardPlayerController.h"

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
	
}

// Called every frame
void AAICardPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
