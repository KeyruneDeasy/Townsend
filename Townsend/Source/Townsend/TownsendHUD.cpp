// Fill out your copyright notice in the Description page of Project Settings.

#include "TownsendHUD.h"
#include "TownsendPlayerState.h"

FText UTownsendHUD::GetRespawnTime()
{
	float respawnTime = 0.0f;
	if( ATownsendPlayerState* playerState = (ATownsendPlayerState*) GetOwningPlayerState() )
	{
		respawnTime = playerState->GetRespawnTime();
	}
	int count = (int) respawnTime + 1; // +1 so it rounds up rather than down.
	FString str1( "Respawning in " );
	FString str2 = FString::FromInt( count );
	return FText::FromString( str1 + str2 );
}

ESlateVisibility UTownsendHUD::GetRespawnTimerVisibility()
{
	// Show the timer while the player is dead.
	if( ATownsendPlayerState* playerState = (ATownsendPlayerState*) GetOwningPlayerState() )
	{
		return playerState->IsDead() ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	}
	return ESlateVisibility::Hidden;
}

FText UTownsendHUD::GetScore()
{
	float scoreF = 0.0f;
	if( APlayerState* playerState = GetOwningPlayerState() )
	{
		scoreF = playerState->Score;
	}
	int score = (int) scoreF;
	FString str = FString::FromInt( score );
	return FText::FromString( str );
}


