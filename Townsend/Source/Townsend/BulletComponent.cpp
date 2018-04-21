// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletComponent.h"


UBulletComponent::UBulletComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBulletComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBulletComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

