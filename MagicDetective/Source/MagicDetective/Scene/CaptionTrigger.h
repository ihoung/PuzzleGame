// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CaptionTrigger.generated.h"

/**
 * 
 */
UCLASS()
class MAGICDETECTIVE_API ACaptionTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	ACaptionTrigger();

protected:
	UPROPERTY(EditInstanceOnly, Category = "Caption")
	FName CaptionID;

	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(class AActor *overlappedActor, class AActor *otherActor);

};
