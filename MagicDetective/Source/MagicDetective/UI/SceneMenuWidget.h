// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SceneMenuWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FHideSceneMenuDelegate)

UCLASS()
class MAGICDETECTIVE_API USceneMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UButton *Button_Resume;
	
	UPROPERTY(meta = (BindWidget))
	class UButton *Button_MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UButton *Button_QuitGame;

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnOpenMainMenu();

public:
	FHideSceneMenuDelegate OnHideSceneMenu;

private:
	UFUNCTION()
	void Resume();

	UFUNCTION()
	void OpenMainMenu();

	UFUNCTION()
	void QuitGame();
};
