// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

#include "InteractiveActor.h"
#include "InteractionHintWidget.h"


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
	
	bDetectHit = true;

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

	if (bDetectHit)
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

USceneComponent *AFirstPersonCharacter::GetObjectHolder() const
{
	return ObjectHolder;
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
	if (!isInteractionKeyPressed && currentInteractiveActor != nullptr)
	{
		isInteractionKeyPressed = true;
		interactionKeyPressedTime = 0.f;
	}
}

void AFirstPersonCharacter::InteractionKeyReleased()
{
	if (isInteractionKeyPressed && currentInteractiveActor != nullptr)
	{
		Interact();
	}

	isInteractionKeyPressed = false;
}

void AFirstPersonCharacter::DetectHit()
{
	FHitResult outHit;
	FVector startLocation = FirstPersonCameraComponent->GetComponentLocation();
	FVector forwardVector = FirstPersonCameraComponent->GetForwardVector();
	FVector endLocation = startLocation + forwardVector * InteractionDistance;

	FCollisionQueryParams collisionParams;
	collisionParams.bTraceComplex = false;
	collisionParams.bReturnPhysicalMaterial = false;

	if (GetWorld()->LineTraceSingleByChannel(outHit, startLocation, endLocation, ECC_Visibility, collisionParams))
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
		}
	}

	if (currentInteractiveActor)
	{
		// invisualize widget of interaction tip
		currentInteractiveActor->HideInteractionHint();
		currentInteractiveActor = nullptr;
	}
}

void AFirstPersonCharacter::Interact()
{
	if (currentInteractiveActor != nullptr)
	{
		currentInteractiveActor->Interact(this);
	}
}

void AFirstPersonCharacter::LongPressedInteract()
{
	if (currentInteractiveActor != nullptr)
	{
		currentInteractiveActor->LongPressedInteract(this);
	}
}


