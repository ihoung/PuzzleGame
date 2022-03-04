// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InteractionHintWidget.h"

#include "MainSceneHUD.generated.h"

/**
 * 
 */
UCLASS()
class MAGICDETECTIVE_API AMainSceneHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "ZOrder")
	TMap<TSubclassOf<class UUserWidget>, int32> WidgetZOrder;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UInteractionHintWidget> InteractionHintWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UCaptionWidget> CaptionWidget;

private:
	// Keep a pointer to be able to hide it
	UPROPERTY()
	class UInteractionHintWidget *InteractionHint;

	UPROPERTY()
	class UCaptionWidget *Caption;

	TArray<class UUserWidget *> PageStack;

public:
	// Methods of Interaction Hint Widget
	UFUNCTION(BlueprintCallable)
	void ShowInteractionHint(enum EInteractionHintMode Mode, FString info = "");

	UFUNCTION(BlueprintCallable)
	void HideInteractionHint();

	// Methods of Caption Widget
	UFUNCTION(BlueprintCallable)
	void ShowCaption(const FString &TextContent = "", bool IsForcedToFinish = false);

	UFUNCTION(BlueprintCallable)
	void HideCaption();
};
