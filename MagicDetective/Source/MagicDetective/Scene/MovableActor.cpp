// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableActor.h"
#include "FirstPersonCharacter.h"

AMovableActor::AMovableActor() :Super()
{
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
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
}

void AMovableActor::LongPressedInteract(AActor *Source)
{
	Super::LongPressedInteract(Source);

	// Collect into pack.	
	CollectToPack();
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
	Destroy();
}
