// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserWidgetManager.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MAGICDETECTIVE_API UUserWidgetManager : public UObject
{
	GENERATED_BODY()
	
public:
	UUserWidgetManager();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> interactionWidget;
};
