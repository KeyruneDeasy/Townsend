// Fill out your copyright notice in the Description page of Project Settings.

#include "TownsendPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

ATownsendPlayerController::ATownsendPlayerController()
{
	ConstructorHelpers::FClassFinder<UUserWidget> classFinder(TEXT("/Game/Blueprints/HUD"));
	if (classFinder.Class != nullptr)
	{
		hudClass = classFinder.Class;
	}
}

void ATownsendPlayerController::BeginPlay()
{
	Super::BeginPlay();

	m_hud = CreateWidget<UTownsendHUD>(this, hudClass);

	if( m_hud )
	{
		m_hud->AddToViewport(9999); // Massive render-Z to make it render at the front.
	}
}


