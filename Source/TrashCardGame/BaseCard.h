// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCard.generated.h"

// Forward declare UCard
class UCard;
class ABaseCardPlayer;
class ATrashGameState;

UCLASS()
class TRASHCARDGAME_API ABaseCard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseCard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 NumPlaceInLayout{-1};

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetCard(UCard* newCard, bool initializing);

	UFUNCTION(BlueprintCallable)
	const UCard* GetCard();

	template<typename T>
	void SwapCardInHand(T* Player)
	{
		if (!Player)
		{
			UE_LOG(LogTemp, Error, TEXT("Player doesn't exist when swapping card in hand"));
			return;
		}

		UCard* temp{CardObject}; // temp set to card in hand before placing
		SetCard(Player->CardInHand); // card card object to wild card
		Player->CardInHand = temp;
	}
	
	void SetCardText(UCard* newCard);
	
	UFUNCTION(BlueprintCallable)
	void CheckIfRoundOver(ABaseCardPlayer* Player, ATrashGameState* GState);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool faceUp{ false }; // maybe not ideal default value, but on spawn in TrashCardGameGameMode, the card is flipped and this is set to false

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCard* CardObject{};

	UPROPERTY(VisibleAnywhere, category = "Components")
	class UStaticMeshComponent* MeshComp{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UInteractableComponent* InteractComp{};

	// Called from the InteractableComponent so state can be taken into account
	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintCallable)
	void FlipCard();

	// void FinishRound();

	// void FinishGame();

};
