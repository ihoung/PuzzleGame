// Fill out your copyright notice in the Description page of Project Settings.


#include "PackWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Overlay.h"
#include "Components/Image.h"

#include "PackItemWidget.h"
#include "PackManager.h"
#include "DataTableManager.h"


void UPackWidget::NativeOnInitialized()
{
    // Register with delegate
    PackManager = GetGameInstance()->GetSubsystem<UPackManager>();
    PackManager->OnAddItem.AddUObject(this, &UPackWidget::AddItem);
    PackManager->OnRemoveItem.AddUObject(this, &UPackWidget::RemoveItem);
    PackManager->OnSelectItem.AddUObject(this, &UPackWidget::OnItemSelected);

    Overlay_SelectedItem->SetVisibility(ESlateVisibility::Hidden);
}

void UPackWidget::AddItem(const FGameplayPropertyInfo &ItemInfo)
{
    UPackItemWidget *ItemWidget = CreateWidget<UPackItemWidget>(GetWorld(), PackItemWidget);
    if (ItemWidget)
    {
        VerticalBox_ItemContainer->AddChildToVerticalBox(ItemWidget);

        ItemWidget->SetData(ItemInfo);
        ItemWidget->OnItemSelected.BindUObject(PackManager, &UPackManager::SelectProperty);

        ItemStack.Add(ItemInfo.ID, ItemWidget);
    }
}

void UPackWidget::RemoveItem(const FGameplayPropertyInfo &ItemInfo)
{
    if (ItemStack.Contains(ItemInfo.ID))
    {
        UPackItemWidget *ItemWidget = ItemStack[ItemInfo.ID];
        ItemWidget->OnItemSelected.Unbind();

        VerticalBox_ItemContainer->RemoveChild(ItemWidget);
        ItemStack.Remove(ItemInfo.ID);
    }
}

void UPackWidget::OnItemSelected(const FGameplayPropertyInfo &ItemInfo)
{
    if (ItemInfo.ID.IsNone())
    {
        Overlay_SelectedItem->SetVisibility(ESlateVisibility::Hidden);
    }
    else
    {
        if (!Overlay_SelectedItem->IsVisible())
        {
            Overlay_SelectedItem->SetVisibility(ESlateVisibility::Visible);
        }

        Image_CurrentSelectedItem->SetBrushFromTexture(ItemInfo.Icon);
    }
}
