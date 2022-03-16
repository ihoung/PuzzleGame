// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PackManager.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FGameplayPropertyInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
 	class UTexture2D *Icon;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FAddItemDelegate, const FGameplayPropertyInfo &)
DECLARE_MULTICAST_DELEGATE_OneParam(FRemoveItemDelegate, const FGameplayPropertyInfo&)
DECLARE_MULTICAST_DELEGATE_OneParam(FSelectItemDelegate, const FGameplayPropertyInfo&)

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
	TSubclassOf<class AMovableActor> GetSelectedProperty(bool bRemoveFromPack = false);

	UFUNCTION(BlueprintCallable)
	TSubclassOf<class AMovableActor> GetPropertyByName(const FName &Name);

	FAddItemDelegate OnAddItem;
	FRemoveItemDelegate OnRemoveItem;
	FSelectItemDelegate OnSelectItem;

private:
	FGameplayPropertyInfo ParseItemInfo(const FName &ID, const struct FGameplayPropertyData &ItemData);
};
