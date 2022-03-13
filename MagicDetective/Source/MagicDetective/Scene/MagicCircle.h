// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicCircle.generated.h"

UCLASS()
class MAGICDETECTIVE_API AMagicCircle : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent *DefaultSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent *PortalEffect;
	
public:	
	// Sets default values for this actor's properties
	AMagicCircle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
	TArray<class ATriggerPlacement*> PlacementArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	TArray<class APortal *> RelevantPortals;

private:
	int32 PairedTriggerCount;

	void ChangePairedTriggerCount(bool isPaired);
};
