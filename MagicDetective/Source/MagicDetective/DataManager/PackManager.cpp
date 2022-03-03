// Fill out your copyright notice in the Description page of Project Settings.


#include "PackManager.h"
#include "DataTableManager.h"

void UPackManager::Initialize(FSubsystemCollectionBase &Collection)
{
	Super::Initialize(Collection);
}

void UPackManager::Deinitialize()
{
}

void UPackManager::AddToPack(const FName &Name)
{
	PropertyStack.Add(Name);
	CurrentSelectedProperty = Name;
}

void UPackManager::RemoveFromPack(const FName &Name)
{
	PropertyStack.Remove(Name);
}

void UPackManager::SelectProperty(const FName &Name)
{
	CurrentSelectedProperty = Name;
}

TSubclassOf<AMovableActor> UPackManager::GetSelectedProperty()
{
	RemoveFromPack(CurrentSelectedProperty);
	FGameplayPropertyData PropertyData = GetGameInstance()->GetSubsystem<UDataTableManager>()->GetGameplayProperty(CurrentSelectedProperty);
	return PropertyData.BlueprintActor;	
}

