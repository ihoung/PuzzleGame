// Fill out your copyright notice in the Description page of Project Settings.


#include "MainSceneHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMainSceneHUD::ShowInteractionHint(EInteractionHintMode Mode, FString info)
{
	if (InteractionHint == nullptr)
	{
		InteractionHint = CreateWidget<UInteractionHintWidget>(GetWorld(), InteractionHintClass);
	}
	if (InteractionHint)
	{
		if (!InteractionHint->IsInViewport())
		{
			int32 ZOrder = 0;
			if (WidgetZOrder.Contains(InteractionHintClass))
			{
				ZOrder = WidgetZOrder[InteractionHintClass];
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
