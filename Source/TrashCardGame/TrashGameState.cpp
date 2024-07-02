// // Fill out your copyright notice in the Description page of Project Settings.


#include "TrashGameState.h"
#include "TrashCardGameGameMode.h"
#include "AICardPlayerController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BasePile.h"
// #include "BaseCardPlayer.h"

ATrashGameState::ATrashGameState() 
{
    
}

// Called when the game starts or when spawned
void ATrashGameState::BeginPlay()
{
    Super::BeginPlay();
    
    GameMode = Cast<ATrashCardGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    BlackboardComponent = {GameMode->aiController->GetBlackboardComponent()};
    SetGameStateBlackboardValue();

    // TODO: change this to SetState(EGameState::setup); (so that cards are shuffled, state is properly changed, etc.)
    SetState(EGameState::setup);

//     UE_LOG(LogTemp, Display, TEXT("Begin Play of TrashGameState called!"));
//     UE_LOG(LogTemp, Display, TEXT("Current state: %i"), static_cast<uint8>(GetState()));
//     // UE_LOG(LogTemp, Warning, TEXT("Name of Player: %s"), *GetOwner()->GetActorNameOrLabel());
}

EGameState ATrashGameState::GetState() const { return m_CurrentState; }

void ATrashGameState::SetState(EGameState NewState)
{
    m_CurrentState = NewState;
    if (NewState == EGameState::setup)
    {
        Setup();
    }
}

void ATrashGameState::EndTurn()
{
    switch (m_CurrentState)
    {
    case EGameState::p1Turn:
        SetState(EGameState::computerTurn);
        SetComputersTurnBlackboardValue(true);

        // CallFunctionByNameWithArguments(TEXT("CallFunctionTest 42"), ar, NULL, true);

        StockPileReference->MeshComp->GetStaticMesh()->SetMaterial(0, StockPileReference->DisabledMat);
        DiscardPileReference->MeshComp->GetStaticMesh()->SetMaterial(0, DiscardPileReference->DisabledMat);

        // if (GameMode)
        // {
        //     UBlackboardComponent* BlackboardComponent {GameMode->aiController->GetBlackboardComponent()};
        //     // UBlackboardComponent* BlackboardComponent {BTAsset->BlackboardAsset->GetBlackboardComponent()};
        //     if (BlackboardComponent)
        //     {
        //         // Set the bool value on the Blackboard
        //         BlackboardComponent->SetValueAsBool("IsComputersTurn", BValue);
        //     }
        //     else
        //     {
        //         UE_LOG(LogTemp, Error, TEXT("Blackboard component is nullptr!"));
        //     }
        //     // if (GameMode->aiController)
        //     // {
        //     //     // GameMode->aiController->PlayAITurn();
        //     //     GameMode->BTAsset->BlackboardAsset
                
        //     // }
        // }
        break;
    case EGameState::computerTurn:
        SetState(EGameState::p1Turn);
        SetComputersTurnBlackboardValue(false);
        
        StockPileReference->MeshComp->GetStaticMesh()->SetMaterial(0, StockPileReference->DefaultMat);
        DiscardPileReference->MeshComp->GetStaticMesh()->SetMaterial(0, DiscardPileReference->DefaultMat);


        // if (GameMode)
        // {
        //     if (BTAsset)
        //     {
        //         UBlackboardComponent* BlackboardComponent {BTAsset->BlackboardAsset->GetBlackboardComponent()};
        //         if (BlackboardComponent)
        //         {
        //             // Set the bool value on the Blackboard
        //             BlackboardComponent->SetValueAsBool("IsComputersTurn", false);
        //         }
        //         else
        //         {
        //             UE_LOG(LogTemp, Error, TEXT("Blackboard component is nullptr!"));
        //         }
        //     }
        //     // if (GameMode->aiController)
        //     // {
        //     //     // GameMode->aiController->PlayAITurn();
        //     //     GameMode->BTAsset->BlackboardAsset
                
        //     // }
        // }
        break;
    default:
        UE_LOG(LogTemp, Error, TEXT("Can't end turn from this state!"));
        break;
    }

}

void ATrashGameState::Setup()
{
    // Declare a TimerHandle variable
    FTimerHandle DelayTimerHandle;

    // Start the delay
    float DelaySeconds = 5.0f;
    GetWorld()->GetTimerManager().SetTimer(DelayTimerHandle, [this]() {
        UE_LOG(LogTemp, Display, TEXT("Game State before is: %i"), static_cast<uint8>(m_CurrentState));
        SetState(EGameState::p1Turn);
        UE_LOG(LogTemp, Display, TEXT("Game State is: %i"), static_cast<uint8>(m_CurrentState));
    }, DelaySeconds, false);

    // shuffle cards
    // play animations
    // tutorial?
    // set state to p1Turn
}

void ATrashGameState::StartGameAfterSetup()
{
    SetState(EGameState::p1Turn);
}

void ATrashGameState::SetGameStateBlackboardValue()
{
    if (BlackboardComponent)
    {
        // Set the bool value on the Blackboard
        BlackboardComponent->SetValueAsObject("GameStateObj", this);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Blackboard component is nullptr!"));
    }
}

void ATrashGameState::SetComputersTurnBlackboardValue(bool BValue)
{
    if (GameMode)
    {
        // UBlackboardComponent* BlackboardComponent {BTAsset->BlackboardAsset->GetBlackboardComponent()};
        if (BlackboardComponent)
        {
            // Set the bool value on the Blackboard
            BlackboardComponent->SetValueAsBool("IsComputersTurn", BValue);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Blackboard component is nullptr!"));
        }
        // if (GameMode->aiController)
        // {
        //     // GameMode->aiController->PlayAITurn();
        //     GameMode->BTAsset->BlackboardAsset
            
        // }
    }
}

void ATrashGameState::FinishHand(ABaseCardPlayer* Player)
{
	// set the state to "round over" (to show round result UI), then to "setup" to setup the next round
    UE_LOG(LogTemp, Warning, TEXT("SHOW RESULT UI FOR {Player}"));

    SetState(EGameState::setup);
    GameMode->startHand();
}

void ATrashGameState::FinishGame(ABaseCardPlayer* Player)
{
	// set the state to "game over" and then restart game (and layouts)
}

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
