// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PackItemWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FItemSelectedDelegate, const FName&)

UCLASS()
class MAGICDETECTIVE_API UPackItemWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UButton *Button_Select;

	UPROPERTY(meta = (BindWidget))
	class UImage *Image_Icon;

protected:
	virtual void NativeOnInitialized() override;

public:
	void SetData(const struct FGameplayPropertyInfo &ItemInfo);

	FItemSelectedDelegate OnItemSelected;

private:
	FName ItemID;

	UFUNCTION()
	void SelectItem();
};
