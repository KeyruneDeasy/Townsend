// Fill out your copyright notice in the Description page of Project Settings.

#include "CylinderPawn.h"
#include "TownsendGameModeBase.h"
#include "TownsendPlayerState.h"
#include "BulletComponent.h"

#define CYLINDERPAWN_AXIS_MOVE_X "MoveX"
#define CYLINDERPAWN_AXIS_MOVE_Y "MoveY"
#define CYLINDERPAWN_AXIS_SHOOT "Shoot"

float ACylinderPawn::AngleBetweenVectors( const FVector& a, const FVector& b )
{
	return FMath::Acos( FVector::DotProduct( a, b ) / ( a.Size() * b.Size() ) );
}

float ACylinderPawn::AngleBetweenVectors( const FVector2D& a, const FVector2D& b )
{
	return FMath::Acos( FVector2D::DotProduct( a, b ) / ( a.Size() * b.Size() ) );
}

float ACylinderPawn::AngleBetweenNormalisedVectors( const FVector& a, const FVector& b )
{
	return FMath::Acos( FVector::DotProduct( a, b ) );
}

float ACylinderPawn::AngleBetweenNormalisedVectors( const FVector2D& a, const FVector2D& b )
{
	return FMath::Acos( FVector2D::DotProduct( a, b ) );
}

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

float ACylinderPawn::GetOrbitDistance( UWorld* world )
{
	if( ATownsendGameModeBase* gameMode = ATownsendGameModeBase::GetFrom( world ) )
	{
		return gameMode->GetOrbitDistance();
	}
	return 0.0f;
}

ACylinderPawn::ACylinderPawn()
	: m_alive( true )
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

	UpdatePlayerInput();

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
}

// Called to bind functionality to input
void ACylinderPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis( CYLINDERPAWN_AXIS_MOVE_X );
	PlayerInputComponent->BindAxis( CYLINDERPAWN_AXIS_MOVE_Y );
	PlayerInputComponent->BindAxis( CYLINDERPAWN_AXIS_SHOOT );
}

float ACylinderPawn::GetOrbitDistance() const
{
	return GetOrbitDistance( GetWorld() );
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
	SetAngleInternal( angle );
	UpdateActorLocationFromOrbit();
}

void ACylinderPawn::SetLocation( float angle, float z )
{
	SetAngleInternal( angle );
	UpdateActorLocationFromOrbit( z );
}

void ACylinderPawn::Move( const FVector2D& moveVec )
{
	float orbitDistance = GetOrbitDistance();
	if( orbitDistance > 0.0f )
	{
		SetAngleInternal( m_angle - moveVec.X / orbitDistance );
	}

	FVector loc = GetActorLocation();
	loc.Z += moveVec.Y;
	loc.Z = FMath::Clamp( loc.Z, GetMinZ(), GetMaxZ() );
	UpdateActorLocationFromOrbit( loc.Z );
}

void ACylinderPawn::MoveTowardsLocation( const FVector& location, float speed, float dt )
{
	FVector myLoc = GetActorLocation();
	FVector2D travelVector = ACylinderPawn::Get2DVectorAcrossCylinder( GetOrbitDistance(), GetOrbitAngle(), myLoc.Z, location );
	if( !travelVector.IsZero() )
	{
		float maxTravelDistance = speed * dt;
		if( travelVector.SizeSquared() >= FMath::Square( maxTravelDistance ) )
		{
			// Only move by the appropriate amount according to the speed.
			travelVector.Normalize();
			travelVector *= maxTravelDistance;
		}

		Move( travelVector );
	}
}

void ACylinderPawn::OnHit( ACylinderPawn* otherPawn )
{
	GetDeathEvent().Broadcast( otherPawn );
	if( IsPlayerControlled() )
	{
		KillPlayer();
	}
	else
	{
		Die();
	}
}

void ACylinderPawn::UpdatePlayerInput()
{
	if( InputComponent )
	{
		m_playerMovement.X = InputComponent->GetAxisValue( CYLINDERPAWN_AXIS_MOVE_X );
		m_playerMovement.Y = InputComponent->GetAxisValue( CYLINDERPAWN_AXIS_MOVE_Y );

		// Normalise if greater than 1.
		float magSqr = m_playerMovement.SizeSquared();
		if( magSqr > 1.0f )
		{
			m_playerMovement /= FMath::Sqrt( magSqr );
		}

		m_playerShootAxis = InputComponent->GetAxisValue( CYLINDERPAWN_AXIS_SHOOT );
	}
	else
	{
		m_playerMovement = FVector2D::ZeroVector;
		m_playerShootAxis = 0.0f;
	}
}

void ACylinderPawn::UpdateActorLocationFromOrbit()
{
	UpdateActorLocationFromOrbit( GetActorLocation().Z );
}

void ACylinderPawn::UpdateActorLocationFromOrbit( float z )
{
	FRotator rotation( 0.0f, m_angle * 180.0f / PI, 0.0f );
	rotation += m_localRotation;

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

void ACylinderPawn::SetAngleInternal( float angle )
{
	m_angle = angle;
	// Wrap the angle to be between 0 and 360 degrees
	while( m_angle < 0.0f )
	{
		m_angle += 2 * PI;
	}
	while( m_angle > 2 * PI )
	{
		m_angle -= 2 * PI;
	}
}
