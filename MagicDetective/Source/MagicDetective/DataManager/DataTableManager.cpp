// Fill out your copyright notice in the Description page of Project Settings.


#include "DataTableManager.h"
#include "Engine/Texture.h"

#include "MovableStaticMeshActor.h"


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
	case Caption:
		CaptionData = Data;
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

FCaptionData UDataTableManager::GetCaption(const FName &RowName)
{
	const FString ContextString(TEXT("Caption Data"));
	FCaptionData *data = CaptionData->FindRow<FCaptionData>(RowName, ContextString);
	return data ? *data : FCaptionData();
}
