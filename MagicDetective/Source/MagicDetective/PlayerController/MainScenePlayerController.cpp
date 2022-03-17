// Fill out your copyright notice in the Description page of Project Settings.


#include "MainScenePlayerController.h"
#include "MainSceneHUD.h"
#include "FirstPersonCharacter.h"
#include "PackManager.h"
#include "MovableStaticMeshActor.h"


AMainScenePlayerController::AMainScenePlayerController(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
{
    bIsOpenPackKeyPressed = false;
    bIsItemDisplayKeyPressed = false;
}

void AMainScenePlayerController::SetupInputComponent()
{
    // Always call this.
    Super::SetupInputComponent();

    // This is initialized on startup, you can go straight to binding
    InputComponent->BindAction("OpenPack", IE_Pressed, this, &AMainScenePlayerController::OpenPackKeyPressed);
    InputComponent->BindAction("OpenPack", IE_Released, this, &AMainScenePlayerController::OpenPackKeyReleased);

    InputComponent->BindAction("CallMouse", IE_Pressed, this, &AMainScenePlayerController::ShowMouseCursor);
    InputComponent->BindAction("CallMouse", IE_Released, this, &AMainScenePlayerController::HideMouseCursor);

    InputComponent->BindAction("DisplayItem", IE_Pressed, this, &AMainScenePlayerController::ShowItemDisplayKeyPressed);
    InputComponent->BindAction("DisplayItem", IE_Released, this, &AMainScenePlayerController::ShowItemDisplayKeyReleased);

    InputComponent->BindAction("Exit", IE_Pressed, this, &AMainScenePlayerController::HideWidgetKeyPressed);
    InputComponent->BindAction("Exit", IE_Released, this, &AMainScenePlayerController::HideWidgetKeyReleased);

    InputComponent->BindAction("OpenMenu", IE_Pressed, this, &AMainScenePlayerController::OpenSceneMenuKeyPressed);
    InputComponent->BindAction("OpenMenu", IE_Released, this, &AMainScenePlayerController::OpenSceneMenuKeyReleased);
}

void AMainScenePlayerController::OpenPackKeyPressed()
{
    bIsOpenPackKeyPressed = true;
}

void AMainScenePlayerController::OpenPackKeyReleased()
{
    if (bIsOpenPackKeyPressed)
    {
        GetHUD<AMainSceneHUD>()->OpenOrHidePack();
        bIsOpenPackKeyPressed = false;
    }
}

void AMainScenePlayerController::ShowItemDisplayKeyPressed()
{
    bIsItemDisplayKeyPressed = true;
}

void AMainScenePlayerController::ShowItemDisplayKeyReleased()
{
    if (bIsItemDisplayKeyPressed)
    {
        TSubclassOf<AMovableStaticMeshActor> SelectedItem = GetGameInstance()->GetSubsystem<UPackManager>()->GetSelectedProperty();
        if (SelectedItem)
        {
            GetHUD<AMainSceneHUD>()->ShowItemDisplay(SelectedItem);
            bIsItemDisplayKeyPressed = false;
        }
    }
}

void AMainScenePlayerController::HideWidgetKeyPressed()
{
    bHideWidgetKeyPressed = true;
}

void AMainScenePlayerController::HideWidgetKeyReleased()
{
    if (bHideWidgetKeyPressed)
    {
        GetHUD<AMainSceneHUD>()->HideItemDisplay();
        bHideWidgetKeyPressed = false;
    }
}

void AMainScenePlayerController::ShowMouseCursor()
{
    GetPawn<AFirstPersonCharacter>()->DisableInput(this);
    bShowMouseCursor = true;
}

void AMainScenePlayerController::HideMouseCursor()
{
    bShowMouseCursor = false;
    GetPawn<AFirstPersonCharacter>()->EnableInput(this);
}

void AMainScenePlayerController::OpenSceneMenuKeyPressed()
{
    bOpenSceneMenuKeyPressed = true;
}

void AMainScenePlayerController::OpenSceneMenuKeyReleased()
{
    if (bOpenSceneMenuKeyPressed)
    {
        GetHUD<AMainSceneHUD>()->ShowMenu();
        bOpenSceneMenuKeyPressed = false;
    }
}
