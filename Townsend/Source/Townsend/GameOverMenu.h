// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverMenu.generated.h"


UCLASS()
class TOWNSEND_API UGameOverMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintGetter)
	FText GetScore();

	UFUNCTION(BlueprintCallable)
	void ReturnToMainMenu();
};
