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
	virtual void ShowInteractionHint() override;

	UFUNCTION()
	virtual void HideInteractionHint() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Display")
	FString InteractionName;

	UPROPERTY(EditDefaultsOnly, Category = "Paired Trigger")
	TSubclassOf<class ATriggerPlacement> PairedTriggerClass;

	UFUNCTION()
	void BeginOverlap(class AActor *overlappedActor, class AActor *otherActor);

	UFUNCTION()
	void EndOverlap(class AActor *overlappedActor, class AActor *otherActor);

private:
	class ATriggerPlacement *DetectedTrigger;

	UFUNCTION()
	void BindInput();

	UFUNCTION()
	void UnbindInput();

	UFUNCTION()
	void Drop();

	UFUNCTION()
	void CollectToPack();

	UFUNCTION()
	void Place();

};
