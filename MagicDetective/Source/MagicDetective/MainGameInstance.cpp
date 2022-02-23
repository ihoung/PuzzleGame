// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"
#include "UserWidgetManager.h"
#include "PackManager.h"

UMainGameInstance::UMainGameInstance(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
{

}

void UMainGameInstance::InitDataMgr()
{
	UIMgr = NewObject<UUserWidgetManager>(this, Blueprint_UIManager);
	PackMgr = NewObject<UPackManager>();
}

UUserWidgetManager *UMainGameInstance::GetUIMgr() const
{
	if (UIMgr == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UIManager wasn't initialized!"));
	}
	return UIMgr ? UIMgr : NewObject<UUserWidgetManager>();
}

UPackManager *UMainGameInstance::GetPackMgr() const
{
	if (UIMgr == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PackManager wasn't initialized!"));
	}
	return PackMgr ? PackMgr : NewObject<UPackManager>();
}
