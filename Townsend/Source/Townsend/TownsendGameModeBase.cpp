// Fill out your copyright notice in the Description page of Project Settings.

#include "TownsendGameModeBase.h"

ATownsendGameModeBase* ATownsendGameModeBase::GetFrom( UWorld* world )
{
	return world ? (ATownsendGameModeBase*) world->GetAuthGameMode() : NULL;
}


