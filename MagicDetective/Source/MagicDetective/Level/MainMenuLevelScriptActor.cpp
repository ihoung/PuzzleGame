// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuLevelScriptActor.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

#include "MainMenuHUD.h"

void AMainMenuLevelScriptActor::BeginPlay()
{
	APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AMainMenuHUD *HUD = PC->GetHUD<AMainMenuHUD>();
	HUD->ShowMainMenu();
}