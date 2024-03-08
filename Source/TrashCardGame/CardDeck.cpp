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

}

UCardDeck* UCardDeck::InitializeDeck()
{
	UE_LOG(LogTemp, Log, TEXT("Initializing the deck..."));

    UCardDeck* NewDeck = NewObject<UCardDeck>();
    if (NewDeck)
    {
        for (const FString& suit : NewDeck->suits)
        {
            for (int i = 1; i <= NewDeck->numRanks; ++i)
            {
                UCard* NewCard = NewObject<UCard>(NewDeck, *FString::Printf(TEXT("Card: %d of %s"), i, *suit));
        		if (NewCard)
        		{
        			NewCard->Rank = i;
        			NewCard->Suit = suit;
                    NewDeck->cardDeck.Add(NewCard);
        		}
            }
        }
        UE_LOG(LogTemp, Warning, TEXT("Num cards in deck: %i"), NewDeck->cardDeck.Num());
    }

    return NewDeck;
}

void UCardDeck::startGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Starting the game!"));
}

