// Fill out your copyright notice in the Description page of Project Settings.


#include "RunBehavior.h"
#include "AICardPlayer.h"
#include "AICardPlayerController.h"
#include "TrashCardGameGameMode.h"

// Sets default values for this component's properties
URunBehavior::URunBehavior()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URunBehavior::BeginPlay()
{
	Super::BeginPlay();

	// ATrashCardGameGameMode* GMode {Cast<ATrashCardGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()))};
	// if (GMode)
	// {
	// 	UBehaviorTree* BTAsset = GMode->BTAsset;
	// 	if (BTAsset)
	// 	{
	// 		Cast<AAICardPlayer>(GetOwner())->AIController->RunBehaviorTree(BTAsset);
	// 	}
	// 	else 
	// 	{
	// 		UE_LOG(LogTemp, Error, TEXT("Can't run behavior tree because BTAsset isn't set on the owner of this component"));
	// 	}
	// }
	
}


// Called every frame
void URunBehavior::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URunBehavior::StartBehaviorTree(UBehaviorTree* BTree)
{
	
}
