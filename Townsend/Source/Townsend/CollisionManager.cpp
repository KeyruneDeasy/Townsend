// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionManager.h"
#include "CollisionComponent.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::RegisterCollisionComponent( UCollisionComponent* component, CollisionType type )
{
	switch( type )
	{
	case CollisionType::Collision_Player:
	{
		m_player = component;
		break;
	}
	case CollisionType::Collision_Enemy:
	{
		m_enemies.Add( component );
		break;
	}
	case CollisionType::Collision_PlayerBullet:
	{
		m_playerBullets.Add( component );
		break;
	}
	case CollisionType::Collision_EnemyBullet:
	{
		m_enemyBullets.Add( component );
		break;
	}
	}
}

void CollisionManager::UnregisterCollisionComponent( UCollisionComponent* component, CollisionType type )
{
	switch( type )
	{
	case CollisionType::Collision_Player:
	{
		if( m_player == component )
		{
			m_player = NULL;
		}
		break;
	}
	case CollisionType::Collision_Enemy:
	{
		m_enemies.Remove( component );
		break;
	}
	case CollisionType::Collision_PlayerBullet:
	{
		m_playerBullets.Remove( component );
		break;
	}
	case CollisionType::Collision_EnemyBullet:
	{
		m_enemyBullets.Remove( component );
		break;
	}
	}
}

void CollisionManager::CheckCollisions()
{
	bool playerHit = false;
	if( m_player )
	{
		for( auto& enemy : m_enemies )
		{
			if( enemy->CollidingWith( *m_player ) )
			{
				playerHit = true;
				m_player->OnHit( (ACylinderPawn*) enemy->GetOwner() );
				break;
			}
		}
		if( !playerHit )
		{
			for( auto& enemyBullet : m_enemyBullets )
			{
				if( enemyBullet->CollidingWith( *m_player ) )
				{
					playerHit = true;
					m_player->OnHit( (ACylinderPawn*) enemyBullet->GetOwner() );
					enemyBullet->OnHit( (ACylinderPawn*) m_player->GetOwner() );
					break;
				}
			}
		}
	}

	for( auto& playerBullet : m_playerBullets )
	{
		for( auto& enemy : m_enemies )
		{
			if( enemy->CollidingWith( *playerBullet ) )
			{
				enemy->OnHit( (ACylinderPawn*) playerBullet->GetOwner() );
				playerBullet->OnHit( (ACylinderPawn*) enemy->GetOwner() );
				break;
			}
		}
	}
}

