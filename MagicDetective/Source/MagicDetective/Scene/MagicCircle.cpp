// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicCircle.h"
#include "NiagaraComponent.h"

#include "TriggerPlacement.h"
#include "Portal.h"


// Sets default values
AMagicCircle::AMagicCircle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	DefaultSceneComponent->SetupAttachment(GetRootComponent());

	PortalEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PortalEffect"));
	PortalEffect->SetupAttachment(DefaultSceneComponent);
	PortalEffect->SetAutoActivate(false);
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
	if (isPaired)
	{
		PairedTriggerCount++;

		// All Trigger are placed with correct objects
		if (PairedTriggerCount >= PlacementArray.Num())
		{
			for (auto *Placement : PlacementArray)
			{
				Placement->OnAllTriggersPaired();
			}
			
			PortalEffect->SetActive(true);
			for (auto *Portal : RelevantPortals)
			{
				Portal->SetPortalActive(true);
			}
		}
	}
	else
	{
		PairedTriggerCount--;
	}
}

