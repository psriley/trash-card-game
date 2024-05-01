// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCard.generated.h"

// Forward declare UCard
class UCard;
class ACardPlayerPlayerState;

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
	UPROPERTY(VisibleAnywhere)
	int32 NumPlaceInLayout{-1};

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetCard(UCard* newCard);

	UFUNCTION(BlueprintCallable)
	const UCard* GetCard();

private:
	UPROPERTY(VisibleAnywhere)
	bool faceUp{ true }; // maybe not ideal default value, but on spawn in TrashCardGameGameMode, the card is flipped and this is set to false

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCard* CardObject{};

	UPROPERTY(VisibleAnywhere, category = "Components")
	class UStaticMeshComponent* MeshComp{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UInteractableComponent* InteractComp{};

	// Called from the InteractableComponent so state can be taken into account
	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION()
	void SwapCardInHand(ACardPlayerPlayerState* PState);

	UFUNCTION()
	void SetCardText(UCard* newCard);

	UFUNCTION(BlueprintCallable)
	void FlipCard();

};
