// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TriggerPlacement.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FOnCheckPairedActor, bool)

UCLASS()
class MAGICDETECTIVE_API ATriggerPlacement : public ATriggerBox
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Placement", meta = (AllowPrivateAccess = "true"))
	class USceneComponent *PlacementComponent;

	bool bIsChildAttached;
	class AMovableStaticMeshActor *AttachedChildActor;

protected:
	virtual void BeginPlay() override;

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

	UFUNCTION()
	void OnAllTriggersPaired();

	FOnCheckPairedActor OnCheckPairedActor;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	FString InteractionName;

	UPROPERTY(EditDefaultsOnly, Category = "Paired Actor")
	TSubclassOf<class AMovableStaticMeshActor> PlaceableActor;

	UPROPERTY(EditInstanceOnly, Category = "Paired Actor")
	TSubclassOf<class AMovableStaticMeshActor> PairedActor;

	UFUNCTION()
	void BeginOverlap(class AActor *overlappedActor, class AActor *otherActor);

	UFUNCTION()
	void EndOverlap(class AActor *overlappedActor, class AActor *otherActor);

private:
	UFUNCTION()
	void PlaceMovableActor(class AMovableStaticMeshActor *TargetActor);

	UFUNCTION()
	void DetachMovableActor(class AMovableStaticMeshActor *TargetActor);

	FDelegateHandle DetachDelegateHandle;

	void SetCollisionResponseToChannel(ECollisionChannel Channel, ECollisionResponse NewResponse);
};
