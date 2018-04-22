// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

AMainMenuPlayerController::AMainMenuPlayerController()
{
	ConstructorHelpers::FClassFinder<UUserWidget> classFinder(TEXT("/Game/Blueprints/MainMenu"));
	if (classFinder.Class != nullptr)
	{
		m_menuClass = classFinder.Class;
	}
}

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	m_menu = CreateWidget<UTownsendMainMenu>(this, m_menuClass);

	if( m_menu )
	{
		m_menu->AddToViewport(9999); // Massive render-Z to make it render at the front.
	}
	bShowMouseCursor = true; 
	bEnableClickEvents = true; 
	bEnableMouseOverEvents = true;
}

