// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardLayout.generated.h"

class ABaseCard;

UCLASS()
class TRASHCARDGAME_API ACardLayout : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardLayout();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ABaseCard*> cards{};

	// Cards that the player or AI can take action on (wild or face down cards in layout)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, ABaseCard*> ActionableCards{};

	const int32 GetLayoutCount();

private:
	UPROPERTY(VisibleAnywhere)
	int32 LayoutCount{};

};
