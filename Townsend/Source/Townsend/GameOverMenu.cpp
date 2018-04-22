// Fill out your copyright notice in the Description page of Project Settings.

#include "GameOverMenu.h"
#include "TownsendPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "TownsendSaveGame.h"
#include "Blueprint/WidgetTree.h"
#include "Components/EditableTextBox.h"

UGameOverMenu::UGameOverMenu( const FObjectInitializer& init )
	: Super( init )
	, m_gotHighScoreRank( false )
{
}

bool UGameOverMenu::Initialize()
{
	bool val = Super::Initialize();
	m_savegame = UTownsendSaveGame::LoadOrCreate();
	return val;
}

FText UGameOverMenu::GetScoreText()
{
	int score = GetScore();
	FString str = FString::FromInt( score );
	return FText::FromString( str );
}

FText UGameOverMenu::GetHighScoreRankText()
{
	int32 highScoreRank = GetHighScoreRank();
	FString rankStr;
	if( highScoreRank == -1 )
	{
		return FText::FromString( "" );
	}
	if( highScoreRank == 0 )
	{
		rankStr = "1st";
	}
	else if( highScoreRank == 1 )
	{
		rankStr = "2nd";
	}
	else if( highScoreRank == 2 )
	{
		rankStr = "3rd";
	}
	else
	{
		rankStr = FString::FromInt( highScoreRank + 1 ) + "th";
	}
	return FText::FromString( "New High Score, Rank " + rankStr + "!" );
}

ESlateVisibility UGameOverMenu::GetHighScoreRankVisibility()
{
	return ( GetHighScoreRank() != -1 ) ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
}

void UGameOverMenu::ReturnToMainMenu()
{
	SaveHighScore();
	UGameplayStatics::OpenLevel( GetWorld(), "Townsend_MainMenu" );
}

int UGameOverMenu::GetScore()
{
	float scoreF = 0.0f;
	if( APlayerState* playerState = GetOwningPlayerState() )
	{
		scoreF = playerState->Score;
	}
	return (int) scoreF;
}

int32 UGameOverMenu::GetHighScoreRank()
{
	if( !m_gotHighScoreRank )
	{
		m_highScoreRank = m_savegame->GetNewHighScoreRanking( GetScore() );
		m_gotHighScoreRank = true;
	}
	return m_highScoreRank;
}

void UGameOverMenu::SaveHighScore()
{
	FString highScoreName = GetHighScoreNameFromTextBox();
	int highScore = GetScore();
	m_savegame->AddNewHighScore( highScoreName, highScore );
	m_savegame->Save();
}

FString UGameOverMenu::GetHighScoreNameFromTextBox()
{
	UEditableTextBox* textBox = (UEditableTextBox*) WidgetTree->FindWidget( "HighscoreNameTextBox" );
	if( textBox )
	{
		return textBox->GetText().ToString();
	}
	return "";
}
