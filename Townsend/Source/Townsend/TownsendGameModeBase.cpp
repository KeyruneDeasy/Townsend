// Fill out your copyright notice in the Description page of Project Settings.

#include "TownsendGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

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
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<AActor> enemyClassFinder(TEXT("/Game/Blueprints/Enemies/HomingEnemy"));
	if (enemyClassFinder.Class != nullptr)
	{
		m_enemyClass = enemyClassFinder.Class;
	}
}

void ATownsendGameModeBase::Tick( float DeltaTime )
{
	float time = GetGameTimeSinceCreation();

	if( time > m_nextEnemySpawnTime )
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


