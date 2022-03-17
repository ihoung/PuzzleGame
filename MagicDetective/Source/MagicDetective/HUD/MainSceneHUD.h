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
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ZOrder", meta = (AllowPrivateAccess = true))
	TMap<TSubclassOf<class UUserWidget>, int32> WidgetZOrder;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Widgets", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UInteractionHintWidget> InteractionHintWidget;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Widgets", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UPackWidget> PackWidget;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Widgets", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UCaptionWidget> CaptionWidget;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Widgets", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UItemDisplayWidget> ItemDisplayWidget;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Widgets", meta = (AllowPrivateAccess = true))
	TSubclassOf<class USceneMenuWidget> SceneMenuWidget;

protected:
	virtual void BeginPlay() override;

private:
	// Keep a pointer to be able to hide it
	UPROPERTY()
	class UInteractionHintWidget *InteractionHint;

	UPROPERTY()
	class UCaptionWidget *Caption;

	class UPackWidget *Pack;

	class UItemDisplayWidget *ItemDisplay;

	class USceneMenuWidget *SceneMenu;

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

	// Methods of Pack Widget
	UFUNCTION(BlueprintCallable)
	void ShowPackWidget();

	UFUNCTION(BlueprintCallable)
	void OpenOrHidePack();

	// Methods of Item Display
	UFUNCTION(BlueprintCallable)
	void ShowItemDisplay(TSubclassOf<class AMovableStaticMeshActor> ItemBlueprint);

	UFUNCTION(BlueprintCallable)
	void HideItemDisplay();

	// Methods of Menu
	UFUNCTION(BlueprintCallable)
	void ShowMenu();

	UFUNCTION(BlueprintCallable)
	void HideMenu();
};
