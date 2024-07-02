// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePile.generated.h"

// Forward declare UCard, UMaterial
class UCard;
class UMaterialInterface;

DECLARE_DELEGATE_OneParam(FBoolDelegate, bool);

UCLASS()
class TRASHCARDGAME_API ABasePile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	TArray<UCard*> cards{};

	UPROPERTY(BlueprintReadWrite)
	bool isDiscardPile{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* DefaultMat{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* DisabledMat{};

	// Called from the InteractableComponent so state can be taken into account
	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintCallable)
	UCard* AIDrawCard();

	UFUNCTION()
	void AIDiscardCard(UCard* Card);

	void SetDiscardPileText(UCard* newCard);

	
	UPROPERTY(VisibleAnywhere, category = "Components")
	class UStaticMeshComponent* MeshComp{};


	// UPROPERTY(BlueprintAssignable)
	// FBoolDelegate EndTurnDelegate;
	// void FOnEndTurn(bool Test);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components", meta = (AllowPrivateAccess = "true"))
	class UInteractableComponent* InteractComp{};

	// UFUNCTION(BlueprintNativeEvent)
	// void InteractWithDiscardPile();

};
