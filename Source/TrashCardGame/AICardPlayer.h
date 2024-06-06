// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AICardPlayer.generated.h"

UCLASS()
class TRASHCARDGAME_API AAICardPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAICardPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class AAICardPlayerController* AIController{};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class ACardLayout* Layout{};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCard* CardInHand{};

private:
	UPROPERTY(VisibleAnywhere, category = "Components")
	class URunBehavior* BehaviorComp{};

};
