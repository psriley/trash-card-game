// Fill out your copyright notice in the Description page of Project Settings.


#include "CardPlayerPlayerState.h"

ACardPlayerPlayerState::ACardPlayerPlayerState() 
{
    m_CurrentState = EPDiddyState::waiting;
}

const EPDiddyState ACardPlayerPlayerState::GetState() { return m_CurrentState; }

// Called when the game starts or when spawned
void ACardPlayerPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
    UE_LOG(LogTemp, Display, TEXT("Current state: %i"), GetState());
    UE_LOG(LogTemp, Warning, TEXT("Name of Player: %s"), *GetOwner()->GetActorNameOrLabel());
}
