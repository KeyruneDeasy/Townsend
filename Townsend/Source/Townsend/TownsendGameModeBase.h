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
		: m_orbitDistance( 500.0f ) {}

	static ATownsendGameModeBase* GetFrom( UWorld* world );

	float GetOrbitDistance() { return m_orbitDistance; }

private:

	float m_orbitDistance;
	
};
