// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverMenu.generated.h"

class UTownsendSaveGame;

UCLASS()
class TOWNSEND_API UGameOverMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UGameOverMenu( const FObjectInitializer& init );

	virtual bool Initialize() override;
	
protected:
	UFUNCTION(BlueprintGetter)
	FText GetScoreText();

	UFUNCTION(BlueprintGetter)
	FText GetHighScoreRankText();

	UFUNCTION(BlueprintGetter)
	ESlateVisibility GetHighScoreRankVisibility();

	UFUNCTION(BlueprintCallable)
	void ReturnToMainMenu();

private:
	UPROPERTY()
	UTownsendSaveGame* m_savegame;
	bool m_gotHighScoreRank;
	int32 m_highScoreRank;

	int GetScore();
	int32 GetHighScoreRank();

	void SaveHighScore();
	FString GetHighScoreNameFromTextBox();
};
