// Fill out your copyright notice in the Description page of Project Settings.

#include "ConstantMoveXCylinderComponent.h"
#include "CylinderPawn.h"


UConstantMoveXCylinderComponent::UConstantMoveXCylinderComponent()
	: m_dir( XDirection::Dir_Right )
	, m_speed( 10.0f )
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UConstantMoveXCylinderComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UConstantMoveXCylinderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if( ACylinderPawn* myPawn = (ACylinderPawn*) GetOwner() )
	{
		myPawn->Move( FVector2D( m_dir == XDirection::Dir_Left ? -m_speed : m_speed, 0.0f ) );
	}
}

