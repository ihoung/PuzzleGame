// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableActor.h"
#include "Kismet/GameplayStatics.h"

#include "MainSceneHUD.h"
#include "FirstPersonCharacter.h"
#include "TriggerPlacement.h"

AMovableActor::AMovableActor() :Super()
{
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	GetStaticMeshComponent()->SetSimulatePhysics(true);

	OnActorBeginOverlap.AddDynamic(this, &AMovableActor::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AMovableActor::EndOverlap);
}

void AMovableActor::Interact(AActor *Source)
{
	Super::Interact(Source);

	// Pick up and hold this object.
	GetStaticMeshComponent()->SetSimulatePhysics(false);

	AFirstPersonCharacter *source = Cast<AFirstPersonCharacter>(Source);
	if (source != nullptr)
	{
		AttachToComponent(source->GetObjectHolder(), FAttachmentTransformRules::KeepWorldTransform);

		source->bDetectHit = false;
		BindInput();
	}

	// Change display content of hint widget
	APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AMainSceneHUD *HUD = PC->GetHUD<AMainSceneHUD>();
	HUD->ShowInteractionHint(EInteractionHintMode::Hold);
}

void AMovableActor::LongPressedInteract(AActor *Source)
{
	Super::LongPressedInteract(Source);

	// Collect into pack.	
	CollectToPack();
}

void AMovableActor::ShowInteractionHint()
{
	APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AMainSceneHUD *HUD = PC->GetHUD<AMainSceneHUD>();
	HUD->ShowInteractionHint(EInteractionHintMode::Interact, InteractionName);
}

void AMovableActor::HideInteractionHint()
{
	APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AMainSceneHUD *HUD = PC->GetHUD<AMainSceneHUD>();
	HUD->HideInteractionHint();
}

void AMovableActor::BeginOverlap(AActor *overlappedActor, AActor *otherActor)
{
	if (otherActor && overlappedActor != otherActor)
	{
		if (otherActor->IsA(PairedTriggerClass))
		{
			DetectedTrigger = Cast<ATriggerPlacement>(otherActor);

			// Interaction hint widget
			APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			AMainSceneHUD *HUD = PC->GetHUD<AMainSceneHUD>();
			HUD->ShowInteractionHint(EInteractionHintMode::HoldAndTrigger);
		}
	}

}

void AMovableActor::EndOverlap(AActor *overlappedActor, AActor *otherActor)
{
	if (otherActor && overlappedActor != otherActor)
	{
		if (otherActor->IsA(PairedTriggerClass))
		{
			DetectedTrigger = nullptr;

			// Interaction hint widget
			APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			AMainSceneHUD *HUD = PC->GetHUD<AMainSceneHUD>();
			HUD->ShowInteractionHint(EInteractionHintMode::Hold);
		}
	}

}

void AMovableActor::BindInput()
{
	if (InputComponent)
	{
		InputComponent->DestroyComponent();
	}

	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent)
	{
		InputComponent->BindAction("Drop", IE_Pressed, this, &AMovableActor::Drop);
		InputComponent->BindAction("Collect", IE_Pressed, this, &AMovableActor::CollectToPack);
		InputComponent->BindAction("Place", IE_Pressed, this, &AMovableActor::Place);

		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

void AMovableActor::UnbindInput()
{
	if (InputComponent)
	{
		DisableInput(GetWorld()->GetFirstPlayerController());
		InputComponent->DestroyComponent();
	}
}

void AMovableActor::Drop()
{
	AFirstPersonCharacter *character = Cast<AFirstPersonCharacter>(GetAttachParentActor());
	if (character)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		character->bDetectHit = true;
	}

	UnbindInput();

	GetStaticMeshComponent()->SetSimulatePhysics(true);

	HideInteractionHint();
}

void AMovableActor::CollectToPack()
{
	AFirstPersonCharacter *character = Cast<AFirstPersonCharacter>(GetAttachParentActor());
	if(character)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		character->bDetectHit = true;
	}

	UnbindInput();
	HideInteractionHint();

	Destroy();
}

void AMovableActor::Place()
{
	if (DetectedTrigger)
	{
		AFirstPersonCharacter *character = Cast<AFirstPersonCharacter>(GetAttachParentActor());
		if (character)
		{
			AttachToComponent(DetectedTrigger->GetPlacementComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);

			character->bDetectHit = true;
		}

		UnbindInput();
		HideInteractionHint();

	}
}

