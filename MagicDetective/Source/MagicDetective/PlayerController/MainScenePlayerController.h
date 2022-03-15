// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainScenePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MAGICDETECTIVE_API AMainScenePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    AMainScenePlayerController(const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

    // ~Overrides: APlayerController
    virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable)
    void ShowMouseCursor();

	UFUNCTION(BlueprintCallable)
    void HideMouseCursor();

private:
    // Open Pack
    bool bIsOpenPackKeyPressed;
    void OpenPackKeyPressed();
    void OpenPackKeyReleased();

    // Show item display widget
    bool bIsItemDisplayKeyPressed;
    void ShowItemDisplayKeyPressed();
    void ShowItemDisplayKeyReleased();

    // Hide widget
    bool bHideWidgetKeyPressed;
    void HideWidgetKeyPressed();
    void HideWidgetKeyReleased();
};
