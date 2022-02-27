// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPlacement.h"
#include "Kismet/GameplayStatics.h"


ATriggerPlacement::ATriggerPlacement() :Super()
{
	// Create a Placement
	PlacementComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Placement"));
	PlacementComponent->SetupAttachment(GetRootComponent());
}

USceneComponent *ATriggerPlacement::GetPlacementComponent() const
{
	return PlacementComponent;
}
