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
	virtual bool Initialize() override;

};
