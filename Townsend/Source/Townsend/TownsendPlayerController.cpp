// Fill out your copyright notice in the Description page of Project Settings.

#include "TownsendPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "TownsendGameModeBase.h"

#define INPUT_ACTION_PAUSE "Pause"

ATownsendPlayerController::ATownsendPlayerController()
{
	{
		ConstructorHelpers::FClassFinder<UUserWidget> classFinder( TEXT( "/Game/Blueprints/HUD" ) );
		if( classFinder.Class != nullptr )
		{
			m_hudClass = classFinder.Class;
		}
	}
	{
		ConstructorHelpers::FClassFinder<UUserWidget> classFinder( TEXT( "/Game/Blueprints/PauseMenu" ) );
		if( classFinder.Class != nullptr )
		{
			m_pauseMenuClass = classFinder.Class;
		}
	}
}

void ATownsendPlayerController::BeginPlay()
{
	Super::BeginPlay();

	m_hud = CreateWidget<UTownsendHUD>( this, m_hudClass );

	if( m_hud )
	{
		m_hud->AddToViewport(9999); // Massive render-Z to make it render at the front.
	}
}

void ATownsendPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	FInputActionBinding& pauseAction = InputComponent->BindAction( INPUT_ACTION_PAUSE, EInputEvent::IE_Pressed, this, &ATownsendPlayerController::TogglePause );
	pauseAction.bExecuteWhenPaused = true; // So we can unpause!
}

void ATownsendPlayerController::TogglePause()
{
	if( ATownsendGameModeBase* gameMode = ATownsendGameModeBase::GetFrom( GetWorld() ) )
	{
		if( gameMode->GameOver() && !IsPaused() )
		{
			// Don't pause if the game is over.
			return;
		}
	}

	SetPause( !IsPaused() );

	if( IsPaused() )
	{
		// Show or create the pause menu.
		if( m_pauseMenu )
		{
			m_pauseMenu->SetVisibility( ESlateVisibility::Visible );
		}
		else
		{
			m_pauseMenu = CreateWidget<UPauseMenu>( this, m_pauseMenuClass );

			if( m_pauseMenu )
			{
				m_pauseMenu->AddToViewport( 10001 );
			}
		}
		bShowMouseCursor = true;
	}
	else
	{
		// Hide the pause menu.
		if( m_pauseMenu )
		{
			m_pauseMenu->SetVisibility( ESlateVisibility::Hidden );
		}
		bShowMouseCursor = false;
	}
}


