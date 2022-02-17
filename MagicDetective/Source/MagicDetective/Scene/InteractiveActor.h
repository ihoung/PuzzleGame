// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "InteractiveActor.generated.h"

/**
 * 
 */
UCLASS()
class MAGICDETECTIVE_API AInteractiveActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AInteractiveActor();

	UFUNCTION()
	void Interact(AActor *Source);
};
