// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AICardPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TRASHCARDGAME_API AAICardPlayerController : public AAIController
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAICardPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class AAICardPlayer* player{};

	UFUNCTION()
	void PlayAITurn();

private:
	UPROPERTY(VisibleAnywhere)
	class ATrashGameState* GStateObj{};

	UFUNCTION()
	bool IsComputersTurn();

	UFUNCTION()
	void PlaceCardsInLayout();

	UFUNCTION()
	void Discard();

};
