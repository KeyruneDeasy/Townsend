// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyWave.h"

EnemyWave::EnemyWave()
	: m_time( 0.0f )
{
}

EnemyWave::~EnemyWave()
{
}

void EnemyWave::Tick( float dt, UWorld* world )
{
	float timeBefore = m_time;
	m_time += dt;
	for( EnemySpawn& spawn : m_spawns )
	{
		if( timeBefore <= spawn.GetTime() && m_time > spawn.GetTime() )
		{
			ACylinderPawn* enemy = (ACylinderPawn*) world->SpawnActor( spawn.GetEnemyClass() );
			float angle = m_originAngle - spawn.GetPosition().X * enemy->GetOrbitDistance();
			enemy->SetLocation( angle, spawn.GetPosition().Y );
		}
	}
}

void EnemyWave::AddSpawn( float time, FVector2D relativePosition, TSubclassOf<ACylinderPawn> enemyClass )
{
	EnemySpawn wave( time, relativePosition, enemyClass );
	m_spawns.Add( wave );
}

bool EnemyWave::IsFinished()
{
	float latestSpawn = 0.0f;
	for( EnemySpawn& spawn : m_spawns )
	{
		if( spawn.GetTime() > latestSpawn ) { latestSpawn = spawn.GetTime(); }
	}
	return m_time > latestSpawn;
}
