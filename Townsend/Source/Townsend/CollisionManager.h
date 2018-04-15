// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UCollisionComponent;

UENUM()
enum class CollisionType : uint8
{
	Collision_Player,
	Collision_Enemy,

	Collision_Max
};

class TOWNSEND_API CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void RegisterCollisionComponent( UCollisionComponent* component, CollisionType type );
	void UnregisterCollisionComponent( UCollisionComponent* component, CollisionType type );

	void CheckCollisions();
	
private:
	UCollisionComponent* m_player;
	TArray< UCollisionComponent* > m_enemies;
};
