// // Fill out your copyright notice in the Description page of Project Settings.


#include "TrashGameState.h"

// ATrashGameState::ATrashGameState() 
// {
//     m_CurrentState = EGameState::setup;
// }

// // Called when the game starts or when spawned
// void ATrashGameState::BeginPlay()
// {
//     Super::BeginPlay();
    
//     UE_LOG(LogTemp, Display, TEXT("Begin Play of TrashGameState called!"));
//     UE_LOG(LogTemp, Display, TEXT("Current state: %i"), static_cast<uint8>(GetState()));
//     // UE_LOG(LogTemp, Warning, TEXT("Name of Player: %s"), *GetOwner()->GetActorNameOrLabel());
// }

// EGameState ATrashGameState::GetState() const { return m_CurrentState; }

// void ATrashGameState::SetState(EGameState NewState)
// {
//     m_CurrentState = NewState;
// }

// // bool ATrashGameState::HasMoreMoves()
// // {
// //     // Get the player's controller
// //     ATrashCardGamePlayerController* Controller {Cast<ATrashCardGamePlayerController>(GetOwner())};
// //     if (Controller)
// //     {
// //         if (Controller->GetNumberMoves() > 0)
// //         {
// //             return true;
// //         }
// //         else 
// //         {
// //             return false;
// //         }
// //     }
    
// //     // If unable to get the pawn or it's not the correct type, return false
// //     UE_LOG(LogTemp, Error, TEXT("Controller not found"));
// //     return false;
// // }
