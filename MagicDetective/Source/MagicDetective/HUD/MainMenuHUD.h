// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class MAGICDETECTIVE_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	// Make BlueprintCallable for testing
	UFUNCTION(BlueprintCallable)
	void ShowMainMenu();

	UFUNCTION(BlueprintCallable)
	void HideMainMenu();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> MainMenuClass;

	// Keep a pointer to be able to hide it
	UPROPERTY()
	class UUserWidget *MainMenu;
};
