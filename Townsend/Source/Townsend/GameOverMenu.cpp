// Fill out your copyright notice in the Description page of Project Settings.

#include "GameOverMenu.h"
#include "TownsendPlayerState.h"
#include "Kismet/GameplayStatics.h"

FText UGameOverMenu::GetScore()
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

void UGameOverMenu::ReturnToMainMenu()
{
	UGameplayStatics::OpenLevel( GetWorld(), "Townsend_MainMenu" );
}
