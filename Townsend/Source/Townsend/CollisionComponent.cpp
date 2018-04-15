// Fill out your copyright notice in the Description page of Project Settings.

#include "CollisionComponent.h"
#include "TownsendGameModeBase.h"


UCollisionComponent::UCollisionComponent()
{
}

void UCollisionComponent::GetMinMax( FVector2D& min, FVector2D& max )
{
	ACylinderPawn* owner = (ACylinderPawn*) GetOwner();
	FVector2D pos = owner->Get2DPlanePosition();
	min.X = pos.X - m_size.X / 2.f;
	min.Y = pos.Y - m_size.Y / 2.f;
	max.X = pos.X + m_size.X / 2.f;
	max.Y = pos.Y + m_size.Y / 2.f;
}

void UCollisionComponent::GetMinMax_XAsAngle( FVector2D& min, FVector2D& max )
{
	ACylinderPawn* owner = (ACylinderPawn*) GetOwner();
	FVector2D pos = owner->Get2DPlanePosition_XAsAngle();
	float angleSize = m_size.X / owner->GetOrbitDistance();
	min.X = pos.X - angleSize / 2.f;
	min.Y = pos.Y - m_size.Y / 2.f;
	max.X = pos.X + angleSize / 2.f;
	max.Y = pos.Y + m_size.Y / 2.f;
}

bool UCollisionComponent::CollidingWith( UCollisionComponent& other )
{
	FVector2D min1, max1, min2, max2;
	GetMinMax_XAsAngle( min1, max1 );
	other.GetMinMax_XAsAngle( min2, max2 );

	if( DimCheck( min1.Y, max1.Y, min2.Y, max2.Y ) )
	{
		if( max1.X > min2.X )
		{
			if( min1.X < max2.X )
			{
				return true;
			}
			else
			{
				return DimCheck( min1.X, max1.X, min2.X + 2 * PI, max2.X + 2 * PI );
			}
		}
		else
		{
			return DimCheck( min1.X + 2 * PI, max1.X + 2 * PI, min2.X, max2.X );
		}
	}
	return false;
}

void UCollisionComponent::BeginPlay()
{
	Super::BeginPlay();

	if( ATownsendGameModeBase* gameMode = ATownsendGameModeBase::GetFrom( GetWorld() ) )
	{
		gameMode->GetCollisionManager().RegisterCollisionComponent( this, m_type );
	}
}

void UCollisionComponent::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
	Super::EndPlay( EndPlayReason );

	if( ATownsendGameModeBase* gameMode = ATownsendGameModeBase::GetFrom( GetWorld() ) )
	{
		gameMode->GetCollisionManager().UnregisterCollisionComponent( this, m_type );
	}
}


