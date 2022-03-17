// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionHintWidget.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"


void UInteractionHintWidget::InteractMode(FString info)
{
	HorizontalBox_InteractionHint->SetVisibility(ESlateVisibility::Visible);
	TextBlock_DropHint->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_CollectHint->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_PlaceHint->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_Exit->SetVisibility(ESlateVisibility::Hidden);

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
	TextBlock_Exit->SetVisibility(ESlateVisibility::Hidden);
}

void UInteractionHintWidget::HoldAndTriggerMode()
{
	HorizontalBox_InteractionHint->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_DropHint->SetVisibility(ESlateVisibility::Visible);
	TextBlock_CollectHint->SetVisibility(ESlateVisibility::Visible);
	TextBlock_PlaceHint->SetVisibility(ESlateVisibility::Visible);
	TextBlock_Exit->SetVisibility(ESlateVisibility::Hidden);
}

void UInteractionHintWidget::FocusMode()
{
	HorizontalBox_InteractionHint->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_DropHint->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_CollectHint->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_PlaceHint->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_Exit->SetVisibility(ESlateVisibility::Visible);

}

