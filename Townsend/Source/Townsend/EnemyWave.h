// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySpawn.h"

class TOWNSEND_API EnemyWave
{
public:
	EnemyWave();
	~EnemyWave();

	void Tick( float dt, UWorld* world );
	void AddSpawn( float time, FVector2D relativePosition, TSubclassOf<ACylinderPawn> enemyClass );
	bool IsFinished();
	void SetOriginAngle( float angle ) { m_originAngle = angle; }

private:
	TArray<EnemySpawn> m_spawns;
	float m_time;

	float m_originAngle;
};
