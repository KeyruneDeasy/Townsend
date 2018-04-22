// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HighScoreMenu.h"
#include "TownsendMainMenu.generated.h"


UCLASS()
class TOWNSEND_API UTownsendMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UTownsendMainMenu( const FObjectInitializer& init );

protected:
	UFUNCTION(BlueprintCallable)
	void StartGame();
	UFUNCTION(BlueprintCallable)
	void GoToHighScores();

	TSubclassOf < UHighScoreMenu > m_highScoreMenuClass;
	UHighScoreMenu* m_highScoreMenu;
};
