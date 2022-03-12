// Fill out your copyright notice in the Description page of Project Settings.


#include "CaptionWidget.h"
#include "Components/TextBlock.h"


UCaptionWidget::UCaptionWidget(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
{
	PlayerSpeed = 0.05f;
}

void UCaptionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	bShouldWait = false;
}

void UCaptionWidget::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Text play time
	TextPlayerTimer += InDeltaTime;
	if (TextPlayerTimer >= MaxTimeLength)
	{
		bShouldWait = false;

		if (TextQueue.Num() != 0)
		{
			FString textContent = TextQueue[0];
			TextQueue.RemoveAt(0);

			ShowCaption(textContent, true);

			return;
		}

		OnCaptionEnd.ExecuteIfBound();
	}
}

void UCaptionWidget::ShowCaption(const FString &TextContent, bool IsForcedToFinish)
{
	if (bShouldWait)
	{
		if (IsForcedToFinish)
		{
			TextQueue.Add(TextContent);
		}

		return;
	}

	MaxTimeLength = TextContent.Len() * PlayerSpeed;
	TextPlayerTimer = 0.f;

	TextBlock_Caption->SetText(FText::FromString(TextContent));

	if (IsForcedToFinish)
	{
		bShouldWait = true;
	}
}
