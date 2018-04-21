// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TownsendHUD.generated.h"


UCLASS()
class TOWNSEND_API UTownsendHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintGetter)
	FText GetRespawnTime();

	UFUNCTION(BlueprintGetter)
	ESlateVisibility GetRespawnTimerVisibility();

	UFUNCTION(BlueprintGetter)
	FText GetScore();
	
	UFUNCTION(BlueprintGetter)
	FText GetLives();
};
