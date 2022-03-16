// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionHintWidget.generated.h"

/**
 * 
 */

UENUM()
enum class EInteractionHintMode : uint8
{
	Interact,
	Hold,
	HoldAndTrigger
};

UCLASS()
class MAGICDETECTIVE_API UInteractionHintWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
		class UHorizontalBox *HorizontalBox_InteractionHint;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock *TextBlock_InteractionHint;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock *TextBlock_DropHint;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock *TextBlock_CollectHint;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock *TextBlock_PlaceHint;

public:
	UFUNCTION()
	void InteractMode(FString info);

	UFUNCTION()
	void HoldMode();

	UFUNCTION()
	void HoldAndTriggerMode();

};
