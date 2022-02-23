// Fill out your copyright notice in the Description page of Project Settings.


#include "MainSceneLevelScriptActor.h"
#include "MainGameInstance.h"

void AMainSceneLevelScriptActor::BeginPlay()
{
	UMainGameInstance *gameInstance = Cast<UMainGameInstance>(GetGameInstance());
	if (gameInstance)
	{
		gameInstance->InitDataMgr();
	}
}