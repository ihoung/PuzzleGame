// Fill out your copyright notice in the Description page of Project Settings.


#include "PackManager.h"
#include "DataTableManager.h"

void UPackManager::Initialize(FSubsystemCollectionBase &Collection)
{
	Super::Initialize(Collection);
}

void UPackManager::Deinitialize()
{
	OnAddItem.Clear();
	OnRemoveItem.Clear();
	OnSelectItem.Clear();
}

void UPackManager::AddToPack(const FName &Name)
{
	PropertyStack.Add(Name);
	if (CurrentSelectedProperty.IsNone())
	{
		SelectProperty(Name);
	}

	FGameplayPropertyData ItemData = GetGameInstance()->GetSubsystem<UDataTableManager>()->GetGameplayProperty(Name);
	FGameplayPropertyInfo ItemInfo = ParseItemInfo(Name, ItemData);
	OnAddItem.Broadcast(ItemInfo);
}

void UPackManager::RemoveFromPack(const FName &Name)
{
	FGameplayPropertyData ItemData = GetGameInstance()->GetSubsystem<UDataTableManager>()->GetGameplayProperty(Name);
	FGameplayPropertyInfo ItemInfo = ParseItemInfo(Name, ItemData);
	OnRemoveItem.Broadcast(ItemInfo);

	if (CurrentSelectedProperty == Name)
	{
		CurrentSelectedProperty = "";
		OnSelectItem.Broadcast(ParseItemInfo("", FGameplayPropertyData()));
	}

	PropertyStack.Remove(Name);
}

void UPackManager::SelectProperty(const FName &ID)
{
	CurrentSelectedProperty = ID;

	FGameplayPropertyData ItemData = GetGameInstance()->GetSubsystem<UDataTableManager>()->GetGameplayProperty(ID);
	FGameplayPropertyInfo ItemInfo = ParseItemInfo(ID, ItemData);
	OnSelectItem.Broadcast(ItemInfo);
}

TSubclassOf<class AMovableStaticMeshActor> UPackManager::GetSelectedProperty(bool bRemoveFromPack)
{
	if (!CurrentSelectedProperty.IsNone())
	{
		FGameplayPropertyData PropertyData = GetGameInstance()->GetSubsystem<UDataTableManager>()->GetGameplayProperty(CurrentSelectedProperty);

		if (bRemoveFromPack)
		{
			RemoveFromPack(CurrentSelectedProperty);
		}

		return PropertyData.BlueprintActor;
	}
	return nullptr;
}

TSubclassOf<class AMovableStaticMeshActor> UPackManager::GetPropertyByName(const FName &Name)
{
	FGameplayPropertyData PropertyData = GetGameInstance()->GetSubsystem<UDataTableManager>()->GetGameplayProperty(Name);
	return PropertyData.BlueprintActor;
}

FGameplayPropertyInfo UPackManager::ParseItemInfo(const FName &ID, const FGameplayPropertyData &ItemData)
{
	UTexture2D *IconTexture = Cast<UTexture2D>(ItemData.Icon);
	FGameplayPropertyInfo ItemInfo;
	ItemInfo.ID = ID;
	ItemInfo.Icon = IconTexture;
	return ItemInfo;
}
