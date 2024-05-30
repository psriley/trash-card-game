// Fill out your copyright notice in the Description page of Project Settings.


#include "CardPlayerPlayerState.h"
#include "TrashCardGamePlayerController.h"

ACardPlayerPlayerState::ACardPlayerPlayerState() 
{
    // m_CurrentState = EPState::waiting;
}

// EPState ACardPlayerPlayerState::GetState() const { return m_CurrentState; }

// void ACardPlayerPlayerState::SetState(EPState NewState)
// {
//     m_CurrentState = NewState;
// }

// bool ACardPlayerPlayerState::HasMoreMoves()
// {
//     // Get the player's controller
//     ATrashCardGamePlayerController* Controller {Cast<ATrashCardGamePlayerController>(GetOwner())};
//     if (Controller)
//     {
//         if (Controller->GetNumberMoves() > 0)
//         {
//             return true;
//         }
//         else 
//         {
//             return false;
//         }
//     }
    
//     // If unable to get the pawn or it's not the correct type, return false
//     UE_LOG(LogTemp, Error, TEXT("Controller not found"));
//     return false;
// }

// Called when the game starts or when spawned
void ACardPlayerPlayerState::BeginPlay()
{
    Super::BeginPlay();
    
    // UE_LOG(LogTemp, Display, TEXT("Current state: %i"), static_cast<uint8>(GetState()));
    // UE_LOG(LogTemp, Warning, TEXT("Name of Player: %s"), *GetOwner()->GetActorNameOrLabel());
}
