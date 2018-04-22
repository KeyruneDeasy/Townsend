// Fill out your copyright notice in the Description page of Project Settings.

#include "ChasePlayerCylinderComponent.h"
#include "CylinderPawn.h"
#include "Kismet/GameplayStatics.h"


UChasePlayerCylinderComponent::UChasePlayerCylinderComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UChasePlayerCylinderComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UChasePlayerCylinderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if( ACylinderPawn* myPawn = (ACylinderPawn*) GetOwner() )
	{
		if( APawn* playerPawn = UGameplayStatics::GetPlayerPawn( GetWorld(), 0 ) )
		{
			FVector playerLoc = playerPawn->GetActorLocation();
			myPawn->MoveTowardsLocation( playerLoc, m_speed, DeltaTime );
		}
	}
}

