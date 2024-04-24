// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"

UCard::UCard()
{
    if (Rank == 11)
    {
        IsWild = true;
    }
    else
    {
        IsWild = false;
    }
}

FString& UCard::GetDisplayName()
{
    if (DisplayName != "")
    {
        return DisplayName;
    } 
    else 
    {
        DisplayName = FString::Printf(TEXT("%i of %s"), Rank, *Suit);
        return DisplayName;
    }
}
