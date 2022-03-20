// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

#include "InteractiveActor.h"
#include "MovableStaticMeshActor.h"
#include "TriggerPlacement.h"


// Sets default values
AFirstPersonCharacter::AFirstPersonCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	//FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a SceneComponent
	ObjectHolder = CreateDefaultSubobject<USceneComponent>(TEXT("ObjectHolder"));
	ObjectHolder->SetMobility(EComponentMobility::Movable);
	ObjectHolder->SetupAttachment(FirstPersonCameraComponent);

	InteractionDistance = 100.f;
	LongPressedTime = 2.0f;
	
	bCanDetectHit = true;

	isInteractionKeyPressed = false;
	interactionKeyPressedTime = 0.0f;
}

// Called when the game starts or when spawned
void AFirstPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirstPersonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bCanDetectHit)
	{
		DetectHit();
	}

	// Interaction Input (Long Pressed)
	if (currentInteractiveActor != nullptr)
	{
		if (isInteractionKeyPressed)
		{
			interactionKeyPressedTime += DeltaTime;
			if (interactionKeyPressedTime >= LongPressedTime)
			{
				LongPressedInteract();
				isInteractionKeyPressed = false;
			}
		}
	}
	else if (currentTrigger != nullptr)
	{

	}
	else
	{
		isInteractionKeyPressed = false;
	}
}

// Called to bind functionality to input
void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFirstPersonCharacter::MoveRight);

	// Bind rotation events
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	// Bind interaction events
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFirstPersonCharacter::InteractionKeyPressed);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AFirstPersonCharacter::InteractionKeyReleased);

}

void AFirstPersonCharacter::SetCharacterCollisionResponse(ECollisionChannel Channel, ECollisionResponse Response)
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(Channel, Response);
}

void AFirstPersonCharacter::ResetCharacterCollisionResponse()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
}

void AFirstPersonCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFirstPersonCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFirstPersonCharacter::InteractionKeyPressed()
{
	if (!isInteractionKeyPressed)
	{
		isInteractionKeyPressed = true;

		if (currentInteractiveActor != nullptr)
		{
			interactionKeyPressedTime = 0.f;
		}
	}
}

void AFirstPersonCharacter::InteractionKeyReleased()
{
	if (isInteractionKeyPressed && (currentInteractiveActor != nullptr || currentTrigger != nullptr))
	{
		Interact();
	}

	isInteractionKeyPressed = false;
}

void AFirstPersonCharacter::SetDetectionHitActive(bool NewActive)
{
	bCanDetectHit = NewActive;
}

void AFirstPersonCharacter::DetectHit()
{
	FHitResult outHit;
	FVector startLocation = FirstPersonCameraComponent->GetComponentLocation();
	FVector forwardVector = FirstPersonCameraComponent->GetForwardVector();
	FVector endLocation = startLocation + forwardVector * InteractionDistance;

	FCollisionQueryParams collisionQueryParams;
	collisionQueryParams.bTraceComplex = false;
	collisionQueryParams.bReturnPhysicalMaterial = false;

	if (GetWorld()->LineTraceSingleByChannel(outHit, startLocation, endLocation, ECC_Visibility, collisionQueryParams))
	{
		if (outHit.bBlockingHit)
		{
			//if (GEngine)
			//{
			//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *outHit.GetActor()->GetName()));
			//}

			AActor *hitActor = outHit.GetActor();
			if (hitActor->IsA(AInteractiveActor::StaticClass()))
			{
				currentInteractiveActor = Cast<AInteractiveActor>(hitActor);

				// visualize widget of interaction tip
				currentInteractiveActor->ShowInteractionHint();

				return;
			}
			else if (hitActor->IsA(ATriggerPlacement::StaticClass()))
			{
				ATriggerPlacement *TriggerPlacement = Cast<ATriggerPlacement>(hitActor);
				if (!TriggerPlacement->HasChildActorAttached())
				{
					currentTrigger = TriggerPlacement;
					currentTrigger->ShowInteractionHint();
				}

				return;
			}
		}
	}

	if (currentInteractiveActor)
	{
		// invisualize widget of interaction tip
		currentInteractiveActor->HideInteractionHint();
		currentInteractiveActor = nullptr;
	}
	else if (currentTrigger)
	{
		currentTrigger->HideInteractionHint();
		currentTrigger = nullptr;
	}
}

void AFirstPersonCharacter::Interact()
{
	if (currentInteractiveActor != nullptr)
	{
		AMovableStaticMeshActor *targetActor = Cast<AMovableStaticMeshActor>(currentInteractiveActor);
		if (targetActor)
		{
			DetachDelegateHandle = targetActor->AttachToCharacterDelegate.AddUObject(this, &AFirstPersonCharacter::AttachMovableActor);
			targetActor->DetachToCharacterDelegate.BindUObject(this, &AFirstPersonCharacter::DetachMovableActor);
		}

		currentInteractiveActor->Interact();
	}
	else if (currentTrigger != nullptr)
	{
		currentTrigger->PlaceFromPack();
	}
}

void AFirstPersonCharacter::LongPressedInteract()
{
	if (currentInteractiveActor != nullptr)
	{
		currentInteractiveActor->LongPressedInteract();
	}
}

void AFirstPersonCharacter::AttachMovableActor(AMovableStaticMeshActor *TargetActor)
{
	TargetActor->AttachToComponent(ObjectHolder, FAttachmentTransformRules::KeepWorldTransform);
	bCanDetectHit = false;
}

void AFirstPersonCharacter::DetachMovableActor(AMovableStaticMeshActor *TargetActor)
{
	TargetActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	bCanDetectHit = true;

	TargetActor->AttachToCharacterDelegate.Remove(DetachDelegateHandle);
	TargetActor->DetachToCharacterDelegate.Unbind();
}


