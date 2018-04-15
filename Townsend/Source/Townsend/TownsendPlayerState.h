// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TownsendPlayerState.generated.h"

/*UENUM()
enum class PlayerStateT : uint8
{
	State_Playing,
	State_Dead,

	State_Max
}*/

UCLASS()
class TOWNSEND_API ATownsendPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	static float s_respawnTime;
	static float s_invulnerabilityTimeAfterRespawn;
	
public:
	ATownsendPlayerState();

	virtual void Tick(float DeltaTime) override;

	void Kill();
	bool IsDead() { return m_respawnTimer > 0.0f; }
	float GetRespawnTime() { return m_respawnTimer; }
	bool IsInvulnerable() { return m_invulnerabilityTimer > 0.0f; }

private:
	float m_respawnTimer;
	float m_invulnerabilityTimer;
	
	void Respawn();
};
