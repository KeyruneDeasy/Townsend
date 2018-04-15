// Fill out your copyright notice in the Description page of Project Settings.

#include "CylinderPawn.h"
#include "TownsendGameModeBase.h"

#define CYLINDERPAWN_AXIS_MOVE_X "MoveX"
#define CYLINDERPAWN_AXIS_MOVE_Y "MoveY"

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

// Sets default values
ACylinderPawn::ACylinderPawn()
	: m_speed( 10.0f )
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACylinderPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACylinderPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CalculatePlayerInputMoveVector();

	Move( m_movement * m_speed );
}

// Called to bind functionality to input
void ACylinderPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis( CYLINDERPAWN_AXIS_MOVE_X );
	PlayerInputComponent->BindAxis( CYLINDERPAWN_AXIS_MOVE_Y );
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
