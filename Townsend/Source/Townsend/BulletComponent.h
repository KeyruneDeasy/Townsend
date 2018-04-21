// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWNSEND_API UBulletComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBulletComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	APlayerController* GetOwningPlayer() { return m_owningPlayer; }
	void SetOwningPlayer( APlayerController* player ) { m_owningPlayer = player; }

private:
	APlayerController* m_owningPlayer;
};
