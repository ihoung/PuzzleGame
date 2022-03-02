// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"
#include <GameFramework/PlayerController.h>
#include <Blueprint/UserWidget.h>
#include <Kismet/GameplayStatics.h>

void AMainMenuHUD::ShowMainMenu()
{
	// Make widget owned by our PlayerController
	APlayerController *PC = Cast<APlayerController>(GetOwner());
	MainMenu = CreateWidget<UUserWidget>(PC, MainMenuClass);

	if (MainMenu)
	{
		MainMenu->AddToViewport();
	}
}

void AMainMenuHUD::HideMainMenu()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD<AMainMenuHUD>();

	if (MainMenu)
	{
		MainMenu->RemoveFromViewport();
		MainMenu = nullptr;
	}
}
