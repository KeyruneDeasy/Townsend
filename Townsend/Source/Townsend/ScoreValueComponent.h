// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreValueComponent.generated.h"

class ACylinderPawn;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWNSEND_API UScoreValueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UScoreValueComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	uint32 m_score;

	void OnDeath( ACylinderPawn* killingPawn );
};
