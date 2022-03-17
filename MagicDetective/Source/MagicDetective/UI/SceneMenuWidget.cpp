// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void USceneMenuWidget::NativeOnInitialized()
{
	Button_Resume->OnClicked.AddDynamic(this, &USceneMenuWidget::Resume);
	Button_MainMenu->OnClicked.AddDynamic(this, &USceneMenuWidget::OpenMainMenu);
	Button_QuitGame->OnClicked.AddDynamic(this, &USceneMenuWidget::QuitGame);
}

void USceneMenuWidget::Resume()
{
	OnHideSceneMenu.ExecuteIfBound();
}

void USceneMenuWidget::OpenMainMenu()
{
	OnOpenMainMenu();
}

void USceneMenuWidget::QuitGame()
{
	UWorld *world = GetWorld();
	if (!ensure(world != nullptr)) return;

	APlayerController *playerCtrler = world->GetFirstPlayerController();
	if (!ensure(playerCtrler != nullptr)) return;

	UKismetSystemLibrary::QuitGame(world, playerCtrler, EQuitPreference::Quit, false);
}
