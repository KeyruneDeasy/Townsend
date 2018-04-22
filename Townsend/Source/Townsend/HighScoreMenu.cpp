// Fill out your copyright notice in the Description page of Project Settings.

#include "HighScoreMenu.h"
#include "TownsendSaveGame.h"
#include "TownsendMainMenu.h"

UHighScoreMenu::UHighScoreMenu( const FObjectInitializer& init )
	: Super( init )
{
	Deactivate();
}

void UHighScoreMenu::Activate()
{
	m_savegame = UTownsendSaveGame::LoadOrCreate();
	SetIsEnabled( true );
	SetVisibility( ESlateVisibility::Visible );
}

void UHighScoreMenu::Deactivate()
{
	if( m_savegame )
	{
		m_savegame = NULL;
	}
	SetIsEnabled( false );
	SetVisibility( ESlateVisibility::Hidden );
}

FText UHighScoreMenu::GetNameText( int rank )
{
	if( m_savegame )
	{
		return FText::FromString( m_savegame->GetName( rank - 1 ) );
	}
	else
	{
		return FText::FromString( "" );
	}
}

FText UHighScoreMenu::GetScoreText( int rank )
{
	if( m_savegame )
	{
		return FText::FromString( FString::FromInt( m_savegame->GetScore( rank - 1 ) ) );
	}
	else
	{
		return FText::FromString( "" );
	}
}

void UHighScoreMenu::ReturnToMainMenu()
{
	Deactivate();
	if( m_mainMenu )
	{
		m_mainMenu->SetVisibility( ESlateVisibility::Visible );
	}
}

