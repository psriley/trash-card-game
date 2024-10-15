// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCardPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "BaseCard.h"

// Sets default values
ABaseCardPlayer::ABaseCardPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = CapsuleComp;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseCardPlayer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseCardPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCardPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCardPlayer::SetCardInHandText()
{
	// HandModel->GetComponentByClass()
	if (!HandModel->GetRootComponent()->IsVisible() && !CardInHandModel->GetRootComponent()->IsVisible())
	{
		SetHandVisibility(true);
	}
	
	CardInHandModel->SetCardText(CardInHand);
}

void ABaseCardPlayer::SetHandVisibility(bool bVisible)
{
	HandModel->GetRootComponent()->SetVisibility(bVisible, true);
	CardInHandModel->GetRootComponent()->SetVisibility(bVisible, true);
}
