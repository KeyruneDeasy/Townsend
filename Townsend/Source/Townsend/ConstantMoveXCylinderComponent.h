// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConstantMoveXCylinderComponent.generated.h"

UENUM()
enum class XDirection
{
	Dir_Left,
	Dir_Right
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWNSEND_API UConstantMoveXCylinderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UConstantMoveXCylinderComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	XDirection m_dir;

	UPROPERTY(EditAnywhere)
	float m_speed;
};
