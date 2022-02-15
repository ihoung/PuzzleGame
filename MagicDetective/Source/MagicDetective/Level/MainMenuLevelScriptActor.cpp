// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuLevelScriptActor.h"
#include "Blueprint/UserWidget.h"

void AMainMenuLevelScriptActor::BeginPlay()
{
	UUserWidget *widget = CreateWidget<UUserWidget>(GetWorld(), Widget);
	if (widget)
	{
		widget->AddToViewport(0);
	}
}