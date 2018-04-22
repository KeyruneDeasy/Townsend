// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CylinderPawn.h"


class TOWNSEND_API EnemySpawn
{
public:
	EnemySpawn( float time, FVector2D relativePosition, TSubclassOf<ACylinderPawn> enemyClass );
	~EnemySpawn();

	float GetTime() { return m_time; }
	FVector2D GetPosition() { return m_relativePosition; }
	TSubclassOf<ACylinderPawn>& GetEnemyClass() { return m_class; }

private:
	float m_time;
	FVector2D m_relativePosition;
	TSubclassOf<ACylinderPawn> m_class;
};
