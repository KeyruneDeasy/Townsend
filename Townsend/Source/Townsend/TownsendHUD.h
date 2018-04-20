// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TownsendHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOWNSEND_API UTownsendHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	FText GetRespawnTime();

	UFUNCTION(BlueprintCallable)
	ESlateVisibility GetRespawnTimerVisibility();
	
};
