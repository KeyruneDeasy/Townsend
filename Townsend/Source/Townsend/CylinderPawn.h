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
	static float Calculate2DPlanePositionX( float orbitDistance, float angle );

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

	// If the cylinder's surface is a flat 2D plane, this gives the position of this pawn on that plane.
	FVector2D Get2DPlanePosition() const;
	// As above, but the X component is the angle value instead of an absolute distance value.
	FVector2D Get2DPlanePosition_XAsAngle() const;

	void SetAngle( float angle );
	void SetLocation( float angle, float z );

	void Move( const FVector2D& moveVec );
	void MoveTowardsLocation( const FVector& location );

private:
	UPROPERTY(EditAnywhere)
	float m_angle;

	UPROPERTY(EditAnywhere)
	float m_speed;

	UPROPERTY(EditAnywhere)
	FVector2D m_hitbox;

	FVector2D m_movement;

	void CalculatePlayerInputMoveVector();
	void UpdateActorLocationFromOrbit();
	void UpdateActorLocationFromOrbit( float z );
};

