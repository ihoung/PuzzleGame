// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/InteractiveActor.h"
#include "MovableStaticMeshActor.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FPlaceMovableActorDelegate, AMovableStaticMeshActor *)
DECLARE_MULTICAST_DELEGATE_OneParam(FAttachToCharacterDelegate, AMovableStaticMeshActor *)
DECLARE_DELEGATE_OneParam(FDetachToCharacterDelegate, AMovableStaticMeshActor *)

UCLASS()
class MAGICDETECTIVE_API AMovableStaticMeshActor : public AInteractiveActor
{
	GENERATED_BODY()
	
	UPROPERTY(Category = StaticMeshActor, VisibleAnywhere, BlueprintReadOnly, meta = (ExposeFunctionCategories = "Mesh,Rendering,Physics,Components|StaticMesh", AllowPrivateAccess = "true"))
	class UStaticMeshComponent *StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent *AttachedPivotComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PropertyInformation", meta = (AllowPrivateAccess = true))
	FName DataID;

public:
	AMovableStaticMeshActor();

	virtual void Interact_Implementation() override;

	virtual void LongPressedInteract_Implementation() override;

	UFUNCTION()
	virtual void ShowInteractionHint_Implementation() override;

	UFUNCTION()
	virtual void HideInteractionHint_Implementation() override;

	UFUNCTION(BlueprintCallable)
	class UStaticMeshComponent *GetStaticMeshComponent() const;

	UFUNCTION()
	USceneComponent *GetAttachedPivotComponent() const;

	UFUNCTION(BlueprintNativeEvent)
	void OnAllTriggerPaired();

	bool bDetectTrigger;

	FPlaceMovableActorDelegate PlaceDelegate;
	FAttachToCharacterDelegate AttachToCharacterDelegate;
	FDetachToCharacterDelegate DetachToCharacterDelegate;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	FString InteractionName;

private:
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
