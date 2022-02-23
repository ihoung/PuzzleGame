// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MAGICDETECTIVE_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMainGameInstance(const FObjectInitializer &ObjectInitializer);

	UFUNCTION()
	class UUserWidgetManager *GetUIMgr() const;

	UFUNCTION()
	class UPackManager *GetPackMgr() const;

	void InitDataMgr();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidgetManager> Blueprint_UIManager;

	//UI Manager
	UPROPERTY()
	class UUserWidgetManager *UIMgr;

	//Data Manager
	UPROPERTY()
	class UPackManager *PackMgr;
};
