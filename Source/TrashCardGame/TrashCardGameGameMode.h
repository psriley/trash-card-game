// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "TrashCardGameGameMode.generated.h"

// Forward declare UCard, ULayoutComponent
class UCard;
class ULayoutComponent;

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

	UPROPERTY(BlueprintReadOnly)
	class AAICardPlayerController* aiController{};

	UPROPERTY(VisibleAnywhere)
    class UCardDeck* cardDeckInstance{};

	UPROPERTY(EditDefaultsOnly)
	class ABasePile* stockPile{};

	UPROPERTY(EditDefaultsOnly)
	class ABasePile* discardPile{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ABaseCard> cardLayoutActorToSpawn{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class ACardLayout> layoutActorToSpawn{};

	UPROPERTY(VisibleAnywhere)
	TArray<ULayoutComponent*> cardComps{};

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BTAsset{};

private:
	class APlayerState* playerState{};

	UFUNCTION(BlueprintCallable)
	void setupLayouts();

	void SpawnAIActor();

	UFUNCTION(BlueprintCallable)
	void setupPiles();

	UFUNCTION(BlueprintCallable)
	bool getPlayerLayout(ACardLayout*& layout);

	bool createAILayout(ACardLayout*& layout, FVector position);

	void SpawnLayoutCards(ACardLayout* layout);

	UFUNCTION(BlueprintCallable)
	void DebugCardLayout();

};



