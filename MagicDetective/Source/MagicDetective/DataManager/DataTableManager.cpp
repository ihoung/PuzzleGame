// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableManager.h"
#include "Engine/Texture.h"

#include "MovableActor.h"


void UDataTableManager::Initialize(FSubsystemCollectionBase &Collection)
{
	Super::Initialize(Collection);
}

void UDataTableManager::Deinitialize()
{
	GameplayPropertyData = nullptr;
}

void UDataTableManager::InitializeData(EDataTableType DataTableType, class UDataTable *Data)
{
	switch (DataTableType)
	{
	case GameplayProperty:
		GameplayPropertyData = Data;
		break;
	default:
		break;
	}
}

FGameplayPropertyData UDataTableManager::GetGameplayProperty(const FName &RowName)
{
	const FString ContextString(TEXT("Gameplay Property Data"));
	FGameplayPropertyData *data = GameplayPropertyData->FindRow<FGameplayPropertyData>(RowName, ContextString);
	return data ? *data : FGameplayPropertyData();
}
