// Fill out your copyright notice in the Description page of Project Settings.

#include "CylinderPawn.h"
#include "TownsendGameModeBase.h"

#define CYLINDERPAWN_AXIS_MOVE_X "MoveX"
#define CYLINDERPAWN_AXIS_MOVE_Y "MoveY"

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

void ACylinderPawn::Move( const FVector2D& moveVec )
{
	float orbitDistance = GetOrbitDistance();
	if( orbitDistance > 0.0f )
	{
		m_angle -= moveVec.X / orbitDistance;
	}

	FVector loc = GetActorLocation();
	loc.Z += moveVec.Y;
	UpdateActorLocationFromOrbit( loc );
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
	FVector location = GetActorLocation();
	UpdateActorLocationFromOrbit( location );
}

void ACylinderPawn::UpdateActorLocationFromOrbit( FVector& location )
{
	FRotator rotation( 0.0f, m_angle * 180.0f / PI, 0.0f );

	float orbitDistance = GetOrbitDistance();
	float sin, cos;
	FMath::SinCos( &sin, &cos, m_angle );
	location.X = orbitDistance * cos;
	location.Y = orbitDistance * sin;

	SetActorLocationAndRotation(location, rotation);
}
