// Fill out your copyright notice in the Description page of Project Settings.

#include "CylinderPawn.h"
#include "TownsendGameModeBase.h"
#include "TownsendPlayerState.h"

#define CYLINDERPAWN_AXIS_MOVE_X "MoveX"
#define CYLINDERPAWN_AXIS_MOVE_Y "MoveY"
#define CYLINDERPAWN_AXIS_SHOOT "Shoot"

FVector ACylinderPawn::CalculateLocationFromOrbit( float distance, float angle, float z )
{
	float orbitDistance = distance;
	float sin, cos;
	FMath::SinCos( &sin, &cos, angle );
	return FVector( orbitDistance * cos, orbitDistance * sin, z );
}

float ACylinderPawn::CalculateOrbitAngleFromLocation( const FVector& location )
{
	return CalculateOrbitAngleFromLocation( location, location.Size() );
}

float ACylinderPawn::CalculateOrbitAngleFromLocation( const FVector& location, float distance )
{
	FVector location2D ( location.X, location.Y, 0.0f );
	float angle = FMath::Acos( FVector::DotProduct( FVector( 1.0f, 0.0f, 0.0f ), location2D ) / distance );
	return location.Y > 0.0f ? angle : -angle;
}

FVector2D ACylinderPawn::Get2DVectorAcrossCylinder( float orbitDistance, float startingAngle, float startingZ, const FVector& destination )
{
	float destinationAngle = CalculateOrbitAngleFromLocation( destination, orbitDistance );

	float angleToTraverse = destinationAngle - startingAngle;
	// Can we go quicker the other way round the cylinder?
	while( angleToTraverse > PI )
	{
		angleToTraverse -= 2 * PI;
	}
	while( angleToTraverse < -PI )
	{
		angleToTraverse += 2 * PI;
	}

	// Note: Increasing angle corresponds to a negative X movement, and vice-versa.
	return FVector2D( -( angleToTraverse * orbitDistance ), destination.Z - startingZ );
}

float ACylinderPawn::Calculate2DPlanePositionX( float orbitDistance, float angle )
{
	return ( 2 * PI - angle ) * orbitDistance;
}

ACylinderPawn::ACylinderPawn()
	: m_speed( 10.0f )
	, m_shootCooldownTimer( 0.0f )
	, m_alive( true )
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACylinderPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACylinderPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if( !m_alive )
	{
		Destroy();
		return;
	}

	if( ATownsendPlayerState* playerState = GetPlayerState() )
	{
		if( playerState->IsDead() )
		{
			SetActorHiddenInGame( true );
			return;
		}
		else
		{
			SetActorHiddenInGame( false );
		}
	}

	CalculatePlayerInputMoveVector();
	Move( m_movement * m_speed );
	ProcessShooting( DeltaTime );
}

// Called to bind functionality to input
void ACylinderPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis( CYLINDERPAWN_AXIS_MOVE_X );
	PlayerInputComponent->BindAxis( CYLINDERPAWN_AXIS_MOVE_Y );
	PlayerInputComponent->BindAxis( CYLINDERPAWN_AXIS_SHOOT );
}

FVector2D ACylinderPawn::GetPlayerInputMoveVector() const
{
	return m_movement;
}

float ACylinderPawn::GetOrbitDistance() const
{
	if( ATownsendGameModeBase* gameMode = ATownsendGameModeBase::GetFrom( GetWorld() ) )
	{
		return gameMode->GetOrbitDistance();
	}
	return 0.0f;
}

float ACylinderPawn::GetMinZ() const
{
	if( ATownsendGameModeBase* gameMode = ATownsendGameModeBase::GetFrom( GetWorld() ) )
	{
		return gameMode->GetCylinderMinZ();
	}
	return 0.0f;
}

float ACylinderPawn::GetMaxZ() const
{
	if( ATownsendGameModeBase* gameMode = ATownsendGameModeBase::GetFrom( GetWorld() ) )
	{
		return gameMode->GetCylinderMaxZ();
	}
	return 0.0f;
}

FVector2D ACylinderPawn::Get2DPlanePosition() const
{
	float x = Calculate2DPlanePositionX( GetOrbitDistance(), GetOrbitAngle() );
	float z = GetActorLocation().Z;
	return FVector2D( x, z );
}

FVector2D ACylinderPawn::Get2DPlanePosition_XAsAngle() const
{
	float x = GetOrbitAngle();
	float z = GetActorLocation().Z;
	return FVector2D( x, z );
}

