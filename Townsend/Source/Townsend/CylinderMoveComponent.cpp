// Fill out your copyright notice in the Description page of Project Settings.

#include "CylinderMoveComponent.h"
#include "CylinderPawn.h"
#include "TownsendPlayerState.h"

UCylinderMoveComponent::UCylinderMoveComponent()
	: m_speed( 300.0f )
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCylinderMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// Wait for the owner to read the player input.
	AddTickPrerequisiteActor( GetOwner() );
}

void UCylinderMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if( ACylinderPawn* owner = (ACylinderPawn*) GetOwner() )
	{
		if( ATownsendPlayerState* playerState = owner->GetPlayerState() )
		{
			if( playerState->IsDead() )
			{
				return;
			}
		}
		FVector2D movement = owner->GetPlayerInputMoveVector();
		owner->Move( movement * m_speed * DeltaTime );
	}
}

