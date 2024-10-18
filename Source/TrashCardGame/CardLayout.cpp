// Fill out your copyright notice in the Description page of Project Settings.


#include "CardLayout.h"
#include "BaseCard.h"
#include "Components/DecalComponent.h"

// Sets default values
ACardLayout::ACardLayout()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LayoutCount = 10;

	if (!RootComponent)
	{
   		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	}

	// Create the DecalComponent and attach it to the root component
    TurnHighlight = CreateDefaultSubobject<UDecalComponent>(TEXT("TurnHighlightDecal"));
	TurnHighlight->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    // Set default properties for the decal
    TurnHighlight->SetVisibility(false); 
    TurnHighlight->SetRelativeLocation(FVector(0, 0, 0));
	TurnHighlight->SetRelativeRotation(FRotator(90, -90, 0));
	TurnHighlight->DecalSize = FVector(5, 60, 110);
}

// Called when the game starts or when spawned
void ACardLayout::BeginPlay()
{
	Super::BeginPlay();
	
	// if (RootComponent->GetNumChildrenComponents() == 0)
	// {
    // 	// Create card layout location components
	// 	for (int i = 1; i <= 10; ++i)
	// 	{
	// 		FName ComponentName = FName(*FString::Printf(TEXT("Card%d"), i));
	// 		ABaseCard* CardComp = NewObject<ABaseCard>(this, ComponentName);

	// 		if (CardComp)
	// 		{
	// 			CardComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	// 		}
	// 		else
	// 		{
	// 			// Failed to create LayoutLocation
	// 			UE_LOG(LogTemp, Error, TEXT("Failed to create LayoutLocation for Card %d"), i);
	// 		}
	// 	}
	// }
	// else 
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("There are already card components (%i) in this layout: %s"), RootComponent->GetNumChildrenComponents(), *this->GetHumanReadableName());
	// }
}

// Called every frame
void ACardLayout::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

const int32 ACardLayout::GetLayoutCount() 
{
	return LayoutCount;
}

void ACardLayout::ReduceLayoutCount()
{
	LayoutCount -= 1;
}

void ACardLayout::SetTurnHighlight(bool bVisible)
{
	TurnHighlight->SetVisibility(bVisible);
}

bool ACardLayout::IsLayoutCompleted()
{
	for (ABaseCard* card : cards)
	{
		if (!card->faceUp)
		{
			UE_LOG(LogTemp, Display, TEXT("Round is NOT over!"));
			return false;
		}
	}

	UE_LOG(LogTemp, Display, TEXT("Round is over!"));
	return true;
}
