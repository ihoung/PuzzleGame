// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "MovableActor.generated.h"

/**
 * 
 */
UCLASS()
class MAGICDETECTIVE_API AMovableActor : public AInteractiveActor
{
	GENERATED_BODY()
	
public:
	AMovableActor();

	UFUNCTION()
	virtual void Interact(AActor *Source) override;

	UFUNCTION()
	virtual void LongPressedInteract(AActor *Source) override;

	UFUNCTION()
	virtual void DisplayInteractionHint() override;

	UFUNCTION()
	virtual void CloseInteractionHint() override;

private:
	// hint widget cache
	UPROPERTY()
	class UInteractionTipWidget *hintWidget;

	UFUNCTION()
	void BindInput();

	UFUNCTION()
	void UnbindInput();

	UFUNCTION()
	void Drop();

	UFUNCTION()
	void CollectToPack();

};
