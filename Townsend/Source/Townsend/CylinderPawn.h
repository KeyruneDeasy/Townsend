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

	void Move( const FVector2D& moveVec );

private:
	float m_orbitDistance;
	float m_angle;
	float m_speed;

	FVector2D m_movement;

	void CalculatePlayerInputMoveVector();
	void UpdateActorLocationFromOrbit();
	void UpdateActorLocationFromOrbit( FVector& location );
};

