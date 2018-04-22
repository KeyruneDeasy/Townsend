// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CylinderPawn.h"
#include "CylinderShootComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWNSEND_API UCylinderShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCylinderShootComponent();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	void ShootLeft();
	void ShootRight();
	void Shoot( const FVector2D& shootHeading );

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf < ACylinderPawn > m_bulletClass;

	UPROPERTY(EditAnywhere)
	float m_fireRate;

	float m_shootCooldownTimer;

	void ProcessShooting( float dt );
};
