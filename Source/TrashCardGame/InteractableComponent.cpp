// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableComponent.h"
#include "TrashCardGamePlayerController.h"
#include "CardPlayerPlayerState.h"
// #include "UObject/Class.h"

// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

EPState UInteractableComponent::SetupInteraction()
{
	if (GetWorld()) 
	{
		PlayerController = Cast<ATrashCardGamePlayerController>(GetWorld()->GetFirstPlayerController());
		if (PlayerController)
		{
			// Get the player state object
			PlayerState = Cast<ACardPlayerPlayerState>(PlayerController->GetPlayerState());
			if (PlayerState)
			{
				return PlayerState->GetState();
			}
		}
	}
	else 
	{
		UE_LOG(LogTemp, Display, TEXT("Get world is null!"));
	}

	return EPState::invalid;
}

//void SetState(const EPState& NewState) 
//{
//
//}

// void UInteractableComponent::SetCurrentState()
// {
// 	// UE_LOG(LogTemp, Warning, TEXT("State has been set by the controller!"));
// 	// FString StateString{UEnum::GetValueAsString(PlayerState->GetState())};

// 	// FString LeftSubstring{};
// 	// FString RightSubstring{};
// 	// if (StateString.Split("::", &LeftSubstring, &RightSubstring, ESearchCase::IgnoreCase, ESearchDir::FromStart))
// 	// {
// 	// 	UE_LOG(LogTemp, Warning, TEXT("Second substring: %s"), *RightSubstring);
// 	// }

// 	CurState = PlayerState->GetState();
// }

// void UInteractableComponent::SetCurState()
// {
// 	if (GetWorld()) {
// 		PlayerController = Cast<ATrashCardGamePlayerController>(GetWorld()->GetFirstPlayerController());
// 		if (PlayerController)
// 		{
// 			// Get the player state object
// 			PlayerState = Cast<ACardPlayerPlayerState>(PlayerController->GetPlayerState());
// 			if (PlayerState)
// 			{
// 				UE_LOG(LogTemp, Warning, TEXT("State has been set by the controller!"));
// 				FString StateString{UEnum::GetValueAsString(PlayerState->GetState())};

// 				FString LeftSubstring{};
// 				FString RightSubstring{};
// 				if (StateString.Split("::", &LeftSubstring, &RightSubstring, ESearchCase::IgnoreCase, ESearchDir::FromStart))
// 				{
// 					UE_LOG(LogTemp, Warning, TEXT("Second substring: %s"), *RightSubstring);
// 				}

// 				CurState = PlayerState->GetState();
// 			}
// 		}
// 	}
// 	else {
// 		UE_LOG(LogTemp, Display, TEXT("Get world is null!"));
// 	}
// }

// template <typename T>
// State UInteractableComponent::SetupInteraction()
// {
// 	// Check player state
//     ATrashCardGamePlayerController* PlayerController = Cast<ATrashCardGamePlayerController>(GetWorld()->GetFirstPlayerController());
//     if (PlayerController)
//     {
// 		// Get the player state
// 		ACardPlayerPlayerState* PlayerState = PlayerController->GetPlayerState();
// 		if (PlayerState)
// 		{
// 			UE_LOG(LogTemp, Display, TEXT("PlayerState is not null"));
// 			State CurrentState{PlayerState->GetState()};

// 			return CurrentState;

// 			// GetOwner()->Interact(CurrentState);

// 			// // Perform actions based on player state
// 			// switch (CurrentState)
// 			// {
// 			// 	case State::waiting:
// 			// 	case State::drawing:
// 			// 		// Do nothing or print a message
// 			// 		// BlueprintClass->GetClass()
// 			// 		UE_LOG(LogTemp, Warning, TEXT("Can't do anything yet, player state is either waiting or drawing"));
// 			// 		GetOwner()->Interact(CurrentState);
// 			// 		break;

// 			// 	case State::playing:
// 			// 		// Perform the action for playing state
// 			// 		// e.g., draw a card from the deck
// 			// 		UE_LOG(LogTemp, Warning, TEXT("Playing..."));
// 			// 		break;

// 			// 	default:
// 			// 		break;
// 			// }
// 		}
// 		else 
// 		{
// 			UE_LOG(LogTemp, Display, TEXT("PlayerState is null"));
// 		}
//     }
		
// 	return State::waiting;
// }
