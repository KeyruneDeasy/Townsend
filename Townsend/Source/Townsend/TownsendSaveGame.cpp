// Fill out your copyright notice in the Description page of Project Settings.

#include "TownsendSaveGame.h"
#include "Kismet/GameplayStatics.h"

const char* UTownsendSaveGame::s_saveSlotName = "TownsendHighScores";

UTownsendSaveGame::UTownsendSaveGame()
{
	m_names[0] = "Ciaran";
	m_names[1] = "Chris";
	m_names[2] = "Leo";
	m_names[3] = "Johno";
	m_names[4] = "Dom";
	m_names[5] = "Ellie";
	m_names[6] = "Vivian";
	m_names[7] = "Karl";
	m_names[8] = "Blush";
	m_names[9] = "Sparkzy";

	m_scores[0] = 1000;
	m_scores[1] = 900;
	m_scores[2] = 800;
	m_scores[3] = 700;
	m_scores[4] = 600;
	m_scores[5] = 500;
	m_scores[6] = 400;
	m_scores[7] = 300;
	m_scores[8] = 200;
	m_scores[9] = 100;
}

int32 UTownsendSaveGame::GetNewHighScoreRanking( uint32 newScore )
{
	for( uint32 i = 0; i < s_numScoresToSave; ++i )
	{
		if( m_scores[i] < newScore )
		{
			return i;
		}
	}
	// Didn't make the highscore board.
	return -1;
}

void UTownsendSaveGame::AddNewHighScore( FString name, uint32 score )
{
	int32 rank = GetNewHighScoreRanking( score );
	if( rank != -1 )
	{
		// Move the lower scores down
		for( uint32 i = s_numScoresToSave - 1; i > (uint32) rank; --i )
		{
			m_names[i] = m_names[i - 1];
			m_scores[i] = m_scores[i - 1];
		}
		// And insert the new score
		m_names[rank] = name;
		m_scores[rank] = score;
	}
}

UTownsendSaveGame* UTownsendSaveGame::LoadOrCreate()
{
	UTownsendSaveGame* savegame = Cast<UTownsendSaveGame>( UGameplayStatics::LoadGameFromSlot( s_saveSlotName, s_userId ) );
	if( !savegame )
	{
		savegame = Cast<UTownsendSaveGame>( UGameplayStatics::CreateSaveGameObject( UTownsendSaveGame::StaticClass() ) );
	}
	return savegame;
}

void UTownsendSaveGame::Save()
{
	UGameplayStatics::SaveGameToSlot( this, s_saveSlotName, s_userId );
}

