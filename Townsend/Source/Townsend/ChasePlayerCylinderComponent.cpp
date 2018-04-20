// Fill out your copyright notice in the Description page of Project Settings.

#include "ChasePlayerCylinderComponent.h"
#include "CylinderPawn.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UChasePlayerCylinderComponent::UChasePlayerCylinderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UChasePlayerCylinderComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UChasePlayerCylinderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if( ACylinderPawn* myPawn = (ACylinderPawn*) GetOwner() )
	{
		if( APawn* playerPawn = UGameplayStatics::GetPlayerPawn( GetWorld(), 0 ) )
		{
			FVector playerLoc = playerPawn->GetActorLocation();
			myPawn->MoveTowardsLocation( playerLoc, DeltaTime );
		}
	}
}

