// Fill out your copyright notice in the Description page of Project Settings.

#include "TownsendMainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

UTownsendMainMenu::UTownsendMainMenu( const FObjectInitializer& init )
	: Super( init )
{
	// Create the highscore submenu
	ConstructorHelpers::FClassFinder<UUserWidget> classFinder(TEXT("/Game/Blueprints/HighScoreMenu"));
	if (classFinder.Class != nullptr)
	{
		m_highScoreMenuClass = classFinder.Class;
	}
}

void UTownsendMainMenu::StartGame()
{
	HideMouseCursor();
	UGameplayStatics::OpenLevel( GetWorld(), "Townsend_Level01" );
}

void UTownsendMainMenu::GoToHighScores()
{
	SetVisibility( ESlateVisibility::Hidden );
	if( !m_highScoreMenu )
	{
		m_highScoreMenu = CreateWidget<UHighScoreMenu>( GetOwningPlayer(), m_highScoreMenuClass );

		if( m_highScoreMenu )
		{
			m_highScoreMenu->AddToViewport(10000);
			m_highScoreMenu->SetMainMenu( this );
		}
	}
	if( m_highScoreMenu )
	{
		m_highScoreMenu->Activate();
	}
}

void UTownsendMainMenu::QuitGame()
{
	FGenericPlatformMisc::RequestExit(false  );
}

void UTownsendMainMenu::HideMouseCursor()
{
	if( APlayerController* controller = GetOwningPlayer() )
	{
		controller->bShowMouseCursor = false;
	}
}


