// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemCapture.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "MovableActor.h"


// Sets default values
AItemCapture::AItemCapture()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>("ItemSceneCapture");
	SceneCaptureComponent->SetupAttachment(GetRootComponent());
	SceneCaptureComponent->PrimitiveRenderMode = ESceneCapturePrimitiveRenderMode::PRM_UseShowOnlyList;

	ItemPlacement = CreateDefaultSubobject<USceneComponent>("ItemPlacement");
	ItemPlacement->SetupAttachment(SceneCaptureComponent);

}

// Called when the game starts or when spawned
void AItemCapture::BeginPlay()
{
	Super::BeginPlay();
	
	RenderTarget = UKismetRenderingLibrary::CreateRenderTarget2D(GetWorld(), 1280, 720);
	RenderTarget->AddressX = TA_Wrap;
	RenderTarget->AddressY = TA_Wrap;
	SceneCaptureComponent->TextureTarget = RenderTarget;
}

// Called every frame
void AItemCapture::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemCapture::DisplayItem(TSubclassOf<class AMovableActor> ItemBlueprint)
{
	// Spawn new item
	DisplayedItem = GetWorld()->SpawnActor<AMovableActor>(ItemBlueprint, ItemPlacement->GetComponentLocation(), { 0.f,0.f,0.f });
	InteractivePivot = Cast<USceneComponent>(DisplayedItem->GetDefaultSubobjectByName(TEXT("InteractivePivot")));
	if (InteractivePivot)
	{
		FTransform relativeTransform = UKismetMathLibrary::ConvertTransformToRelative(InteractivePivot->GetComponentTransform(), DisplayedItem->GetActorTransform());
		FTransform composedTransform = UKismetMathLibrary::ComposeTransforms(relativeTransform, ItemPlacement->GetComponentTransform());
		DisplayedItem->SetActorTransform(composedTransform);
	}
	else
	{
		DisplayedItem->SetActorTransform(ItemPlacement->GetComponentTransform());
	}

	// Only show current display actor
	SceneCaptureComponent->ShowOnlyActors = { DisplayedItem };
}

void AItemCapture::RotateItem(float ScreenOffset_X, float ScreenOffset_Y)
{
	FRotator rot = { 0.f, -ScreenOffset_Y, ScreenOffset_X };
	if (InteractivePivot)
	{
		auto world_rot = UKismetMathLibrary::TransformRotation(SceneCaptureComponent->GetComponentTransform(), rot);
		DisplayedItem->AddActorWorldRotation(world_rot);
	}
	else
	{
		DisplayedItem->AddActorWorldRotation(UKismetMathLibrary::TransformRotation(SceneCaptureComponent->GetComponentTransform(), rot));
	}
}

void AItemCapture::ZoomItem(float WheelDelta)
{
	SceneCaptureComponent->FOVAngle -= WheelDelta;
}


