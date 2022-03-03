// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainSceneLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class MAGICDETECTIVE_API AMainSceneLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

	// Gameplay Property Data Table
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = true))
	class UDataTable *GameplayPropertyDataTable;
	
protected:
	virtual void BeginPlay() override;

};
