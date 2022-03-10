// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "NiagaraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Materials/Material.h"
#include "GameFramework/PawnMovementComponent.h"

#include "FirstPersonCharacter.h"


// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	DefaultSceneComponent->SetupAttachment(GetRootComponent());

	PortalEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PortalEffect"));
	PortalEffectComponent->SetupAttachment(DefaultSceneComponent);

	PortalMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	PortalMeshComponent->SetupAttachment(DefaultSceneComponent);

	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
	SceneCaptureComponent->SetupAttachment(DefaultSceneComponent);

	BackwardSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Backward"));
	BackwardSceneComponent->SetupAttachment(DefaultSceneComponent);


}

void APortal::PostActorCreated()
{
	Super::PostActorCreated();

	RenderTarget = UKismetRenderingLibrary::CreateRenderTarget2D(GetWorld(), 1280, 720);
	RenderTarget->AddressX = TA_Wrap;
	RenderTarget->AddressY = TA_Wrap;

	SceneCaptureComponent->TextureTarget = RenderTarget;

	DynamicPortalMaterial = UMaterialInstanceDynamic::Create(PortalMaterialAsset, GetWorld());
	if (DynamicPortalMaterial)
	{
		PortalEffectComponent->SetVariableMaterial(MaterialParameterName, DynamicPortalMaterial);
	}
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	
	if (LinkedPortal && DynamicPortalMaterial)
	{
		DynamicPortalMaterial->SetTextureParameterValue(TextureParameterName, LinkedPortal->GetPortalRenderTarget());
	}
	else
	{
		DynamicPortalMaterial = UMaterialInstanceDynamic::Create(DefaultPortalMaterialAsset, GetWorld());
		if (DynamicPortalMaterial)
		{
			PortalEffectComponent->SetVariableMaterial(MaterialParameterName, DynamicPortalMaterial);
		}
	}

	OnActorBeginOverlap.AddDynamic(this, &APortal::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &APortal::EndOverlap);
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UpdateSceneCapture();

	if (OverlappedCharacter)
	{
		FVector postPlayerLocation;
		if (CheckIfPlayerShouldTransport(OverlappedCharacter, DeltaTime, postPlayerLocation))
		{
			TransportPlayer(OverlappedCharacter, postPlayerLocation);
		}
	}
}

UTextureRenderTarget2D *APortal::GetPortalRenderTarget() const
{
	return RenderTarget;
}

void APortal::BeginOverlap(class AActor *overlappedActor, class AActor *otherActor)
{
	if (otherActor && otherActor != overlappedActor)
	{
		if (otherActor->IsA(AFirstPersonCharacter::StaticClass()))
		{
			OverlappedCharacter = Cast<AFirstPersonCharacter>(otherActor);
			OverlappedCharacter->SetCharacterCollisionResponse(ECC_PhysicsBody, ECR_Overlap);
		}
	}
}

void APortal::EndOverlap(class AActor *overlappedActor, class AActor *otherActor)
{
	if (otherActor && otherActor != overlappedActor)
	{
		if (otherActor->IsA(AFirstPersonCharacter::StaticClass()))
		{
			OverlappedCharacter->ResetCharacterCollisionResponse();
			OverlappedCharacter = nullptr;
		}
	}
}

void APortal::UpdateSceneCapture()
{
	//FVector2D viewportSize;
	//GetWorld()->GetGameViewport()->GetViewportSize(viewportSize);
	//ResizeRenderTarget(viewportSize.X, viewportSize.Y);

	if (LinkedPortal)
	{
		FTransform playerCameraTransform = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetTransformComponent()->GetComponentTransform();
		FTransform relativeTransform = UKismetMathLibrary::ConvertTransformToRelative(playerCameraTransform, DefaultSceneComponent->GetComponentTransform());
		LinkedPortal->SceneCaptureComponent->SetRelativeLocationAndRotation(relativeTransform.GetLocation(), relativeTransform.GetRotation());

		// Set near clipping plane of scene capture
		float distance = UKismetMathLibrary::Vector_Distance(playerCameraTransform.GetLocation(), GetActorLocation());
		LinkedPortal->SceneCaptureComponent->CustomNearClippingPlane = distance;
	}

}

//void APortal::ResizeRenderTarget(float size_x, float size_y)
//{
//	if (RenderTarget)
//	{
//		RenderTarget->ResizeTarget(size_x, size_y);
//	}
//}

bool APortal::CheckIfPlayerShouldTransport(class AFirstPersonCharacter *Player, float DeltaTime, FVector &PostPlayerLocation)
{
	FVector playerLocation = Player->GetActorLocation();
	FVector playerVelocity = Player->GetVelocity();
	PostPlayerLocation = playerLocation + playerVelocity * DeltaTime;
	FVector offset = GetActorLocation() - PostPlayerLocation;
	FVector lastInputDirection = Player->GetLastMovementInputVector();

	if (FVector::DotProduct(offset, GetActorForwardVector()) < 0 && FVector::DotProduct(lastInputDirection, GetActorForwardVector()) < 0)
	{
		return true;
	}

	return false;
}

void APortal::TransportPlayer(class AFirstPersonCharacter *Player, const FVector &PostPlayerLocation)
{
	if (LinkedPortal)
	{
		auto relativeVelocity = UKismetMathLibrary::InverseTransformDirection(Player->GetTransform(), Player->GetVelocity());

		// Get location and rotation after tranported
		FTransform postPlayerTransform = UKismetMathLibrary::MakeTransform(PostPlayerLocation, Player->GetActorRotation(), Player->GetActorScale3D());
		FTransform relativeTransform = UKismetMathLibrary::ConvertTransformToRelative(BackwardSceneComponent->GetComponentTransform(), postPlayerTransform);
		FTransform composedTransform = UKismetMathLibrary::ComposeTransforms(relativeTransform, LinkedPortal->GetTransform());
		Player->SetActorLocation(composedTransform.GetLocation());
		FRotator rotator = composedTransform.GetRotation().Rotator();
		Player->GetController()->SetControlRotation(rotator);

		// Set velocity
		FVector velocity = UKismetMathLibrary::TransformDirection(UKismetMathLibrary::MakeTransform(composedTransform.GetLocation(), rotator, FVector(1.f, 1.f, 1.f)), relativeVelocity);
		Player->GetMovementComponent()->Velocity = velocity;
	}
}

