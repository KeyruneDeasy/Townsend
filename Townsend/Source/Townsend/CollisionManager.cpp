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
				break;
			}
		}
	}

	if( playerHit )
	{
		m_player->OnHit( CollisionType::Collision_Enemy );
	}

	for( auto& playerBullet : m_playerBullets )
	{
		for( auto& enemy : m_enemies )
		{
			if( enemy->CollidingWith( *playerBullet ) )
			{
				enemy->OnHit( CollisionType::Collision_PlayerBullet );
				playerBullet->OnHit( CollisionType::Collision_Enemy );
				break;
			}
		}
	}
}

