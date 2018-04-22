// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CylinderPawn.h"
#include "CollisionManager.h"
#include "GameOverMenu.h"
#include "EnemyWave.h"
#include "TownsendGameModeBase.generated.h"

class UGameOverMenu;

UCLASS()
class TOWNSEND_API ATownsendGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	enum Wave
	{
		Wave_HomingEnemyLine,
		Wave_HomingEnemyV,
		Wave_StraightEnemyLine,
		Wave_StraightEnemyV,
		Wave_Diamond,

		Wave_Count
	};

	static ATownsendGameModeBase* GetFrom( UWorld* world );

	ATownsendGameModeBase();

	virtual void Tick(float DeltaTime) override;

	float GetOrbitDistance() { return m_orbitDistance; }
	float GetCylinderMinZ() { return m_cylinderMinZ; }
	float GetCylinderMaxZ() { return m_cylinderMaxZ; }

	uint32 GetCurrentLives() { return m_currentLives; }
	void GainLife() { ++m_currentLives; }
	void LoseLife() { --m_currentLives; }

	CollisionManager& GetCollisionManager() { return m_collisionManager; }

	void EndGame();
	bool GameOver() { return m_gameOver; }

private:

	float m_orbitDistance;
	float m_cylinderMinZ;
	float m_cylinderMaxZ;

	float m_enemySpawnInterval;
	float m_nextEnemySpawnTime;
	TSubclassOf < ACylinderPawn > m_homingEnemyClass;
	TSubclassOf < ACylinderPawn > m_straightEnemyClass;

	uint16 m_currentLives;
	bool m_gameOver;
	TSubclassOf < UGameOverMenu > m_gameOverMenuClass;
	UGameOverMenu* m_gameOverMenu;

	CollisionManager m_collisionManager;

	TArray< EnemyWave > m_waves;

	void SpawnEnemyWave();

	void SpawnWaveLine( EnemyWave& wave, TSubclassOf<ACylinderPawn>& enemyClass );
	void SpawnWaveV( EnemyWave& wave, TSubclassOf<ACylinderPawn>& enemyClass );
	void SpawnWaveDiamond( EnemyWave& wave, TSubclassOf<ACylinderPawn>& outerClass, TSubclassOf<ACylinderPawn>& innerClass );
};
