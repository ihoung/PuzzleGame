// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableStaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "MainSceneHUD.h"
#include "PackManager.h"


AMovableStaticMeshActor::AMovableStaticMeshActor() :Super()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	StaticMeshComponent->Mobility = EComponentMobility::Movable;
	StaticMeshComponent->SetSimulatePhysics(true);

	AttachedPivotComponent = CreateDefaultSubobject<USceneComponent>(TEXT("AttachedPivot"));
	AttachedPivotComponent->SetupAttachment(StaticMeshComponent);

	bDetectTrigger = false;
}

UStaticMeshComponent *AMovableStaticMeshActor::GetStaticMeshComponent() const
{
	return StaticMeshComponent;
}

USceneComponent *AMovableStaticMeshActor::GetAttachedPivotComponent() const
{
	return AttachedPivotComponent;
}


void AMovableStaticMeshActor::Interact_Implementation()
{
	if (!bIsInteractable)
		return;

	Super::Interact_Implementation();

	// Pick up and hold this object.
	StaticMeshComponent->SetSimulatePhysics(false);

	AttachToCharacterDelegate.Broadcast(this);

	BindInput();

	// Change display content of hint widget
	APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AMainSceneHUD *HUD = PC->GetHUD<AMainSceneHUD>();
	HUD->ShowInteractionHint(EInteractionHintMode::Hold);
}

void AMovableStaticMeshActor::LongPressedInteract_Implementation()
{
	if (!bIsInteractable)
		return;

	Super::LongPressedInteract_Implementation();

	// Collect into pack.	
	CollectToPack();
}

void AMovableStaticMeshActor::ShowInteractionHint_Implementation()
{
	if (bIsInteractable)
	{
		APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AMainSceneHUD *HUD = PC->GetHUD<AMainSceneHUD>();
		HUD->ShowInteractionHint(EInteractionHintMode::Interact, InteractionName);
	}
}

void AMovableStaticMeshActor::HideInteractionHint_Implementation()
{
	APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AMainSceneHUD *HUD = PC->GetHUD<AMainSceneHUD>();
	HUD->HideInteractionHint();
}

void AMovableStaticMeshActor::BindInput()
{
	if (InputComponent)
	{
		InputComponent->DestroyComponent();
	}

	InputComponent = NewObject<UInputComponent>(this);
	InputComponent->RegisterComponent();
	if (InputComponent)
	{
		InputComponent->BindAction("Drop", IE_Pressed, this, &AMovableStaticMeshActor::Drop);
		InputComponent->BindAction("Collect", IE_Pressed, this, &AMovableStaticMeshActor::CollectToPack);
		InputComponent->BindAction("Place", IE_Pressed, this, &AMovableStaticMeshActor::Place);

		EnableInput(GetWorld()->GetFirstPlayerController());
	}
}

void AMovableStaticMeshActor::UnbindInput()
{
	if (InputComponent)
	{
		DisableInput(GetWorld()->GetFirstPlayerController());
		InputComponent->DestroyComponent();
	}
}

void AMovableStaticMeshActor::Drop()
{
	DetachToCharacterDelegate.ExecuteIfBound(this);

	UnbindInput();

	StaticMeshComponent->SetSimulatePhysics(true);

	HideInteractionHint();
}

void AMovableStaticMeshActor::CollectToPack()
{
	// Add to Pack
	GetGameInstance()->GetSubsystem<UPackManager>()->AddToPack(DataID);

	DetachToCharacterDelegate.ExecuteIfBound(this);

	UnbindInput();
	HideInteractionHint();

	Destroy();
}

void AMovableStaticMeshActor::Place()
{
	if (bDetectTrigger)
	{
		PlaceDelegate.ExecuteIfBound(this);

		DetachToCharacterDelegate.ExecuteIfBound(this);

		UnbindInput();
		HideInteractionHint();
	}
}

void AMovableStaticMeshActor::OnAllTriggerPaired_Implementation()
{
	bIsInteractable = false;
}
