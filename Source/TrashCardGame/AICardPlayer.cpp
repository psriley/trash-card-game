// Fill out your copyright notice in the Description page of Project Settings.


#include "AICardPlayer.h"
#include "RunBehavior.h"

// Sets default values
AAICardPlayer::AAICardPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BehaviorComp = CreateDefaultSubobject<URunBehavior>(TEXT("BehaviorTree"));
	AddOwnedComponent(BehaviorComp);

}

// Called when the game starts or when spawned
void AAICardPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICardPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