void ACylinderPawn::SetAngle( float angle )
{
	m_angle = angle;
	UpdateActorLocationFromOrbit();
}

void ACylinderPawn::SetLocation( float angle, float z )
{
	m_angle = angle;
	UpdateActorLocationFromOrbit( z );
}

void ACylinderPawn::Move( const FVector2D& moveVec )
{
	float orbitDistance = GetOrbitDistance();
	if( orbitDistance > 0.0f )
	{
		m_angle -= moveVec.X / orbitDistance;
	}

	FVector loc = GetActorLocation();
	loc.Z += moveVec.Y;
	loc.Z = FMath::Clamp( loc.Z, GetMinZ(), GetMaxZ() );
	UpdateActorLocationFromOrbit( loc.Z );
}

void ACylinderPawn::MoveTowardsLocation( const FVector& location )
{
	FVector myLoc = GetActorLocation();
	FVector2D travelVector = ACylinderPawn::Get2DVectorAcrossCylinder( GetOrbitDistance(), GetOrbitAngle(), myLoc.Z, location );
	if( !travelVector.IsZero() )
	{
		if( travelVector.SizeSquared() >= FMath::Square( m_speed ) )
		{
			// Only move by the appropriate amount according to my speed.
			travelVector.Normalize();
			travelVector *= m_speed;
		}

		Move( travelVector );
	}
}

void ACylinderPawn::ShootLeft()
{
	Shoot( FVector2D( -1.0f, 0.0f ) );
}

void ACylinderPawn::ShootRight()
{
	Shoot( FVector2D( 1.0f, 0.0f ) );
}

void ACylinderPawn::Shoot( const FVector2D& shootHeading )
{
	if( m_bulletClass )
	{
		ACylinderPawn* bullet = (ACylinderPawn*) GetWorld()->SpawnActor( m_bulletClass );
		bullet->SetLocation( m_angle, GetActorLocation().Z );
		FRotator rotation( 0.0f, 90.0f, 0.0f );
		bullet->SetActorRotation( rotation );
		bullet->SetHeading( shootHeading );
	}
}

void ACylinderPawn::OnHit( CollisionType myType, CollisionType otherType )
{
	switch( myType )
	{
	case CollisionType::Collision_Player:
	{
		KillPlayer();
		break;
	}
	case CollisionType::Collision_Enemy:
	{
		Die();
		break;
	}
	case CollisionType::Collision_PlayerBullet:
	{
		Die();
		break;
	}
	}
}

void ACylinderPawn::CalculatePlayerInputMoveVector()
{
	if( InputComponent )
	{
		m_movement.X = InputComponent->GetAxisValue( CYLINDERPAWN_AXIS_MOVE_X );
		m_movement.Y = InputComponent->GetAxisValue( CYLINDERPAWN_AXIS_MOVE_Y );

		// Normalise if greater than 1.
		float magSqr = m_movement.SizeSquared();
		if( magSqr > 1.0f )
		{
			m_movement /= FMath::Sqrt( magSqr );
		}
	}
	else
	{
		m_movement = FVector2D::ZeroVector;
	}
}

void ACylinderPawn::UpdateActorLocationFromOrbit()
{
	UpdateActorLocationFromOrbit( GetActorLocation().Z );
}

void ACylinderPawn::UpdateActorLocationFromOrbit( float z )
{
	FRotator rotation( 0.0f, m_angle * 180.0f / PI, 0.0f );

	FVector location = CalculateLocationFromOrbit( GetOrbitDistance(), m_angle, z );

	SetActorLocationAndRotation(location, rotation);
}

void ACylinderPawn::KillPlayer()
{
	if( ATownsendPlayerState* playerState = GetPlayerState() )
	{
		playerState->Kill();
	}
}

ATownsendPlayerState* ACylinderPawn::GetPlayerState()
{
	if( AController* controller = GetController() )
	{
		if( controller->IsPlayerController() )
		{
			return (ATownsendPlayerState*) ( controller->PlayerState );
		}
	}
	return NULL;
}

void ACylinderPawn::ProcessShooting( float dt )
{
	if( m_shootCooldownTimer > 0.0f )
	{
		m_shootCooldownTimer -= dt;
	}

	if( m_shootCooldownTimer <= 0.0f && m_fireRate > 0.0f )
	{
		float shootAxis = InputComponent->GetAxisValue( CYLINDERPAWN_AXIS_SHOOT );

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
