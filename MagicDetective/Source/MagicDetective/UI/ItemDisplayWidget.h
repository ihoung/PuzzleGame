// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemDisplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class MAGICDETECTIVE_API UItemDisplayWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UBorder *Border_DisplayItem;

public:
	UItemDisplayWidget(const FObjectInitializer &ObjectInitializer);

	UFUNCTION(BlueprintCallable)
	void ShowItem(TSubclassOf<class AMovableStaticMeshActor> ItemBlueprint);

protected:
	virtual void NativeOnInitialized() override;

	//virtual FReply NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent);

	//virtual FReply NativeOnMouseMove(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent) override;

	//virtual FReply NativeOnMouseButtonUp(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent);

	virtual FReply NativeOnMouseWheel(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Overlay 3D Target")
	class UMaterialInterface *DisplayMaterialAsset;

	UPROPERTY(EditDefaultsOnly, Category = "Overlay 3D Target")
	FName TextureParameterName;
	
	UPROPERTY(EditDefaultsOnly, Category = "Overlay 3D Target")
	TSubclassOf<class AItemCapture> ItemCapture;

	UPROPERTY(EditDefaultsOnly, Category = "Overlay 3D Target")
	FVector ItemCaptureLocation;

private:
	class AItemCapture *ItemCaptureInstance;

	class UMaterialInstanceDynamic *DynamicDisplayMaterial;

	// Mouse rotate item
	//bool bIsClickedInArea;
	bool bIsMouseLeftButtonPressed;

	UFUNCTION()
	FEventReply MouseButtonDownInArea(FGeometry MyGeometry, const FPointerEvent &MouseEvent);

	UFUNCTION()
	FEventReply MouseMoveInArea(FGeometry MyGeometry, const FPointerEvent &MouseEvent);

	UFUNCTION()
	FEventReply MouseButtonUpInArea(FGeometry MyGeometry, const FPointerEvent &MouseEvent);
};
