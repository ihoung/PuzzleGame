// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableActor.h"
#include "Kismet/GameplayStatics.h"

#include "MainSceneHUD.h"
#include "PackManager.h"


AMovableActor::AMovableActor() :Super()
{
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	GetStaticMeshComponent()->SetSimulatePhysics(true);

	bDetectTrigger = false;
}

void AMovableActor::Interact()
{
	Super::Interact();

	// Pick up and hold this object.
	GetStaticMeshComponent()->SetSimulatePhysics(false);

	AttachToCharacterDelegate.Broadcast(this);

	BindInput();

	// Change display content of hint widget
	APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AMainSceneHUD *HUD = PC->GetHUD<AMainSceneHUD>();
	HUD->ShowInteractionHint(EInteractionHintMode::Hold);
}

void AMovableActor::LongPressedInteract()
{
	Super::LongPressedInteract();

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
	DetachToCharacterDelegate.ExecuteIfBound(this);

	UnbindInput();

	GetStaticMeshComponent()->SetSimulatePhysics(true);

	HideInteractionHint();
}

void AMovableActor::CollectToPack()
{
	// Add to Pack
	GetGameInstance()->GetSubsystem<UPackManager>()->AddToPack(DataID);

	DetachToCharacterDelegate.ExecuteIfBound(this);

	UnbindInput();
	HideInteractionHint();

	Destroy();
}

void AMovableActor::Place()
{
	if (bDetectTrigger)
	{
		PlaceDelegate.ExecuteIfBound(this);

		DetachToCharacterDelegate.ExecuteIfBound(this);

		UnbindInput();
		HideInteractionHint();
	}
}

void AMovableActor::OnAllTriggerPaired_Implementation()
{
}
