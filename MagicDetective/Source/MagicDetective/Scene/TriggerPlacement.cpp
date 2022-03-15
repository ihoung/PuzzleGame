// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPlacement.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

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

void ATriggerPlacement::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor *> childActors;
	GetAttachedActors(childActors);
	if (childActors.Num() != 0)
	{
		AttachedChildActor = Cast<AMovableActor>(childActors[0]);
		//SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
		PlaceMovableActor(AttachedChildActor);
	}
}

void ATriggerPlacement::BeginOverlap(AActor *overlappedActor, AActor *otherActor)
{
	if (otherActor && overlappedActor != otherActor)
	{
		if (otherActor->IsA(PlaceableActor))
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
		if (otherActor->IsA(PlaceableActor))
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
		// Disable interaction detection
		SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

		TargetActor->AttachToComponent(PlacementComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

		if (TargetActor->PlaceDelegate.IsBound())
		{
			TargetActor->PlaceDelegate.Unbind();
		}

		DetachDelegateHandle = TargetActor->AttachToCharacterDelegate.AddUObject(this, &ATriggerPlacement::DetachMovableActor);

		AttachedChildActor = TargetActor;

		// Check if paired Actor
		if (TargetActor->IsA(PairedActor))
		{
			OnCheckPairedActor.ExecuteIfBound(true);
		}
	}
}

void ATriggerPlacement::DetachMovableActor(AMovableActor *TargetActor)
{
	if (TargetActor)
	{
		// Enable interaction detection again
		SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

		AttachedChildActor = nullptr;

		// Reduce paired Actor count
		if (TargetActor->IsA(PairedActor))
		{
			OnCheckPairedActor.ExecuteIfBound(false);
		}

		TargetActor->AttachToCharacterDelegate.Remove(DetachDelegateHandle);
	}
}

void ATriggerPlacement::SetCollisionResponseToChannel(ECollisionChannel Channel, ECollisionResponse NewResponse)
{
	TArray<UObject *> defaultSubobjects;
	GetDefaultSubobjects(defaultSubobjects);
	UBoxComponent *boxComponent = nullptr;
	for (auto *component : defaultSubobjects)
	{
		if (component->IsA(UBoxComponent::StaticClass()))
		{
			boxComponent = Cast<UBoxComponent>(component);
			break;
		}
	}
	if (boxComponent)
	{
		boxComponent->SetCollisionResponseToChannel(Channel, NewResponse);
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

void ATriggerPlacement::PlaceFromPack()
{
	UPackManager *PackManager = GetGameInstance()->GetSubsystem<UPackManager>();
	TSubclassOf<AMovableActor> SelectedProperty = PackManager->GetSelectedProperty(true);
	AMovableActor *SpawnedActor = GetWorld()->SpawnActor<AMovableActor>(SelectedProperty, PlacementComponent->GetComponentTransform());
	if (SpawnedActor)
	{
		SpawnedActor->GetStaticMeshComponent()->SetSimulatePhysics(false);
		PlaceMovableActor(SpawnedActor);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn Actor [%s]! "), *SelectedProperty->StaticClass()->GetName());
	}
}

bool ATriggerPlacement::HasChildActorAttached() const
{
	return AttachedChildActor != nullptr;
}

void ATriggerPlacement::OnAllTriggersPaired()
{
	if (AttachedChildActor)
	{
		AttachedChildActor->OnAllTriggerPaired();
	}
}


