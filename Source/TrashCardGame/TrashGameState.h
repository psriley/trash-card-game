// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TrashGameState.generated.h"

/**
 * 
 */
UCLASS()
class TRASHCARDGAME_API ATrashGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
    class ABasePile* StockPileReference;

	UPROPERTY(BlueprintReadWrite)
    class ABasePile* DiscardPileReference;
};
