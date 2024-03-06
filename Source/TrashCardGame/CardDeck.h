#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CardDeck.generated.h"

// /**
//  * 
//  */
// UCLASS()
// class TRASHCARDGAME_API UCardDeck : public UObject
// {
// 	GENERATED_BODY()

// public:
// 	UCardDeck();

// private:
// 	TArray<class UCard> cards {};
// 	const int num_ranks{ 13 };


// 	// Classes:
// 	// ShuffleDeck
// 	// DealCards
// 	// Reset?
// };

// Forward declare UCard
class UCard;

UENUM()
enum class Suit : uint8
{
	clubs = 0 UMETA(DisplayName="CLUBS"),
	diamonds UMETA(DisplayName="DIAMONDS"),
	hearts UMETA(DisplayName="HEARTS"),
	spades UMETA(DisplayName="SPADES"),
	invalid UMETA(DisplayName="INVALID")
};

UCLASS(Blueprintable)
class TRASHCARDGAME_API UCardDeck : public UObject
{
    GENERATED_BODY()

public:
    UCardDeck();

    UPROPERTY(BlueprintReadOnly)
    TArray<UCard*> cards;
	
	const int numRanks {13};

private:

	const FString suits[4] = { "clubs", "diamonds", "hearts", "spades" };

    void initializeDeck();

public:
	UFUNCTION(BlueprintCallable)
	void startGame();
};
