// Fill out your copyright notice in the Description page of Project Settings.

#include "TownsendGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "TownsendPlayerState.h"
#include "TownsendPlayerController.h"

ATownsendGameModeBase* ATownsendGameModeBase::GetFrom( UWorld* world )
{
	return world ? (ATownsendGameModeBase*) world->GetAuthGameMode() : NULL;
}

ATownsendGameModeBase::ATownsendGameModeBase()
	: m_orbitDistance( 500.0f )
	, m_cylinderMinZ( 100.0f )
	, m_cylinderMaxZ( 700.0f )
	, m_enemySpawnInterval( 5.0f )
	, m_nextEnemySpawnTime( 5.0f )
	, m_currentLives( 2 )
{
	PlayerStateClass = ATownsendPlayerState::StaticClass();
	PlayerControllerClass = ATownsendPlayerController::StaticClass();

	PrimaryActorTick.bCanEverTick = true;

	{
		ConstructorHelpers::FClassFinder<AActor> classFinder(TEXT("/Game/Blueprints/Enemies/HomingEnemy"));
		if (classFinder.Class != nullptr)
		{
			m_homingEnemyClass = classFinder.Class;
		}
	}

	{
		ConstructorHelpers::FClassFinder<UGameOverMenu> classFinder(TEXT("/Game/Blueprints/GameOverMenu"));
		if (classFinder.Class != nullptr)
		{
			m_gameOverMenuClass = classFinder.Class;
		}
	}
}

void ATownsendGameModeBase::Tick( float DeltaTime )
{
	float time = GetGameTimeSinceCreation();

	for( int32 i = 0; i < m_waves.Num(); ++i )
	{
		EnemyWave& wave = m_waves[i];
		wave.Tick( DeltaTime, GetWorld() );
		if( wave.IsFinished() )
		{
			m_waves.RemoveAtSwap( i );
			--i;
		}
	}

	if( time > m_nextEnemySpawnTime && !m_gameOver )
	{
		m_nextEnemySpawnTime += m_enemySpawnInterval;

		if( ACylinderPawn* playerPawn = (ACylinderPawn*) UGameplayStatics::GetPlayerPawn( GetWorld(), 0 ) )
		{
			float angle = playerPawn->GetOrbitAngle();

			SpawnHomingEnemyWave1( angle );
		}
	}

	m_collisionManager.CheckCollisions();
}

void ATownsendGameModeBase::EndGame()
{
	m_gameOver = true;
	if( !m_gameOverMenu )
	{
		if( APlayerController* controller = UGameplayStatics::GetPlayerController( GetWorld(), 0 ) )
		{
			m_gameOverMenu = CreateWidget<UGameOverMenu>( controller, m_gameOverMenuClass );
			if( m_gameOverMenu )
			{
				m_gameOverMenu->AddToViewport( 10000 );
			}
			controller->bShowMouseCursor = true; 
			controller->bEnableClickEvents = true; 
			controller->bEnableMouseOverEvents = true;
		}
	}
}

void ATownsendGameModeBase::SpawnHomingEnemyWave1( float playerAngle )
{
	m_waves.AddDefaulted( 1 );
	EnemyWave& wave = m_waves[m_waves.Num() - 1];
	wave.SetOriginAngle( playerAngle + PI / 2.f );

	wave.AddSpawn( 0.0f, FVector2D( 0.0f, 100.0f ), m_homingEnemyClass );
	wave.AddSpawn( 0.2f, FVector2D( 0.0f, 200.0f ), m_homingEnemyClass );
	wave.AddSpawn( 0.4f, FVector2D( 0.0f, 300.0f ), m_homingEnemyClass );
	wave.AddSpawn( 0.6f, FVector2D( 0.0f, 400.0f ), m_homingEnemyClass );
	wave.AddSpawn( 0.8f, FVector2D( 0.0f, 500.0f ), m_homingEnemyClass );
}


