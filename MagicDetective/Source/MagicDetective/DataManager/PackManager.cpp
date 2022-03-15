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
	PropertyStack.Remove(Name);

	if (CurrentSelectedProperty == Name)
	{
		CurrentSelectedProperty = "";
		OnSelectItem.Broadcast(ParseItemInfo("", FGameplayPropertyData()));
	}

	FGameplayPropertyData ItemData = GetGameInstance()->GetSubsystem<UDataTableManager>()->GetGameplayProperty(Name);
	FGameplayPropertyInfo ItemInfo = ParseItemInfo(Name, ItemData);
	OnRemoveItem.Broadcast(ItemInfo);
}

void UPackManager::SelectProperty(const FName &ID)
{
	CurrentSelectedProperty = ID;

	FGameplayPropertyData ItemData = GetGameInstance()->GetSubsystem<UDataTableManager>()->GetGameplayProperty(ID);
	FGameplayPropertyInfo ItemInfo = ParseItemInfo(ID, ItemData);
	OnSelectItem.Broadcast(ItemInfo);
}

TSubclassOf<AMovableActor> UPackManager::GetSelectedProperty(bool bRemoveFromPack)
{
	if (!CurrentSelectedProperty.IsNone())
	{
		if (bRemoveFromPack)
		{
			RemoveFromPack(CurrentSelectedProperty);
		}

		FGameplayPropertyData PropertyData = GetGameInstance()->GetSubsystem<UDataTableManager>()->GetGameplayProperty(CurrentSelectedProperty);
		return PropertyData.BlueprintActor;
	}
	return nullptr;
}

TSubclassOf<class AMovableActor> UPackManager::GetPropertyByName(const FName &Name)
{
	FGameplayPropertyData PropertyData = GetGameInstance()->GetSubsystem<UDataTableManager>()->GetGameplayProperty(Name);
	return PropertyData.BlueprintActor;
}

FGameplayPropertyInfo UPackManager::ParseItemInfo(const FName &ID, const FGameplayPropertyData &ItemData)
{
	UTexture2D *IconTexture = Cast<UTexture2D>(ItemData.Icon.Get());
	FGameplayPropertyInfo ItemInfo;
	ItemInfo.ID = ID;
	ItemInfo.Icon = IconTexture;
	return ItemInfo;
}
