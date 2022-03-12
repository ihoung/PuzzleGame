// Fill out your copyright notice in the Description page of Project Settings.


#include "PackItemWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"

#include "PackManager.h"
#include "DataTableManager.h"


void UPackItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Button_Select->OnClicked.AddDynamic(this, &UPackItemWidget::SelectItem);
}

void UPackItemWidget::SetData(const FGameplayPropertyInfo &ItemInfo)
{
	ItemID = ItemInfo.ID;
	Image_Icon->SetBrushFromTexture(ItemInfo.Icon, true);
}

void UPackItemWidget::SelectItem()
{
	OnItemSelected.ExecuteIfBound(ItemID);
}
