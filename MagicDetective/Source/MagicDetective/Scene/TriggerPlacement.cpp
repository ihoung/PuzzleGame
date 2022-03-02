// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPlacement.h"
#include "Kismet/GameplayStatics.h"

#include "MovableActor.h"
#include "MainSceneHUD.h"


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

		TargetActor->PlaceDelegate.Unbind();
	}
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

