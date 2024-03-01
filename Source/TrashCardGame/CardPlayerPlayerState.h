// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CardPlayerPlayerState.generated.h"

UENUM(BlueprintType)
enum class EPState : uint8
{
	waiting = 0 UMETA(DisplayName="WAITING"),
	drawing = 1 UMETA(DisplayName="DRAWING"),
	playing = 2 UMETA(DisplayName="PLAYING"),
	invalid = 3 UMETA(DisplayName="INVALID")
};

/**
 * 
 */
UCLASS()
class TRASHCARDGAME_API ACardPlayerPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ACardPlayerPlayerState();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool TestBool{ true };

	UFUNCTION(BlueprintCallable)
	const EPState GetState();

	// UFUNCTION(BlueprintCallable)
	// const EPState SetState();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly)
	EPState m_CurrentState{ };
};
