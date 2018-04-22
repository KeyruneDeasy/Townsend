// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CylinderPawn.generated.h"

enum class CollisionType : uint8;

class ATownsendPlayerState;

UCLASS()
class TOWNSEND_API ACylinderPawn : public APawn
{
	GENERATED_BODY()

public:
	static float AngleBetweenVectors( const FVector& a, const FVector& b );
	static float AngleBetweenVectors( const FVector2D& a, const FVector2D& b );
	static float AngleBetweenNormalisedVectors( const FVector& a, const FVector& b );
	static float AngleBetweenNormalisedVectors( const FVector2D& a, const FVector2D& b );
	static FVector CalculateLocationFromOrbit( float distance, float angle, float z = 0.0f );
	static float CalculateOrbitAngleFromLocation( const FVector& location );
	static float CalculateOrbitAngleFromLocation( const FVector& location, float distance );
	static FVector2D Get2DVectorAcrossCylinder( float orbitDistance, float startingAngle, float startingZ, const FVector& destination );
	static float Calculate2DPlanePositionX( float orbitDistance, float angle );

	DECLARE_EVENT_OneParam( ACylinderPawn, FDeathEvent, ACylinderPawn* )
	FDeathEvent& GetDeathEvent() { return DeathEvent; }

	// Sets default values for this pawn's properties
	ACylinderPawn();

public:
	virtual void Tick( float DeltaTime ) override;
	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;

	FVector2D GetPlayerInputMoveVector() const { return m_playerMovement; }
	float GetPlayerInputShootAxis() const { return m_playerShootAxis; }
	float GetOrbitDistance() const;
	float GetOrbitAngle() const { return m_angle; }
	float GetMinZ() const;
	float GetMaxZ() const;
	FVector2D GetHeading() const { return m_heading; }
	ATownsendPlayerState* GetPlayerState();

	// If the cylinder's surface is a flat 2D plane, this gives the position of this pawn on that plane.
	FVector2D Get2DPlanePosition() const;
	// As above, but the X component is the angle value instead of an absolute distance value.
	FVector2D Get2DPlanePosition_XAsAngle() const;

	void SetAngle( float angle );
	void SetLocation( float angle, float z );
	void SetHeading( const FVector2D& heading ) { m_heading = heading; }
	void SetLocalRotation( const FRotator& rotation ) { m_localRotation = rotation; }

	void Move( const FVector2D& moveVec );
	void MoveTowardsLocation( const FVector& location, float speed, float dt );

	void OnHit( ACylinderPawn* otherPawn );

protected:
	virtual void BeginPlay() override;

private:
	FDeathEvent DeathEvent;

	UPROPERTY(EditAnywhere)
	float m_angle;

	FVector2D m_playerMovement;
	float m_playerShootAxis;

	FVector2D m_heading;
	FRotator m_localRotation;

	void UpdatePlayerInput();
	void UpdateActorLocationFromOrbit();
	void UpdateActorLocationFromOrbit( float z );
	void KillPlayer();
	void Die() { m_alive = false; }

	bool m_alive;
};

