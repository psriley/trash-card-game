// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TrashCardGamePlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class TRASHCARDGAME_API ATrashCardGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATrashCardGamePlayerController();

	class ACardPlayerPlayerState* GetPlayerState() const;

	UFUNCTION(BlueprintCallable)
	int32 GetNumberMoves();
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface

private:
	class ABaseCardPlayer* PlayerPawn{};
};
