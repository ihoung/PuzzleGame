// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"
#include "UserWidgetManager.h"
#include "PackManager.h"

UMainGameInstance::UMainGameInstance(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
{
	InitDataMgr();
}

void UMainGameInstance::InitDataMgr()
{
	UIMgr = NewObject<UUserWidgetManager>();
	PackMgr = NewObject<UPackManager>();
}

UUserWidgetManager *UMainGameInstance::GetUIMgr() const
{
	return UIMgr;
}

UPackManager *UMainGameInstance::GetPackMgr() const
{
	return PackMgr;
}
