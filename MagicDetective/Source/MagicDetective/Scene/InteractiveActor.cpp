// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActor.h"

AInteractiveActor::AInteractiveActor()
{

}

void AInteractiveActor::Interact(AActor *Source)
{
	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Short Pressed Interact: %s"));
	//}
}

void AInteractiveActor::LongPressedInteract(AActor *Source)
{
	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Long Pressed Interact: %s"));
	//}
}

void AInteractiveActor::ShowInteractionHint()
{

}

void AInteractiveActor::HideInteractionHint()
{

}

