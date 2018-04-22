// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TownsendSaveGame.generated.h"


UCLASS()
class TOWNSEND_API UTownsendSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	static UTownsendSaveGame* LoadOrCreate();

private:
	enum SaveVersion
	{
		Version_1,

		Version_Current
	};

	static const uint32 s_numScoresToSave = 10;
	static const uint32 s_userId = 0;
	static const char* s_saveSlotName;
	
public:
	UTownsendSaveGame();

	int32 GetNewHighScoreRanking( uint32 score );
	void AddNewHighScore( FString name, uint32 score );

	void Save();

	FString GetName( int index ) { return m_names[index]; }
	uint32 GetScore( int index ) { return m_scores[index]; }
	
private:
	UPROPERTY(VisibleAnywhere)
	FString m_names[s_numScoresToSave];

	UPROPERTY(VisibleAnywhere)
	uint32 m_scores[s_numScoresToSave];
};
