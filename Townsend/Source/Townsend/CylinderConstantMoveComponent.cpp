// Fill out your copyright notice in the Description page of Project Settings.

#include "CylinderConstantMoveComponent.h"
#include "CylinderPawn.h"


UCylinderConstantMoveComponent::UCylinderConstantMoveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCylinderConstantMoveComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCylinderConstantMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if( ACylinderPawn* myPawn = (ACylinderPawn*) GetOwner() )
	{
		myPawn->Move( myPawn->GetHeading() * m_speed * DeltaTime );
	}
}

