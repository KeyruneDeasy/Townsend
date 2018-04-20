// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TownsendHUD.h"
#include "TownsendPlayerController.generated.h"

class UTownsendHUD;

UCLASS()
class TOWNSEND_API ATownsendPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATownsendPlayerController();

	void BeginPlay() override;

private:
	TSubclassOf < UTownsendHUD > hudClass;
	UTownsendHUD* m_hud;
};
