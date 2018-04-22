// Fill out your copyright notice in the Description page of Project Settings.

#include "CylinderShootComponent.h"
#include "BulletComponent.h"
#include "TownsendPlayerState.h"


UCylinderShootComponent::UCylinderShootComponent()
	: m_shootCooldownTimer( 0.0f )
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCylinderShootComponent::BeginPlay()
{
	Super::BeginPlay();

	// Wait for the owner to read the player input.
	AddTickPrerequisiteActor( GetOwner() );
}

void UCylinderShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ProcessShooting( DeltaTime );
}

void UCylinderShootComponent::ShootLeft()
{
	Shoot( FVector2D( -1.0f, 0.0f ) );
}

void UCylinderShootComponent::ShootRight()
{
	Shoot( FVector2D( 1.0f, 0.0f ) );
}

void UCylinderShootComponent::Shoot( const FVector2D& shootHeading )
{
	if( ACylinderPawn* owner = (ACylinderPawn*) GetOwner() )
	{
		if( m_bulletClass )
		{
			ACylinderPawn* bullet = (ACylinderPawn*) GetWorld()->SpawnActor( m_bulletClass );
			float orbitAngle = owner->GetOrbitAngle() - ( m_shootLocator.X / owner->GetOrbitDistance() );
			float z = owner->GetActorLocation().Z + m_shootLocator.Y;
			bullet->SetLocation( orbitAngle, z );
			bullet->SetHeading( shootHeading );
			if( UBulletComponent* bulletComp = (UBulletComponent*) bullet->FindComponentByClass( UBulletComponent::StaticClass() ) )
			{
				if( AController* controller = owner->GetController() )
				{
					if( controller->IsPlayerController() )
					{
						bulletComp->SetOwningPlayer( (APlayerController*) controller );
					}
				}
			}

			float rotationAngle = ACylinderPawn::AngleBetweenNormalisedVectors( FVector2D( 1.0f, 0.0f ), shootHeading );
			if( shootHeading.Y < 0.0f ) { rotationAngle = -rotationAngle; }
			FRotator rotation( FMath::RadiansToDegrees( rotationAngle ), 270.0f, 0.0f );
			bullet->SetLocalRotation( rotation );
		}
	}
}

void UCylinderShootComponent::ProcessShooting( float dt )
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
			float shootAxis = owner->GetPlayerInputShootAxis();

			// If we're shooting continuously, let the "overflow" time from one cooldown count towards the next.
			// But if we stop shooting, let the cooldown sit at zero.
			if( shootAxis == 0.0f )
			{
				m_shootCooldownTimer;
			}
			else
			{
				if( shootAxis > 0.0f )
				{
					ShootRight();
				}
				else //if( shootAxis < 0.0f )
				{
					ShootLeft();
				}
				m_shootCooldownTimer += 1.0f / m_fireRate;
			}
		}
	}
}

