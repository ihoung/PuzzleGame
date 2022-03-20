// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class MAGICDETECTIVE_API APortal : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent *DefaultSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent *PortalEffectComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent *PortalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D *SceneCaptureComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent *BackwardSceneComponent;

	// Render Target
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class UTextureRenderTarget2D *RenderTarget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class UMaterialInstanceDynamic *DynamicPortalMaterial;
	
public:	
	// Sets default values for this actor's properties
	APortal();

protected:
	virtual void PostActorCreated() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent &PropertyChangedEvent) override;
#endif
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION()
	class UTextureRenderTarget2D *GetPortalRenderTarget() const;

	UFUNCTION(BlueprintCallable)
	void SetPortalActive(bool bNewActive);

private:
	// overlapped character
	class AFirstPersonCharacter *OverlappedCharacter;

public:
	UPROPERTY(EditInstanceOnly, Category = "InstanceSetting")
	APortal *LinkedPortal;

	UPROPERTY(EditInstanceOnly, Category = "InstanceSetting")
	bool ShouldRealtimeRender;

	UPROPERTY(EditInstanceOnly, Category = "InstanceSetting")
	float DistanceOfStartTransport;

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	class UMaterialInterface *DefaultPortalMaterialAsset;

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	class UMaterialInterface *PortalMaterialAsset;

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	FName TextureParameterName;

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	FName MaterialParameterName;

private:
	UFUNCTION()
	void BeginOverlap(class AActor *overlappedActor, class AActor *otherActor);

	UFUNCTION()
	void EndOverlap(class AActor *overlappedActor, class AActor *otherActor);

	void UpdateSceneCapture();

	//void ResizeRenderTarget(float size_x, float size_y);

	bool CheckIfPlayerShouldTransport(class AFirstPersonCharacter *Player, float DeltaTime, FVector &PostPlayerLocation);

	void TransportPlayer(class AFirstPersonCharacter *Player, const FVector &PostPlayerLocation);
};
