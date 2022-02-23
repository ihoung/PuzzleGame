// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionTipWidget.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"

bool UInteractionTipWidget::Initialize()
{
	Super::Initialize();

	InteractMode();

	return true;
}

void UInteractionTipWidget::SetCenterHintText(FString text)
{
	TextBlock_CenterHint->SetText(FText::FromString(text));
}

void UInteractionTipWidget::InteractMode()
{
	HorizontalBox_InteractionHint->SetVisibility(ESlateVisibility::Visible);
	TextBlock_DropHint->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_CollectHint->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_PlaceHint->SetVisibility(ESlateVisibility::Collapsed);
}

void UInteractionTipWidget::HoldMode()
{
	HorizontalBox_InteractionHint->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_DropHint->SetVisibility(ESlateVisibility::Visible);
	TextBlock_CollectHint->SetVisibility(ESlateVisibility::Visible);
	TextBlock_PlaceHint->SetVisibility(ESlateVisibility::Collapsed);
}

void UInteractionTipWidget::HoldAndTriggerMode()
{
	HorizontalBox_InteractionHint->SetVisibility(ESlateVisibility::Collapsed);
	TextBlock_DropHint->SetVisibility(ESlateVisibility::Visible);
	TextBlock_CollectHint->SetVisibility(ESlateVisibility::Visible);
	TextBlock_PlaceHint->SetVisibility(ESlateVisibility::Visible);
}
