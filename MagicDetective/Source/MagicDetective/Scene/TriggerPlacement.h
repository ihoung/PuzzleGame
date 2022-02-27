// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerPlacement.generated.h"

/**
 * 
 */
UCLASS()
class MAGICDETECTIVE_API ATriggerPlacement : public ATriggerBox
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Placement", meta = (AllowPrivateAccess = "true"))
	class USceneComponent *PlacementComponent;

public:
	ATriggerPlacement();

	UFUNCTION(BlueprintCallable)
	class USceneComponent *GetPlacementComponent() const;
};
