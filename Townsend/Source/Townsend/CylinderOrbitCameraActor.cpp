// Fill out your copyright notice in the Description page of Project Settings.

#include "CylinderOrbitCameraActor.h"
#include "CylinderPawn.h"


ACylinderOrbitCameraActor::ACylinderOrbitCameraActor()
	: m_angle( 0.0f )
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bAllowTickOnDedicatedServer = true;
}

void ACylinderOrbitCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if( m_target )
	{
		UpdateLocationFromTarget();
	}
}

void ACylinderOrbitCameraActor::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled( true );

	// Ensure that the target actor has done its movement, including its attached components.
	if( m_target )
	{
		AddTickPrerequisiteActor( m_target );
		const TSet< UActorComponent* >& components = m_target->GetComponents();
		for( UActorComponent* component : components )
		{
			AddTickPrerequisiteComponent( component );
		}
	}
}

void ACylinderOrbitCameraActor::UpdateLocationFromTarget()
{
	if( !m_target ) { return; }
	m_angle = m_target->GetOrbitAngle();
	float orbitDistance = m_target->GetOrbitDistance() + m_targetDistance;
	UpdateLocationFromOrbit( orbitDistance, m_angle );
}

void ACylinderOrbitCameraActor::UpdateLocationFromOrbit( float orbitDistance, float angle )
{
	float z = GetActorLocation().Z;

	FVector location = ACylinderPawn::CalculateLocationFromOrbit( orbitDistance, m_angle, z );
	FRotator rotation( 0.0f, ( m_angle + PI ) * 180.0f / PI, 0.0f );

	SetActorLocationAndRotation( location, rotation );
}

#if WITH_EDITOR
void ACylinderOrbitCameraActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//if( PropertyChangedEvent.GetPropertyName().Equals("m_angle") )
	{
		UpdateLocationFromTarget();
	}
}
#endif

