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
	, m_minimumEnemySpawnInterval( 0.5f )
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
		ConstructorHelpers::FClassFinder<AActor> classFinder(TEXT("/Game/Blueprints/Enemies/StraightLineEnemy"));
		if (classFinder.Class != nullptr)
		{
			m_straightEnemyClass = classFinder.Class;
		}
	}

	{
		ConstructorHelpers::FClassFinder<AActor> classFinder(TEXT("/Game/Blueprints/Enemies/ShootingEnemy"));
		if (classFinder.Class != nullptr)
		{
			m_shootingEnemyClass = classFinder.Class;
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
		m_enemySpawnInterval -= 0.1f;

		SpawnEnemyWave();
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

void ATownsendGameModeBase::SpawnEnemyWave()
{
	m_waves.AddDefaulted( 1 );
	EnemyWave& wave = m_waves[m_waves.Num() - 1];

	float angle = 0.0f;
	if( ACylinderPawn* playerPawn = (ACylinderPawn*) UGameplayStatics::GetPlayerPawn( GetWorld(), 0 ) )
	{
		angle = playerPawn->GetOrbitAngle();
	}

	float angleOffset = PI / 2.f;
	int32 rand = FMath::RandRange( 0, 1 );
	if( rand == 1 ) { angleOffset *= -1.f; }
	wave.SetOriginAngle( angle + angleOffset );

	rand = FMath::RandRange( 0, ( (int) Wave_Count ) - 1 );

	switch( (Wave) rand )
	{
	case Wave_HomingEnemyLine:
	{
		SpawnWaveLine( wave, m_homingEnemyClass );
		break;
	}
	case Wave_HomingEnemyV:
	{
		SpawnWaveV( wave, m_homingEnemyClass );
		break;
	}
	case Wave_StraightEnemyLine:
	{
		SpawnWaveLine( wave, m_straightEnemyClass );
		break;
	}
	case Wave_StraightEnemyV:
	{
		SpawnWaveV( wave, m_straightEnemyClass );
		break;
	}
	case Wave_Diamond:
	{
		SpawnWaveDiamond( wave, m_homingEnemyClass, m_straightEnemyClass );
		break;
	}
	case Wave_Shooters:
	{
		SpawnWaveLineOfThree( wave, m_shootingEnemyClass );
		break;
	}
	}
}

void ATownsendGameModeBase::SpawnWaveLine( EnemyWave& wave, TSubclassOf<ACylinderPawn>& enemyClass )
{
	wave.AddSpawn( 0.0f, FVector2D( 0.0f, 100.0f ), enemyClass );
	wave.AddSpawn( 0.1f, FVector2D( 0.0f, 150.0f ), enemyClass );
	wave.AddSpawn( 0.2f, FVector2D( 0.0f, 200.0f ), enemyClass );
	wave.AddSpawn( 0.3f, FVector2D( 0.0f, 250.0f ), enemyClass );
	wave.AddSpawn( 0.4f, FVector2D( 0.0f, 300.0f ), enemyClass );
	wave.AddSpawn( 0.5f, FVector2D( 0.0f, 350.0f ), enemyClass );
	wave.AddSpawn( 0.6f, FVector2D( 0.0f, 400.0f ), enemyClass );
	wave.AddSpawn( 0.7f, FVector2D( 0.0f, 450.0f ), enemyClass );
	wave.AddSpawn( 0.8f, FVector2D( 0.0f, 500.0f ), enemyClass );
	wave.AddSpawn( 0.9f, FVector2D( 0.0f, 550.0f ), enemyClass );
}

void ATownsendGameModeBase::SpawnWaveV( EnemyWave& wave, TSubclassOf<ACylinderPawn>& enemyClass )
{
	wave.AddSpawn( 0.0f, FVector2D( -50.0f, 400.0f ), enemyClass );
	wave.AddSpawn( 0.2f, FVector2D( -25.0f, 430.0f ), enemyClass );
	wave.AddSpawn( 0.2f, FVector2D( -25.0f, 370.0f ), enemyClass );
	wave.AddSpawn( 0.4f, FVector2D(   0.0f, 460.0f ), enemyClass );
	wave.AddSpawn( 0.4f, FVector2D(   0.0f, 340.0f ), enemyClass );
	wave.AddSpawn( 0.6f, FVector2D(  25.0f, 490.0f ), enemyClass );
	wave.AddSpawn( 0.6f, FVector2D(  25.0f, 310.0f ), enemyClass );
	wave.AddSpawn( 0.8f, FVector2D(  50.0f, 520.0f ), enemyClass );
	wave.AddSpawn( 0.8f, FVector2D(  50.0f, 280.0f ), enemyClass );
	wave.AddSpawn( 1.0f, FVector2D(  75.0f, 550.0f ), enemyClass );
	wave.AddSpawn( 1.0f, FVector2D(  75.0f, 250.0f ), enemyClass );
}

void ATownsendGameModeBase::SpawnWaveDiamond( EnemyWave& wave, TSubclassOf<ACylinderPawn>& outerClass, TSubclassOf<ACylinderPawn>& innerClass )
{
	wave.AddSpawn( 0.0f, FVector2D( -300.0f, 400.0f ), outerClass );
	wave.AddSpawn( 0.0f, FVector2D( -200.0f, 460.0f ), outerClass );
	wave.AddSpawn( 0.0f, FVector2D( -200.0f, 340.0f ), outerClass );
	wave.AddSpawn( 0.0f, FVector2D( -100.0f, 520.0f ), outerClass );
	wave.AddSpawn( 0.0f, FVector2D( -100.0f, 280.0f ), outerClass );
	wave.AddSpawn( 0.0f, FVector2D(    0.0f, 580.0f ), outerClass );
	wave.AddSpawn( 0.0f, FVector2D(    0.0f, 220.0f ), outerClass );
	wave.AddSpawn( 0.0f, FVector2D(  100.0f, 520.0f ), outerClass );
	wave.AddSpawn( 0.0f, FVector2D(  100.0f, 280.0f ), outerClass );
	wave.AddSpawn( 0.0f, FVector2D(  200.0f, 460.0f ), outerClass );
	wave.AddSpawn( 0.0f, FVector2D(  200.0f, 340.0f ), outerClass );
	wave.AddSpawn( 0.0f, FVector2D(  300.0f, 400.0f ), outerClass );
	wave.AddSpawn( 0.0f, FVector2D(    0.0f, 400.0f ), innerClass );
}

void ATownsendGameModeBase::SpawnWaveLineOfThree( EnemyWave& wave, TSubclassOf<ACylinderPawn>& enemyClass )
{
	wave.AddSpawn( 0.0f, FVector2D( 0.0f, 200.0f ), enemyClass );
	wave.AddSpawn( 0.0f, FVector2D( 0.0f, 400.0f ), enemyClass );
	wave.AddSpawn( 0.0f, FVector2D( 0.0f, 600.0f ), enemyClass );
}


