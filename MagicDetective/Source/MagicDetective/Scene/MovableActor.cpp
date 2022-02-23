// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableActor.h"

#include "MainGameInstance.h"
#include "UserWidgetManager.h"
#include "InteractionTipWidget.h"
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

	// Change display content of hint widget
	UMainGameInstance *gameInstance = Cast<UMainGameInstance>(GetGameInstance());
	if (gameInstance)
	{
		hintWidget = Cast<UInteractionTipWidget>(gameInstance->GetUIMgr()->Display(EUIType::InteractionHint));
		if (hintWidget)
		{
			hintWidget->HoldMode();
		}
	}

}

void AMovableActor::LongPressedInteract(AActor *Source)
{
	Super::LongPressedInteract(Source);

	// Collect into pack.	
	CollectToPack();
}

void AMovableActor::DisplayInteractionHint()
{
	UMainGameInstance *gameInstance = Cast<UMainGameInstance>(GetGameInstance());
	if (gameInstance)
	{
		hintWidget = Cast<UInteractionTipWidget>(gameInstance->GetUIMgr()->Display(EUIType::InteractionHint, TEXT("Move")));
		if (hintWidget)
		{
			hintWidget->InteractMode();
		}
	}
}

void AMovableActor::CloseInteractionHint()
{
	UMainGameInstance *gameInstance = Cast<UMainGameInstance>(GetGameInstance());
	if (gameInstance)
	{
		gameInstance->GetUIMgr()->Close(EUIType::InteractionHint);
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

	CloseInteractionHint();
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
	CloseInteractionHint();

	Destroy();
}
