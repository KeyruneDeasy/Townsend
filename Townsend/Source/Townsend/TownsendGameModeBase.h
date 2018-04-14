// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TownsendGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOWNSEND_API ATownsendGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATownsendGameModeBase()
		: m_orbitDistance( 500.0f )
		, m_cylinderMinZ( 100.0f )
		, m_cylinderMaxZ( 700.0f ) {}

	static ATownsendGameModeBase* GetFrom( UWorld* world );

	float GetOrbitDistance() { return m_orbitDistance; }
	float GetCylinderMinZ() { return m_cylinderMinZ; }
	float GetCylinderMaxZ() { return m_cylinderMaxZ; }

private:

	float m_orbitDistance;
	float m_cylinderMinZ;
	float m_cylinderMaxZ;
	
};
