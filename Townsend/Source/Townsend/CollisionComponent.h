// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollisionManager.h"
#include "CollisionComponent.generated.h"

class ACylinderPawn;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWNSEND_API UCollisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCollisionComponent();

	void GetMinMax( FVector2D& min, FVector2D& max );
	void GetMinMax_XAsAngle( FVector2D& min, FVector2D& max );
	bool CollidingWith( UCollisionComponent& other );

	void OnHit( ACylinderPawn* otherPawn );

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

private:	
	UPROPERTY( EditAnywhere )
	CollisionType m_type;

	UPROPERTY( EditAnywhere )
	FVector2D m_size;

	bool DimCheck( float min1, float max1, float min2, float max2 );
};

inline bool UCollisionComponent::DimCheck( float min1, float max1, float min2, float max2 )
{
	return max1 > min2 && min1 < max2;
}
