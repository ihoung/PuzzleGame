// Fill out your copyright notice in the Description page of Project Settings.


#include "MainScenePlayerController.h"
#include "MainSceneHUD.h"
#include "FirstPersonCharacter.h"


AMainScenePlayerController::AMainScenePlayerController(const FObjectInitializer &ObjectInitializer) :Super(ObjectInitializer)
{
    bIsOpenPackKeyPressed = false;
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
