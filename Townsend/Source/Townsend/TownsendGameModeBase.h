// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CylinderPawn.h"
#include "CollisionManager.h"
#include "TownsendGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOWNSEND_API ATownsendGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	static ATownsendGameModeBase* GetFrom( UWorld* world );

	ATownsendGameModeBase();

	virtual void Tick(float DeltaTime) override;

	float GetOrbitDistance() { return m_orbitDistance; }
	float GetCylinderMinZ() { return m_cylinderMinZ; }
	float GetCylinderMaxZ() { return m_cylinderMaxZ; }

	CollisionManager& GetCollisionManager() { return m_collisionManager; }

private:

	float m_orbitDistance;
	float m_cylinderMinZ;
	float m_cylinderMaxZ;

	float m_enemySpawnInterval;
	float m_nextEnemySpawnTime;
	TSubclassOf < ACylinderPawn > m_enemyClass;

	CollisionManager m_collisionManager;
};
