// Fill out your copyright notice in the Description page of Project Settings.


#include "MainSceneHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

#include "CaptionWidget.h"
#include "PackWidget.h"
#include "ItemDisplayWidget.h"
#include "MainScenePlayerController.h"


void AMainSceneHUD::BeginPlay()
{
	Super::BeginPlay();

	ShowPackWidget();
}

void AMainSceneHUD::ShowInteractionHint(EInteractionHintMode Mode, FString info)
{
	if (InteractionHint == nullptr)
	{
		InteractionHint = CreateWidget<UInteractionHintWidget>(GetWorld(), InteractionHintWidget);
	}
	if (InteractionHint)
	{
		if (!InteractionHint->IsInViewport())
		{
			int32 ZOrder = 0;
			if (WidgetZOrder.Contains(InteractionHintWidget))
			{
				ZOrder = WidgetZOrder[InteractionHintWidget];
			}
			InteractionHint->AddToViewport(ZOrder);
		}
		switch (Mode)
		{
		case EInteractionHintMode::Interact:
			InteractionHint->InteractMode(info);
			break;
		case EInteractionHintMode::Hold:
			InteractionHint->HoldMode();
			break;
		case EInteractionHintMode::HoldAndTrigger:
			InteractionHint->HoldAndTriggerMode();
			break;
		default:
			break;
		}
	}
}

void AMainSceneHUD::HideInteractionHint()
{
	if (InteractionHint)
	{
		InteractionHint->RemoveFromViewport();
	}
}

void AMainSceneHUD::ShowCaption(const FString &TextContent, bool IsForcedToFinish)
{
	if (Caption == nullptr)
	{
		Caption = CreateWidget<UCaptionWidget>(GetWorld(), CaptionWidget);
	}

	if (!Caption->IsInViewport())
	{
		Caption->OnCaptionEnd.BindUObject(this, &AMainSceneHUD::HideCaption);

		int32 ZOrder = 0;
		if (WidgetZOrder.Contains(CaptionWidget))
		{
			ZOrder = WidgetZOrder[CaptionWidget];
		}
		Caption->AddToViewport(ZOrder);
	}

	Caption->ShowCaption(TextContent, IsForcedToFinish);
}

void AMainSceneHUD::HideCaption()
{
	if (Caption->IsInViewport())
	{
		Caption->OnCaptionEnd.Unbind();
		Caption->RemoveFromViewport();
	}
}

void AMainSceneHUD::ShowPackWidget()
{
	if (Pack == nullptr)
	{
		Pack = CreateWidget<UPackWidget>(GetWorld(), PackWidget);
	}

	if (!Pack->IsInViewport())
	{
		int32 ZOrder = 0;
		if (WidgetZOrder.Contains(PackWidget))
		{
			ZOrder = WidgetZOrder[PackWidget];
		}
		Pack->AddToViewport(ZOrder);
	}

}

void AMainSceneHUD::OpenOrHidePack()
{
	if (Pack)
	{
		Pack->OpenOrHidePack();
	}
}

void AMainSceneHUD::ShowItemDisplay(TSubclassOf<AMovableActor> ItemBlueprint)
{
	if (ItemDisplay == nullptr)
	{
		ItemDisplay = CreateWidget<UItemDisplayWidget>(GetWorld(), ItemDisplayWidget);
	}

	if (ItemDisplay)
	{
		if (!ItemDisplay->IsInViewport())
		{
			int32 ZOrder = 0;
			if (WidgetZOrder.Contains(ItemDisplayWidget))
			{
				ZOrder = WidgetZOrder[ItemDisplayWidget];
			}
			ItemDisplay->AddToViewport(ZOrder);
		}

		AMainScenePlayerController *playerController = Cast<AMainScenePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (playerController)
		{
			playerController->ShowMouseCursor();
		}
		ItemDisplay->ShowItem(ItemBlueprint);
	}
}

void AMainSceneHUD::HideItemDisplay()
{
	AMainScenePlayerController *playerController = Cast<AMainScenePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (playerController)
	{
		playerController->HideMouseCursor();
	}

	if (ItemDisplay && ItemDisplay->IsInViewport())
	{
		ItemDisplay->RemoveFromViewport();
	}
}
