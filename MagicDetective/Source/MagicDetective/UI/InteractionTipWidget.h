// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionTipWidget.generated.h"

/**
 * 
 */
UCLASS()
class MAGICDETECTIVE_API UInteractionTipWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox *HorizontalBox_InteractionHint;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *TextBlock_CenterHint;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *TextBlock_DropHint;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *TextBlock_CollectHint;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *TextBlock_PlaceHint;
	
public:
	UFUNCTION()
	void SetCenterHintText(FString text);

	UFUNCTION()
	void InteractMode();

	UFUNCTION()
	void HoldMode();

	UFUNCTION()
	void HoldAndTriggerMode();
};
