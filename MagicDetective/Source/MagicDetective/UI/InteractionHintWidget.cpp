// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionHintWidget.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"

bool UInteractionHintWidget::Initialize()
{
	Super::Initialize();

	return true;
}

void UInteractionHintWidget::InteractMode(FString info)
{
	HorizontalBox_InteractionHint->SetVisibility(ESlateVisibility::Visible);
	TextBlock_DropHint->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_CollectHint->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_PlaceHint->SetVisibility(ESlateVisibility::Collapsed);

	if (!info.IsEmpty())
	{
		TextBlock_InteractionHint->SetText(FText::FromString(info));
	}
}

void UInteractionHintWidget::HoldMode()
{
	HorizontalBox_InteractionHint->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_DropHint->SetVisibility(ESlateVisibility::Visible);
	TextBlock_CollectHint->SetVisibility(ESlateVisibility::Visible);
	TextBlock_PlaceHint->SetVisibility(ESlateVisibility::Collapsed);
}

void UInteractionHintWidget::HoldAndTriggerMode()
{
	HorizontalBox_InteractionHint->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_DropHint->SetVisibility(ESlateVisibility::Visible);
	TextBlock_CollectHint->SetVisibility(ESlateVisibility::Visible);
	TextBlock_PlaceHint->SetVisibility(ESlateVisibility::Visible);
}
