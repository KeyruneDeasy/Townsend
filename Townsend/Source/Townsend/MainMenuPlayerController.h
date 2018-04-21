// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TownsendMainMenu.h"
#include "MainMenuPlayerController.generated.h"


UCLASS()
class TOWNSEND_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	AMainMenuPlayerController();

	void BeginPlay() override;
	
	TSubclassOf < UTownsendMainMenu > m_menuClass;
	UTownsendMainMenu* m_menu;
};
