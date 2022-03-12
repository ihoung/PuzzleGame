// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PackWidget.generated.h"

/**
 * 
 */
UCLASS()
class MAGICDETECTIVE_API UPackWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox *VerticalBox_ItemContainer;

	UPROPERTY(meta = (BindWidget))
	class UBorder *Border_SelectedItem;

	UPROPERTY(meta = (BindWidget))
	class UPackItemWidget *CurrentSelectedItem;

private:
	UPROPERTY()
	TMap<FName, class UPackItemWidget *> ItemStack;

	class UPackManager *PackManager;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Elements")
	TSubclassOf<UUserWidget> PackItemWidget;

	UFUNCTION(BlueprintImplementableEvent)
	void OpenOrHidePack();

private:
	void AddItem(const struct FGameplayPropertyInfo &ItemInfo);
	void RemoveItem(const struct FGameplayPropertyInfo &ItemInfo);
	void OnItemSelected(const struct FGameplayPropertyInfo &ItemInfo);

};
