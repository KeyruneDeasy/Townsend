// Fill out your copyright notice in the Description page of Project Settings.

#include "TownsendPlayerState.h"
#include "TownsendGameModeBase.h"

float ATownsendPlayerState::s_respawnTime = 3.0f;
float ATownsendPlayerState::s_invulnerabilityTimeAfterRespawn = 2.0f;

ATownsendPlayerState::ATownsendPlayerState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATownsendPlayerState::Tick( float DeltaTime )
{
	if( IsDead() )
	{
		m_respawnTimer -= DeltaTime;
		if( m_respawnTimer <= 0.0f )
		{
			if( ATownsendGameModeBase* gameMode = ATownsendGameModeBase::GetFrom( GetWorld() ) )
			{
				if( gameMode->GetCurrentLives() > 0 )
				{
					gameMode->LoseLife();
					Respawn();
				}
				else
				{
					gameMode->EndGame();
				}
			}
		}
	}
	else
	{
		if( m_invulnerabilityTimer > 0.0f )
		{
			m_invulnerabilityTimer -= DeltaTime;
		}
	}
}

void ATownsendPlayerState::Kill()
{
	if( IsDead() ) { return; } // You cannot slay that which hath already been slain
	if( IsInvulnerable() ) { return; } // HAHA YOU CAN'T TOUCH ME LOSERS

	m_respawnTimer = s_respawnTime;
}

void ATownsendPlayerState::Respawn()
{
	m_invulnerabilityTimer = s_invulnerabilityTimeAfterRespawn;
}
