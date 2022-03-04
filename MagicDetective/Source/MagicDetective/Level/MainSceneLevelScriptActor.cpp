// Fill out your copyright notice in the Description page of Project Settings.


#include "MainSceneLevelScriptActor.h"
#include "Engine/DataTable.h"

#include "DataTableManager.h"


void AMainSceneLevelScriptActor::BeginPlay()
{
	// Initialize Data Tables
	GetGameInstance()->GetSubsystem<UDataTableManager>()->InitializeData(EDataTableType::GameplayProperty, GameplayPropertyDataTable);
	GetGameInstance()->GetSubsystem<UDataTableManager>()->InitializeData(EDataTableType::Caption, CaptionDataTable);
}
