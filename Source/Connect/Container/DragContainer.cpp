// Fill out your copyright notice in the Description page of Project Settings.


#include "Connect/Container/DragContainer.h"
#include "Components/UniformGridSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

// void UDragContainer::NativeTick(const FGeometry& MovieSceneBlends, float InDeltaTime)
// {
// 	Super::NativeTick(MovieSceneBlends, InDeltaTime);
//
// 	if(PlayerController)
// 	{
// 		if (PlayerController->ControlledButton)
// 		{
// 			CanvasPanel_67->AddChild(PlayerController->ControlledButton);
// 		}
// 	}
// }

void UDragContainer::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayerController)
	{
		for (int i = 0; i < PlayerController->ItemsArrays.Num(); i++)
		{
			UE_LOG(LogTemp,Warning,TEXT("%d"),i);
			for (int j = 0; j < PlayerController->ItemsArrays[i].Items.Num(); j++)
			{
				UUserWidget* Item = CreateWidget(GetWorld(),PlayerController->ItemsArrays[i].Items[j]);
				UniformGridPanel_51->AddChild(Item);
				UUniformGridSlot* UniformGridSlot =  Cast<UUniformGridSlot>(Item->Slot);
				UniformGridSlot->SetRow(i);
				UniformGridSlot->SetColumn(j);
				UE_LOG(LogTemp,Warning,TEXT("%s"),*Item->GetName());
			}
		}
	}
}

int32 UDragContainer::NativePaint(const FPaintArgs& MovieSceneBlends, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	Super::NativePaint(MovieSceneBlends, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId,
	                   InWidgetStyle,
	                   bParentEnabled);

	FPaintContext Context(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	if (PlayerController)
		for (auto i : PlayerController->Lines)
		{
			if (i.UpButton != nullptr && i.DownButton != nullptr)
			{
				FVector2D Position1 = i.UpButton->Position;
				FVector2D Position2 = i.DownButton->Position;

				UWidgetBlueprintLibrary::DrawLine(Context, Position1, Position2);
			}
		}

	return LayerId;
}


