// // Fill out your copyright notice in the Description page of Project Settings.

// #pragma once

// #include "CoreMinimal.h"
// #include "UObject/Object.h"
// #include "Card.generated.h"

// /**
//  * 
//  */
// UCLASS()
// class TRASHCARDGAME_API UCard : public UObject
// {
// 	GENERATED_BODY()

// public:
// 	UCard();
	
// 	enum Suit
// 	{
// 		clubs,
// 		diamonds,
// 		hearts,
// 		spades,
// 		invalid
// 	};
	

// private:
// 	int m_rank;
// 	Suit m_suit;
// };

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.generated.h"

UCLASS(Blueprintable)
class TRASHCARDGAME_API UCard : public UObject
{
    GENERATED_BODY()

public:
	UCard();

    UFUNCTION(BlueprintCallable)
    FString& GetDisplayName();

    UPROPERTY(BlueprintReadOnly)
    int32 Rank{};

    UPROPERTY(BlueprintReadOnly)
    FString Suit{};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool IsWild;

private:

    UPROPERTY(VisibleAnywhere)
    FString DisplayName{};

	// ToString method that prints the "name" in appropriate places (Ace, King, Jack, Queen, 10, etc.)
};
