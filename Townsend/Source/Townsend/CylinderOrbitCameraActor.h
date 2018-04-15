// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "CylinderOrbitCameraActor.generated.h"

class ACylinderPawn;

UCLASS()
class TOWNSEND_API ACylinderOrbitCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	ACylinderOrbitCameraActor();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	ACylinderPawn* m_target;
	float m_angle;
	UPROPERTY(EditAnywhere)
	float m_targetDistance;

	void UpdateLocationFromTarget();
	void UpdateLocationFromOrbit( float orbitDistance, float angle );

public:
#if WITH_EDITOR
	void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent );
#endif
};
