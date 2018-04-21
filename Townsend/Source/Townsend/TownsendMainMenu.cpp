// Fill out your copyright notice in the Description page of Project Settings.

#include "TownsendMainMenu.h"
#include "Kismet/GameplayStatics.h"

void UTownsendMainMenu::StartGame()
{
	UGameplayStatics::OpenLevel( GetWorld(), "Townsend_Level01" );
}


