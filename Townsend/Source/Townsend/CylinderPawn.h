// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CylinderPawn.generated.h"

UCLASS()
class TOWNSEND_API ACylinderPawn : public APawn
{
	GENERATED_BODY()

public:
	static FVector CalculateLocationFromOrbit( float distance, float angle, float z = 0.0f );
	static float CalculateOrbitAngleFromLocation( const FVector& location );
	static float CalculateOrbitAngleFromLocation( const FVector& location, float distance );
	static FVector2D Get2DVectorAcrossCylinder( float orbitDistance, float startingAngle, float startingZ, const FVector& destination );

	// Sets default values for this pawn's properties
	ACylinderPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector2D GetPlayerInputMoveVector() const;
	float GetOrbitDistance() const;
	float GetOrbitAngle() const { return m_angle; }
	float GetSpeed() const { return m_speed; }
	float GetMinZ() const;
	float GetMaxZ() const;

	void Move( const FVector2D& moveVec );
	void MoveTowardsLocation( const FVector& location );

private:
	UPROPERTY(EditAnywhere)
	float m_angle;

	UPROPERTY(EditAnywhere)
	float m_speed;

	FVector2D m_movement;

	void CalculatePlayerInputMoveVector();
	void UpdateActorLocationFromOrbit();
	void UpdateActorLocationFromOrbit( float z );
};

