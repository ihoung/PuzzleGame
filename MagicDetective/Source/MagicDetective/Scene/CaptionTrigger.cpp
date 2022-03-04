// Fill out your copyright notice in the Description page of Project Settings.


#include "CaptionTrigger.h"
#include "Kismet/GameplayStatics.h"

#include "FirstPersonCharacter.h"
#include "MainSceneHUD.h"
#include "DataTableManager.h"


ACaptionTrigger::ACaptionTrigger() :Super()
{
	OnActorBeginOverlap.AddDynamic(this, &ACaptionTrigger::BeginOverlap);
}

void ACaptionTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void ACaptionTrigger::BeginOverlap(AActor *overlappedActor, AActor *otherActor)
{
	if (otherActor && otherActor != overlappedActor)
	{
		if (otherActor->IsA(AFirstPersonCharacter::StaticClass()))
		{
			// Show caption
			FCaptionData captionData = GetGameInstance()->GetSubsystem<UDataTableManager>()->GetCaption(CaptionID);
			FString captionContent = captionData.TextContent;
			if (!captionContent.IsEmpty())
			{
				APlayerController *PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				AMainSceneHUD *HUD = PC->GetHUD<AMainSceneHUD>();
				HUD->ShowCaption(captionContent);
			}

		}
	}
}
