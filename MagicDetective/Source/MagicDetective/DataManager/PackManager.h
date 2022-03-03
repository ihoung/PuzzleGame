// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PackManager.generated.h"

/**
 * 
 */
UCLASS()
class MAGICDETECTIVE_API UPackManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	// Pack storage of gameplay properties
	UPROPERTY()
	TArray<FName> PropertyStack;

	UPROPERTY()
	FName CurrentSelectedProperty;
	
public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase &Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

	UFUNCTION(BlueprintCallable)
	void AddToPack(const FName &Name);

	UFUNCTION(BlueprintCallable)
	void RemoveFromPack(const FName &Name);

	UFUNCTION(BlueprintCallable)
	void SelectProperty(const FName &Name);

	UFUNCTION(BlueprintCallable)
	TSubclassOf<class AMovableActor> GetSelectedProperty();

};
