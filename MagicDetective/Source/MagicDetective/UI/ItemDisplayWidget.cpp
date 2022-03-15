// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDisplayWidget.h"
#include "Materials/Material.h"
#include "Components/Border.h"
#include "Engine/TextureRenderTarget2D.h"

#include "MovableActor.h"
#include "ItemCapture.h"


UItemDisplayWidget::UItemDisplayWidget(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
{

}

void UItemDisplayWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//bIsClickedInArea = false;
	bIsMouseLeftButtonPressed = false;

	Border_DisplayItem->OnMouseButtonDownEvent.BindDynamic(this, &UItemDisplayWidget::MouseButtonDownInArea);
	Border_DisplayItem->OnMouseMoveEvent.BindDynamic(this, &UItemDisplayWidget::MouseMoveInArea);
	Border_DisplayItem->OnMouseButtonUpEvent.BindDynamic(this, &UItemDisplayWidget::MouseButtonUpInArea);

	// Spawn Item Capture
	ItemCaptureInstance = GetWorld()->SpawnActor<AItemCapture>(ItemCapture, ItemCaptureLocation, { 0.f,0.f,0.f });

	// Assign material to Image component
	DynamicDisplayMaterial = UMaterialInstanceDynamic::Create(DisplayMaterialAsset, GetWorld());
	if (DynamicDisplayMaterial)
	{
		DynamicDisplayMaterial->SetTextureParameterValue(TextureParameterName, ItemCaptureInstance->RenderTarget);
		Border_DisplayItem->SetBrushFromMaterial(DynamicDisplayMaterial);
	}
}

//FReply UItemDisplayWidget::NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
//{
//	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
//
//	if (bIsClickedInArea)
//	{
//		bIsMouseLeftButtonPressed = true;
//	}
//
//	return FReply::Handled();
//}
//
//FReply UItemDisplayWidget::NativeOnMouseMove(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
//{
//	Super::NativeOnMouseMove(InGeometry, InMouseEvent);
//
//	if (bIsMouseLeftButtonPressed)
//	{
//		ItemCaptureInstance->RotateItem(InMouseEvent.GetCursorDelta().X, InMouseEvent.GetCursorDelta().Y);
//	}
//	return FReply::Handled();
//}
//
//FReply UItemDisplayWidget::NativeOnMouseButtonUp(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
//{
//	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
//
//	bIsMouseLeftButtonPressed = false;
//
//	return FReply::Handled();
//}

FReply UItemDisplayWidget::NativeOnMouseWheel(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
	Super::NativeOnMouseWheel(InGeometry, InMouseEvent);

	ItemCaptureInstance->ZoomItem(InMouseEvent.GetWheelDelta());

	return FReply::Handled();
}

void UItemDisplayWidget::ShowItem(TSubclassOf<AMovableActor> ItemBlueprint)
{
	ItemCaptureInstance->DisplayItem(ItemBlueprint);
}

FEventReply UItemDisplayWidget::MouseButtonDownInArea(FGeometry MyGeometry, const FPointerEvent &MouseEvent)
{
	if (MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		bIsMouseLeftButtonPressed = true;
	}

	return FEventReply(true);
}

FEventReply UItemDisplayWidget::MouseMoveInArea(FGeometry MyGeometry, const FPointerEvent &MouseEvent)
{
	if (bIsMouseLeftButtonPressed)
	{
		ItemCaptureInstance->RotateItem(MouseEvent.GetCursorDelta().X, MouseEvent.GetCursorDelta().Y);
	}

	return FEventReply(true);
}

FEventReply UItemDisplayWidget::MouseButtonUpInArea(FGeometry MyGeometry, const FPointerEvent &MouseEvent)
{
	bIsMouseLeftButtonPressed = false;

	return FEventReply(true);
}
