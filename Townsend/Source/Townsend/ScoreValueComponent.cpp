// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreValueComponent.h"
#include "CylinderPawn.h"
#include "BulletComponent.h"
#include "GameFramework/PlayerState.h"


UScoreValueComponent::UScoreValueComponent()
{
}

void UScoreValueComponent::BeginPlay()
{
	Super::BeginPlay();

	ACylinderPawn& owner = *( (ACylinderPawn*) GetOwner() );
	owner.GetDeathEvent().AddUObject( this, &UScoreValueComponent::OnDeath );
}

void UScoreValueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UScoreValueComponent::OnDeath( ACylinderPawn* killingPawn )
{
	if( killingPawn )
	{
		if( UBulletComponent* bulletComponent = (UBulletComponent*) killingPawn->GetComponentByClass( UBulletComponent::StaticClass() ) )
		{
			if( APlayerController* playerController = bulletComponent->GetOwningPlayer() )
			{
				if( APlayerState* playerState = playerController->PlayerState )
				{
					playerState->Score += m_score;
				}
			}
		}
	}
}

