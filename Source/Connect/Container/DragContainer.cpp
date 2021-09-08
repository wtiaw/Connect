// Fill out your copyright notice in the Description page of Project Settings.


#include "Connect/Container/DragContainer.h"

#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/UniformGridSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UDragContainer::NativeTick(const FGeometry& MovieSceneBlends, float InDeltaTime)
{
	Super::NativeTick(MovieSceneBlends, InDeltaTime);

	FVector2D PixelPosition;
	FVector2D ViewportPosition;
	
	if(PlayerController)
	{
		if (PlayerController->ControlledButton)
		{
			USlateBlueprintLibrary::LocalToViewport(GetWorld(), MovieSceneBlends, FVector2D(0, 0), PixelPosition,
			                                        ViewportPosition);
			FVector2D MousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
			PlayerController->ControlledButton->Position = MousePosition - ViewportPosition;
		}
	}
}

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
				FVector2D UpPosition = i.UpButton->Position;
				FVector2D DownPosition = i.DownButton->Position;

				if (UpPosition.X == DownPosition.X)
				{
					FVector2D PositionOffset = DownPosition - UpPosition;
					FVector2D PrePosition = DownPosition;
					for (int j = 0; j < DegreesOfSubdivision; j++)
					{
						FVector2D CurrentPosition = PrePosition + PositionOffset;
						UWidgetBlueprintLibrary::DrawLine(Context,
						                                  PrePosition,
						                                  CurrentPosition,
						                                  FColor::Red, true, 5.f);
						PrePosition = CurrentPosition;
					}
				}
				else
				{
					UWidgetBlueprintLibrary::DrawLine(Context,
												DownPosition,
												FVector2D(DownPosition.X, UpPosition.Y - 15.f),
												FColor::Red, true,5.f);
					UWidgetBlueprintLibrary::DrawLine(Context,
												FVector2D(DownPosition.X, UpPosition.Y - 15.f),
												FVector2D(UpPosition.X, UpPosition.Y - 15.f),
												FColor::Red,true, 5.f);
					UWidgetBlueprintLibrary::DrawLine(Context,
												FVector2D(UpPosition.X, UpPosition.Y - 15.f),
												UpPosition,
												FColor::Red, true, 5.f);
				}
			}
		}
	return LayerId;
}


