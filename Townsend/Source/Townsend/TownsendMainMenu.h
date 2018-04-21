// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TownsendMainMenu.generated.h"


UCLASS()
class TOWNSEND_API UTownsendMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
	void StartGame();
	
	
};
