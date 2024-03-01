// // Fill out your copyright notice in the Description page of Project Settings.


// #include "CardDeck.h"
// #include "Card.h"

// UCardDeck::UCardDeck()
// {
// 	for (int i = 0; i < num_ranks; i++) 
// 	{
// 		// iterate over all suits in Suit enum
// 		for (int suitValue = static_cast<int>(UCard::Suit::clubs); suitValue <= static_cast<int>(UCard::Suit::spades); ++suitValue)
// 		{
// 			UCard card{};
// 			cards.Add(card);
// 		}
// 	}

// 	UE_LOG(LogTemp, Log, TEXT("Number of cards in deck: %i"), cards.Num());
// }


#include "CardDeck.h"
#include "Card.h"
#include "UObject/Class.h"

UCardDeck::UCardDeck()
{
    initializeDeck();
}

void UCardDeck::initializeDeck()
{
	UE_LOG(LogTemp, Log, TEXT("Initializing the deck..."));
    // 52 card standard deck
    // FString Ranks[] = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };

    // for (uint8 suitValue = static_cast<uint8>(Suit::clubs); suitValue <= static_cast<uint8>(Suit::spades); ++suitValue)
	for (const FString& suit : suits)
    {
        for (int i = 1; i <= numRanks; ++i)
        {
            UCard* NewCard = CreateDefaultSubobject<UCard>(*FString::Printf(TEXT("Card: %d of %s"), i, *suit));
			if (NewCard) 
			{
				NewCard->Rank = i;
				NewCard->Suit = suit;
			}
			// NewCard->Suit = "Spades";
            cards.Add(NewCard);
        }
    }
}

void UCardDeck::startGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Starting the game!"));
}

