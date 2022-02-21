// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstPersonCharacter.generated.h"

UCLASS()
class MAGICDETECTIVE_API AFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent *FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USceneComponent *ObjectHolder;

public:
	// Sets default values for this character's properties
	AFirstPersonCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	TSubclassOf<class UInteractionTipWidget> InteractionTipWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	USceneComponent *GetObjectHolder() const;

protected:
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	void InteractionKeyPressed();

	void InteractionKeyReleased();

public:
	UPROPERTY(EditAnywhere, Category = "Interaction")
	float InteractionDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Interaction")
	float LongPressedTime;

	bool bDetectHit;

private:
	UPROPERTY()
	class UInteractionTipWidget *interactionTipWidgetInstance;

	class AInteractiveActor *currentInteractiveActor;

	void DetectHit();

	// Interaction Input Start
	// Record key is pressed when detecting interactive object.
	bool isInteractionKeyPressed;

	// Key pressed time
	float interactionKeyPressedTime;

	// Interact with target Actor
	void Interact();

	// Long pressed interact with target Actor
	void LongPressedInteract();
	// Interaction Inpu End

};