// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"

UCard::UCard()
{
    
}

FString& UCard::GetDisplayName()
{
    if (DisplayName != "")
    {
        return DisplayName;
    } 
    else 
    {
        DisplayName = FString::Printf(TEXT("%s of %s"), *GetRankDisplayName(), *Suit);
        return DisplayName;
    }
}

FString& UCard::GetRankDisplayName()
{
    switch (Rank)
    {
        case 1:
            RankDisplayName = FString(TEXT("A"));
            break;
        case 11:
            RankDisplayName = FString(TEXT("J"));
            break;
        case 12:
            RankDisplayName = FString(TEXT("Q"));
            break;
        case 13:
            RankDisplayName = FString(TEXT("K"));
            break;
        default:
            RankDisplayName = FString::FromInt(Rank);
            break;
    }

    return RankDisplayName;
}
