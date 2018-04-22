// Fill out your copyright notice in the Description page of Project Settings.

#include "PauseMenu.h"
#include "TownsendPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UPauseMenu::ResumeGame()
{
	if( ATownsendPlayerController* playerController = (ATownsendPlayerController*) GetOwningPlayer() )
	{
		playerController->TogglePause();
	}
}

void UPauseMenu::ReturnToMenu()
{
	UGameplayStatics::OpenLevel( GetWorld(), "Townsend_MainMenu" );
}
