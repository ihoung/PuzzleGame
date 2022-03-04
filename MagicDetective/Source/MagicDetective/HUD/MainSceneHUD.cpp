// Fill out your copyright notice in the Description page of Project Settings.


#include "MainSceneHUD.h"
#include "Blueprint/UserWidget.h"

#include "CaptionWidget.h"

void AMainSceneHUD::ShowInteractionHint(EInteractionHintMode Mode, FString info)
{
	if (InteractionHint == nullptr)
	{
		InteractionHint = CreateWidget<UInteractionHintWidget>(GetWorld(), InteractionHintWidget);
	}
	if (InteractionHint)
	{
		if (!InteractionHint->IsInViewport())
		{
			int32 ZOrder = 0;
			if (WidgetZOrder.Contains(InteractionHintWidget))
			{
				ZOrder = WidgetZOrder[InteractionHintWidget];
			}
			InteractionHint->AddToViewport(ZOrder);
		}
		switch (Mode)
		{
		case EInteractionHintMode::Interact:
			InteractionHint->InteractMode(info);
			break;
		case EInteractionHintMode::Hold:
			InteractionHint->HoldMode();
			break;
		case EInteractionHintMode::HoldAndTrigger:
			InteractionHint->HoldAndTriggerMode();
			break;
		default:
			break;
		}
	}
}

void AMainSceneHUD::HideInteractionHint()
{
	if (InteractionHint)
	{
		InteractionHint->RemoveFromViewport();
	}
}

void AMainSceneHUD::ShowCaption(const FString &TextContent, bool IsForcedToFinish)
{
	if (Caption == nullptr)
	{
		Caption = CreateWidget<UCaptionWidget>(GetWorld(), CaptionWidget);
	}

	if (!Caption->IsInViewport())
	{
		Caption->OnCaptionEnd.BindUObject(this, &AMainSceneHUD::HideCaption);

		int32 ZOrder = 0;
		if (WidgetZOrder.Contains(CaptionWidget))
		{
			ZOrder = WidgetZOrder[CaptionWidget];
		}
		Caption->AddToViewport(ZOrder);
	}

	Caption->ShowCaption(TextContent, IsForcedToFinish);
}

void AMainSceneHUD::HideCaption()
{
	if (Caption->IsInViewport())
	{
		Caption->OnCaptionEnd.Unbind();
		Caption->RemoveFromViewport();
	}
}
