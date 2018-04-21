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
			m_enemyClass = classFinder.Class;
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

	if( time > m_nextEnemySpawnTime && !m_gameOver )
	{
		m_nextEnemySpawnTime += m_enemySpawnInterval;
		ACylinderPawn* enemy = (ACylinderPawn*) GetWorld()->SpawnActor( m_enemyClass );
		if( ACylinderPawn* playerPawn = (ACylinderPawn*) UGameplayStatics::GetPlayerPawn( GetWorld(), 0 ) )
		{
			FVector playerLoc = playerPawn->GetActorLocation();
			float angle = playerPawn->GetOrbitAngle();
			if( (int) time % 10 == 0 )
			{
				angle += PI / 2;
			}
			else
			{
				angle -= PI / 2;
			}
			enemy->SetLocation( angle, playerLoc.Z );
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


