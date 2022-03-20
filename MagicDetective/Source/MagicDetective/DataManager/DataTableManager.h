// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataTable.h"
#include "DataTableManager.generated.h"

/**
 * 
 */
UENUM()
enum EDataTableType
{
	GameplayProperty,
	Caption
};

USTRUCT(BlueprintType)
struct FGameplayPropertyData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UTexture *Icon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AMovableStaticMeshActor> BlueprintActor;

};

USTRUCT(BlueprintType)
struct FCaptionData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString TextContent;
};

UCLASS()
class MAGICDETECTIVE_API UDataTableManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	class UDataTable *GameplayPropertyData;

	UPROPERTY()
	class UDataTable *CaptionData;

public:
	// Begin USubsystem
	virtual void Initialize(FSubsystemCollectionBase &Collection) override;
	virtual void Deinitialize() override;
	// End USubsystem

	void InitializeData(EDataTableType DataTableType, class UDataTable *Data);

	// Gameplay property methods
	UFUNCTION(BlueprintCallable)
	FGameplayPropertyData GetGameplayProperty(const FName &RowName);

	// Caption methods
	UFUNCTION(BlueprintCallable)
	FCaptionData GetCaption(const FName &RowName);
};
