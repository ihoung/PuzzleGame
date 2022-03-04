// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicCircle.h"

#include "TriggerPlacement.h"

// Sets default values
AMagicCircle::AMagicCircle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMagicCircle::BeginPlay()
{
	Super::BeginPlay();

	for (ATriggerPlacement *Placement : PlacementArray)
	{
		Placement->OnCheckPairedActor.BindUObject(this, &AMagicCircle::ChangePairedTriggerCount);
	}
}

// Called every frame
void AMagicCircle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMagicCircle::ChangePairedTriggerCount(bool isPaired)
{
	PairedTriggerCount++;
	if (PairedTriggerCount >= PlacementArray.Num())
	{

	}
}

