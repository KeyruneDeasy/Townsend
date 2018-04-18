// Fill out your copyright notice in the Description page of Project Settings.

#include "DestroyTimerComponent.h"


UDestroyTimerComponent::UDestroyTimerComponent()
	: m_timer( 5.0f )
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDestroyTimerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDestroyTimerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	m_timer -= DeltaTime;

	if( m_timer <= 0.0f )
	{
		GetOwner()->Destroy();
	}
}

