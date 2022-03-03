// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPlacement.h"
#include "Kismet/GameplayStatics.h"

#include "MovableActor.h"
#include "MainSceneHUD.h"
#include "PackManager.h"


ATriggerPlacement::ATriggerPlacement() :Super()
{
	// Create a Placement
	PlacementComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Placement"));
	PlacementComponent->SetupAttachment(GetRootComponent());

	OnActorBeginOverlap.AddDynamic(this, &ATriggerPlacement::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ATriggerPlacement::EndOverlap);

}

void ATriggerPlacement::BeginOverlap(AActor *overlappedActor, AActor *otherActor)
{
	if (otherActor && overlappedActor != otherActor)
	{
		if (otherActor->IsA(PairedActorClass))
		{
			AMovableActor * DetectedActor = Cast<AMovableActor>(otherActor);
			DetectedActor->bDetectTrigger = true;

			DetectedActor->PlaceDelegate.BindUObject(this, &ATriggerPlacement::PlaceMovableActor);

			// Interaction hint widget
			APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			AMainSceneHUD *HUD = PC->GetHUD<AMainSceneHUD>();
			HUD->ShowInteractionHint(EInteractionHintMode::HoldAndTrigger);
		}
	}

}

void ATriggerPlacement::EndOverlap(AActor *overlappedActor, AActor *otherActor)
{
	if (otherActor && overlappedActor != otherActor)
	{
		if (otherActor->IsA(PairedActorClass))
		{
			AMovableActor *DetectedActor = Cast<AMovableActor>(otherActor);
			DetectedActor->bDetectTrigger = false;

			DetectedActor->PlaceDelegate.Unbind();

			// Interaction hint widget
			APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			AMainSceneHUD *HUD = PC->GetHUD<AMainSceneHUD>();
			HUD->ShowInteractionHint(EInteractionHintMode::Hold);
		}
	}

}

void ATriggerPlacement::PlaceMovableActor(AMovableActor *TargetActor)
{
	if (TargetActor)
	{
		TargetActor->AttachToComponent(PlacementComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		if (TargetActor->PlaceDelegate.IsBound())
		{
			TargetActor->PlaceDelegate.Unbind();
		}

		DetachDelegateHandle = TargetActor->AttachToCharacterDelegate.AddUObject(this, &ATriggerPlacement::DetachMovableActor);

		bIsChildAttached = true;
	}
}

void ATriggerPlacement::DetachMovableActor(AMovableActor *TargetActor)
{
	bIsChildAttached = false;
	TargetActor->AttachToCharacterDelegate.Remove(DetachDelegateHandle);
}


void ATriggerPlacement::ShowInteractionHint()
{
	APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AMainSceneHUD *HUD = PC->GetHUD<AMainSceneHUD>();
	HUD->ShowInteractionHint(EInteractionHintMode::Interact, InteractionName);
}

void ATriggerPlacement::HideInteractionHint()
{
	APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AMainSceneHUD *HUD = PC->GetHUD<AMainSceneHUD>();
	HUD->HideInteractionHint();
}

void ATriggerPlacement::PlaceFromPack()
{
	UPackManager *PackManager = GetGameInstance()->GetSubsystem<UPackManager>();
	TSubclassOf<AMovableActor> SelectedProperty = PackManager->GetSelectedProperty();
	AMovableActor *SpawnedActor = GetWorld()->SpawnActor<AMovableActor>(SelectedProperty, PlacementComponent->GetComponentTransform());
	SpawnedActor->GetStaticMeshComponent()->SetSimulatePhysics(false);
	PlaceMovableActor(SpawnedActor);
}

bool ATriggerPlacement::HasChildActorAttached() const
{
	return bIsChildAttached;
}

