// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemCapture.generated.h"

UCLASS()
class MAGICDETECTIVE_API AItemCapture : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D *SceneCaptureComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent *ItemPlacement;
	
public:	
	// Sets default values for this actor's properties
	AItemCapture();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UTextureRenderTarget2D *RenderTarget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class AMovableStaticMeshActor *DisplayedItem;

	USceneComponent *InteractivePivot;

public:
	UFUNCTION(BlueprintCallable)
	void DisplayItem(TSubclassOf<class AMovableStaticMeshActor> ItemBlueprint);

	UFUNCTION(BlueprintCallable)
	void RotateItem(float ScreenOffset_X, float ScreenOffset_Y);

	UFUNCTION(BlueprintCallable)
	void ZoomItem(float WheelDelta);
};
