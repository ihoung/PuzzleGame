// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Btn_StartGame->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartGameBtnClicked);
	Btn_Quit->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitBtnClicked);
}

void UMainMenuWidget::OnStartGameBtnClicked()
{
	StartGame();
}

void UMainMenuWidget::OnQuitBtnClicked()
{
	UWorld *world = GetWorld();
	if (!ensure(world != nullptr)) return;

	APlayerController *playerCtrler = world->GetFirstPlayerController();
	if (!ensure(playerCtrler != nullptr)) return;

	//playerCtrler->ConsoleCommand("quit");

	UKismetSystemLibrary::QuitGame(world, playerCtrler, EQuitPreference::Quit, false);
}
