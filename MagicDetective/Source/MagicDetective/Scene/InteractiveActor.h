// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "InteractiveActor.generated.h"

/**
 * 
 */
UCLASS()
class MAGICDETECTIVE_API AInteractiveActor : public AActor
{
	GENERATED_BODY()

public:
	AInteractiveActor();

	UFUNCTION(BlueprintNativeEvent)
	void Interact();

	UFUNCTION(BlueprintNativeEvent)
	void LongPressedInteract();

	virtual void ShowInteractionHint();

	virtual void HideInteractionHint();

	UFUNCTION(BlueprintCallable)
	void SetInteractable(bool IsInteractable);

	UFUNCTION(BlueprintCallable)
	bool GetInteractable() const;

protected:
	bool bIsInteractable;
};
