// Fill out your copyright notice in the Description page of Project Settings.

#include "AutoCylinderShootComponent.h"
#include "TownsendPlayerState.h"

void UAutoCylinderShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ProcessShooting( DeltaTime );
}

void UAutoCylinderShootComponent::ProcessShooting( float dt )
{
	if( m_shootCooldownTimer > 0.0f )
	{
		m_shootCooldownTimer -= dt;
	}

	if( m_shootCooldownTimer <= 0.0f && m_fireRate > 0.0f )
	{
		if( ACylinderPawn* owner = (ACylinderPawn*) GetOwner() )
		{
			if( ATownsendPlayerState* playerState = owner->GetPlayerState() )
			{
				if( playerState->IsDead() )
				{
					return;
				}
			}

			m_heading.Normalize();
			Shoot( m_heading );

			// Let the "overflow" time from one cooldown count towards the next.
			m_shootCooldownTimer += 1.0f / m_fireRate;
		}
	}
}

