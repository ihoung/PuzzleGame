// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MAGICDETECTIVE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public :
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Level)
	FName MainLevel;

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	void OpenNewLevel();

	UFUNCTION(BlueprintImplementableEvent)
	void OnStartGame();

private:
	UPROPERTY(meta = (BindWidget))
	class UButton *Btn_StartGame;

	UPROPERTY(meta = (BindWidget))
	class UButton *Btn_Quit;

	UFUNCTION()
	void OnStartGameBtnClicked();

	UFUNCTION()
	void OnQuitBtnClicked();
};
