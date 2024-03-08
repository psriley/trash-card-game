// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "TrashCardGameGameMode.generated.h"

// Forward declare UCard
class UCard;

UCLASS(minimalapi)
class ATrashCardGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATrashCardGameGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void InitializeCards();
	
	// A "hand" is one round (until one of the players completes their layout)
	UFUNCTION(BlueprintCallable)
	void startHand();
	
	UPROPERTY(BlueprintReadOnly)
	class AController* controller{};

	UPROPERTY(VisibleAnywhere)
    class UCardDeck* cardDeckInstance{};

	UPROPERTY(EditDefaultsOnly)
	class ABasePile* stockPile{};

	UPROPERTY(EditDefaultsOnly)
	class ABasePile* discardPile{};

private:
	class APlayerState* playerState{};

	UFUNCTION(BlueprintCallable)
	void setupLayouts();

};



