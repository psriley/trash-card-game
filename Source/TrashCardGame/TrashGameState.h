// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TrashGameState.generated.h"

class ABaseCardPlayer;

UENUM(BlueprintType)
enum class EGameState : uint8
{
	setup = 0 UMETA(DisplayName="Setup"), // state at beginning of round and in between rounds (shuffling cards and setting up layouts)
	p1Turn = 1 UMETA(DisplayName="Player 1's Turn"),
	computerTurn = 2 UMETA(DisplayName="Computer's Turn"),
	gameOver = 3 UMETA(DisplayName="Game Over"),
	invalid = 4 UMETA(DisplayName="INVALID")
};

/**
 * 
 */
UCLASS()
class TRASHCARDGAME_API ATrashGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ATrashGameState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	EGameState m_CurrentState{ };

public:
	UPROPERTY(BlueprintReadWrite)
    class ABasePile* StockPileReference;

	UPROPERTY(BlueprintReadWrite)
    class ABasePile* DiscardPileReference;

	UFUNCTION(BlueprintCallable)
    EGameState GetState() const;

	UFUNCTION(BlueprintCallable)
    void SetState(EGameState NewState);

	UFUNCTION(BlueprintCallable)
	void EndTurn();

	void FinishHand(ABaseCardPlayer* Player);

	void FinishGame(ABaseCardPlayer* Player);

private:
	UFUNCTION()
	void Setup();

	UFUNCTION()
	void StartGameAfterSetup();

	void SetGameStateBlackboardValue();

	void SetComputersTurnBlackboardValue(bool BValue);

	class ATrashCardGameGameMode* GameMode;

	class UBlackboardComponent* BlackboardComponent{};

// 	// UFUNCTION(BlueprintCallable)
// 	// bool HasMoreMoves();

// 	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
// 	// UCard* CardInHand{};

};
