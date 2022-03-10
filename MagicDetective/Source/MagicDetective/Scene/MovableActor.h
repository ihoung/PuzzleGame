// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "MovableActor.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FPlaceMovableActorDelegate, AMovableActor*)
DECLARE_MULTICAST_DELEGATE_OneParam(FAttachToCharacterDelegate, AMovableActor*)
DECLARE_DELEGATE_OneParam(FDetachToCharacterDelegate, AMovableActor*)

UCLASS()
class MAGICDETECTIVE_API AMovableActor : public AInteractiveActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PropertyInformation", meta = (AllowPrivateAccess = true))
	FName DataID;
	
public:
	AMovableActor();

	UFUNCTION()
	virtual void Interact() override;

	UFUNCTION()
	virtual void LongPressedInteract() override;

	UFUNCTION()
	virtual void ShowInteractionHint() override;

	UFUNCTION()
	virtual void HideInteractionHint() override;

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
