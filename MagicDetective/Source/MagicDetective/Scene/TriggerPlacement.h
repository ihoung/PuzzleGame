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

	bool bIsChildAttached;

public:
	ATriggerPlacement();

	UFUNCTION()
	virtual void ShowInteractionHint();

	UFUNCTION()
	virtual void HideInteractionHint();

	UFUNCTION()
	void PlaceFromPack();

	UFUNCTION()
	bool HasChildActorAttached() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	FString InteractionName;

	UPROPERTY(EditDefaultsOnly, Category = "Paired Actor")
	TSubclassOf<class AMovableActor> PairedActorClass;

	UFUNCTION()
	void BeginOverlap(class AActor *overlappedActor, class AActor *otherActor);

	UFUNCTION()
	void EndOverlap(class AActor *overlappedActor, class AActor *otherActor);

private:
	UFUNCTION()
	void PlaceMovableActor(class AMovableActor *TargetActor);

	UFUNCTION()
	void DetachMovableActor(class AMovableActor *TargetActor);

	FDelegateHandle DetachDelegateHandle;
};
