// Fill out your copyright notice in the Description page of Project Settings.


#include "PackItemWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/KismetSystemLibrary.h"

#include "PackManager.h"
#include "DataTableManager.h"
#include "MainSceneHUD.h"
#include "PackManager.h"


UPackItemWidget::UPackItemWidget(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
{
	DoubleClickTimeSpan = 0.5f;
}

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

	FLatentActionInfo latenActionInfo;
	latenActionInfo.CallbackTarget = this;
	latenActionInfo.ExecutionFunction = "ResetClickCount";
	latenActionInfo.Linkage = 0;
	latenActionInfo.UUID = 1;
	UKismetSystemLibrary::RetriggerableDelay(GetWorld(), DoubleClickTimeSpan, latenActionInfo);

	ClickCount++;
	if (ClickCount >= 2)
	{
		TSubclassOf<AMovableStaticMeshActor> ItemSubclass = GetGameInstance()->GetSubsystem<UPackManager>()->GetPropertyByName(ItemID);
		GetGameInstance()->GetFirstLocalPlayerController()->GetHUD<AMainSceneHUD>()->ShowItemDisplay(ItemSubclass);
	}
}

void UPackItemWidget::ResetClickCount()
{
	ClickCount = 0;
}
