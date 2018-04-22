// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HighScoreMenu.generated.h"

class UTownsendSaveGame;
class UTownsendMainMenu;

UCLASS()
class TOWNSEND_API UHighScoreMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UHighScoreMenu( const FObjectInitializer& init );

	void Activate();
	void Deactivate();

	void SetMainMenu( UTownsendMainMenu* mainMenu ) { m_mainMenu = mainMenu; }

protected:
	UFUNCTION(BlueprintGetter)
	FText GetNameText1() { return GetNameText( 1 ); }
	UFUNCTION(BlueprintGetter)
	FText GetNameText2() { return GetNameText( 2 ); }
	UFUNCTION(BlueprintGetter)
	FText GetNameText3() { return GetNameText( 3 ); }
	UFUNCTION(BlueprintGetter)
	FText GetNameText4() { return GetNameText( 4 ); }
	UFUNCTION(BlueprintGetter)
	FText GetNameText5() { return GetNameText( 5 ); }
	UFUNCTION(BlueprintGetter)
	FText GetNameText6() { return GetNameText( 6 ); }
	UFUNCTION(BlueprintGetter)
	FText GetNameText7() { return GetNameText( 7 ); }
	UFUNCTION(BlueprintGetter)
	FText GetNameText8() { return GetNameText( 8 ); }
	UFUNCTION(BlueprintGetter)
	FText GetNameText9() { return GetNameText( 9 ); }
	UFUNCTION(BlueprintGetter)
	FText GetNameText10() { return GetNameText( 10 ); }
	
	UFUNCTION(BlueprintGetter)
	FText GetScoreText1() { return GetScoreText( 1 ); }
	UFUNCTION(BlueprintGetter)
	FText GetScoreText2() { return GetScoreText( 2 ); }
	UFUNCTION(BlueprintGetter)
	FText GetScoreText3() { return GetScoreText( 3 ); }
	UFUNCTION(BlueprintGetter)
	FText GetScoreText4() { return GetScoreText( 4 ); }
	UFUNCTION(BlueprintGetter)
	FText GetScoreText5() { return GetScoreText( 5 ); }
	UFUNCTION(BlueprintGetter)
	FText GetScoreText6() { return GetScoreText( 6 ); }
	UFUNCTION(BlueprintGetter)
	FText GetScoreText7() { return GetScoreText( 7 ); }
	UFUNCTION(BlueprintGetter)
	FText GetScoreText8() { return GetScoreText( 8 ); }
	UFUNCTION(BlueprintGetter)
	FText GetScoreText9() { return GetScoreText( 9 ); }
	UFUNCTION(BlueprintGetter)
	FText GetScoreText10() { return GetScoreText( 10 ); }

	UFUNCTION(BlueprintCallable)
	void ReturnToMainMenu();

private:
	UPROPERTY()
	UTownsendSaveGame* m_savegame;
	UTownsendMainMenu* m_mainMenu;

	FText GetNameText( int rank );
	FText GetScoreText( int rank );
};
