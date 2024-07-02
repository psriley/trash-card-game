// Fill out your copyright notice in the Description page of Project Settings.


#include "CardLayout.h"
#include "BaseCard.h"

// Sets default values
ACardLayout::ACardLayout()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LayoutCount = 10;
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
