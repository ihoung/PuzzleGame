// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CaptionWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FOnCaptionEnd)

UCLASS()
class MAGICDETECTIVE_API UCaptionWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *TextBlock_Caption;

public:
	UCaptionWidget(const FObjectInitializer &ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "PlayerSetting")
	float PlayerSpeed;

public:
	void ShowCaption(const FString &TextContent, bool IsForcedToFinish = false);

	FOnCaptionEnd OnCaptionEnd;

private:
	// Whether should wait for finishing when new text content passed
	bool bShouldWait;

	// Timer of text player
	float TextPlayerTimer;

	// Current max playing time
	float MaxTimeLength;

	UPROPERTY()
	TArray<FString> TextQueue;
};
