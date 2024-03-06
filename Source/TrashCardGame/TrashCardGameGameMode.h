// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "TrashCardGameGameMode.generated.h"

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
	// A "hand" is one round (until one of the players completes their layout)
	UFUNCTION(BlueprintCallable)
	void startHand();
	
	UPROPERTY(BlueprintReadOnly)
	class AController* controller{};

private:
	class UCardDeck* cardDeck{};

	class APlayerState* playerState{};

	UFUNCTION(BlueprintCallable)
	void setupLayouts();

};



