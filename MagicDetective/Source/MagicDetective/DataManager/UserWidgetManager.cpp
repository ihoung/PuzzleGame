// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgetManager.h"
#include "Components/WidgetComponent.h"
#include "InteractionTipWidget.h"

UUserWidgetManager::UUserWidgetManager()
{

}

UUserWidget *UUserWidgetManager::Display(EUIType uiType)
{
	switch (uiType)
	{
	case EUIType::Hint:
		if (hintWidget == nullptr)
		{
			hintWidget = CreateWidget<UInteractionTipWidget>(GetWorld(), InteractionTipWidget);
			if (hintWidget == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Creating Hint Widget Failed!"));
				return nullptr;
			}
		}
		if (!hintWidget->IsInViewport())
		{
			hintWidget->AddToViewport((uint32)EUIType::Hint);
		}
		return hintWidget;
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
	case EUIType::Hint:
		if (hintWidget && hintWidget->IsInViewport())
		{
			hintWidget->RemoveFromViewport();
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