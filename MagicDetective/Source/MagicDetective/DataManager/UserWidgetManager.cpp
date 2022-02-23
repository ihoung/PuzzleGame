// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetManager.h"
#include "Components/WidgetComponent.h"
#include "InteractionTipWidget.h"

UUserWidgetManager::UUserWidgetManager()
{

}

UUserWidget *UUserWidgetManager::Display(EUIType uiType, FString desc)
{
	switch (uiType)
	{
	case EUIType::InteractionHint:
		if (interactionHintWidget == nullptr)
		{
			interactionHintWidget = CreateWidget<UInteractionTipWidget>(GetWorld(), InteractionTipWidget);
			if (interactionHintWidget == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Creating Hint Widget Failed!"));
				return nullptr;
			}
		}
		if (!interactionHintWidget->IsInViewport())
		{
			interactionHintWidget->SetCenterHintText(desc);
			interactionHintWidget->AddToViewport((uint32)EUIType::InteractionHint);
		}
		return interactionHintWidget;
	case EUIType::Fixed:
		return nullptr;
	case EUIType::PopupWindow:
		return nullptr;
	default:
		return nullptr;
	}
}

void UUserWidgetManager::Close(EUIType uiType)
{
	switch (uiType)
	{
	case EUIType::InteractionHint:
		if (interactionHintWidget && interactionHintWidget->IsInViewport())
		{
			interactionHintWidget->RemoveFromViewport();
		}
		break;
	case EUIType::Fixed:
		break;
	case EUIType::PopupWindow:
		break;
	default:
		break;
	}
}
