// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

// Forward declare EGameState enum
enum class EGameState : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRASHCARDGAME_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	//UPROPERTY(BlueprintReadOnly)
	//EPState CurState { };
	// class ACardPlayerPlayerState* PlayerState{};

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//void SetState(const EPState& NewState);

	// UFUNCTION(BlueprintCallable)
	// void SetupInteraction();

private:
	class ATrashCardGamePlayerController* PlayerController{};

	UFUNCTION(BlueprintCallable)
	EGameState SetupInteraction();
};
