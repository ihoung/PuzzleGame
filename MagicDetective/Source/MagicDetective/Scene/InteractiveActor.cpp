// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActor.h"

AInteractiveActor::AInteractiveActor()
{
	bIsInteractable = true;
}

void AInteractiveActor::Interact_Implementation()
{
	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Short Pressed Interact: %s"));
	//}
}

void AInteractiveActor::LongPressedInteract_Implementation()
{
	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Long Pressed Interact: %s"));
	//}
}

void AInteractiveActor::ShowInteractionHint_Implementation()
{

}

void AInteractiveActor::HideInteractionHint_Implementation()
{

}

void AInteractiveActor::SetInteractable(bool IsInteractable)
{
	bIsInteractable = IsInteractable;
}

bool AInteractiveActor::GetInteractable() const
{
	return bIsInteractable;
}

