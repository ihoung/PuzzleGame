// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserWidgetManager.generated.h"

/**
 * 
 */
UENUM()
enum class EUIType : uint8
{
	InteractionHint = 0,
	Fixed = 10,
	PopupWindow = 50,
};

UCLASS(Blueprintable)
class MAGICDETECTIVE_API UUserWidgetManager : public UObject
{
	GENERATED_BODY()
	
public:
	UUserWidgetManager();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UInteractionTipWidget> InteractionTipWidget;

	UFUNCTION(BlueprintCallable)
	class UUserWidget *Display(EUIType UIType, FString desc = "");

	UFUNCTION(BlueprintCallable)
	void Close(EUIType UIType);

private:
	class UInteractionTipWidget *interactionHintWidget;

};
