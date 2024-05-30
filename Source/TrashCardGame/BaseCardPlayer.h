// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseCardPlayer.generated.h"

UCLASS()
class TRASHCARDGAME_API ABaseCardPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseCardPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere)
	class ACardLayout* Layout{};

	UPROPERTY(VisibleAnywhere, category = "Components")
	TArray<USceneComponent*> LayoutLocations{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCard* CardInHand{};

private:
	UPROPERTY(VisibleAnywhere, category = "Components")
	class UCapsuleComponent* CapsuleComp{};

	UPROPERTY(VisibleAnywhere, category = "Components")
	class UCameraComponent* CameraComp{};
};
