// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UMainMenuWidget::Initialize()
{
	Super::Initialize();

	Btn_StartGame->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartGameBtnClicked);
	Btn_Quit->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitBtnClicked);

	return true;
}

void UMainMenuWidget::OnStartGameBtnClicked()
{
	UGameplayStatics::OpenLevel(this, MainLevel);
}

void UMainMenuWidget::OnQuitBtnClicked()
{
	UWorld *world = GetWorld();
	if (!ensure(world != nullptr)) return;

	APlayerController *playerCtrler = world->GetFirstPlayerController();
	if (!ensure(playerCtrler != nullptr)) return;

	playerCtrler->ConsoleCommand("quit");
}