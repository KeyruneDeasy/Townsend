// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemySpawn.h"

EnemySpawn::EnemySpawn( float time, FVector2D relativePosition, TSubclassOf<ACylinderPawn> enemyClass )
	: m_time( time )
	, m_class( enemyClass )
	, m_relativePosition( relativePosition )
{
}

EnemySpawn::~EnemySpawn()
{
}
