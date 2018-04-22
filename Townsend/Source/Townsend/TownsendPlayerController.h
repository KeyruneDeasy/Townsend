// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TownsendHUD.h"
#include "PauseMenu.h"
#include "TownsendPlayerController.generated.h"

class UTownsendHUD;

UCLASS()
class TOWNSEND_API ATownsendPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATownsendPlayerController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void TogglePause();

private:
	TSubclassOf < UTownsendHUD > m_hudClass;
	UTownsendHUD* m_hud;

	TSubclassOf < UPauseMenu > m_pauseMenuClass;
	UPauseMenu* m_pauseMenu;
};
