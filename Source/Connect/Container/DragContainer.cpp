#include "Connect/Container/DragContainer.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/UniformGridSlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Connect/Base/MyDragDropOperation.h"

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

				FLinearColor PreColor = Color1;
				if (UpPosition.X == DownPosition.X)
				{
					FVector2D PositionOffset = (UpPosition - DownPosition) / DegreesOfSubdivision;
					FVector2D PrePosition = DownPosition;
					for (int j = 0; j < DegreesOfSubdivision; j++)
					{
						FVector2D CurrentPosition = PrePosition + PositionOffset;
						UWidgetBlueprintLibrary::DrawLine(Context,
						                                  PrePosition,
						                                  CurrentPosition,
						                                  PreColor, true, 6.f);
						PrePosition = CurrentPosition;
						PreColor = PreColor + ColorOffset;
					}
				}
				else
				{
					FVector2D Position1 = DownPosition;
					FVector2D Position2 = FVector2D(DownPosition.X, UpPosition.Y - 15.f);
					FVector2D Position3 = FVector2D(UpPosition.X, UpPosition.Y - 15.f);
					FVector2D Position4 = UpPosition;

					float Length3 = (Position4 - Position3).Size();
					float Length2 = (Position3 - Position2).Size();
					float Length1 = (Position2 - Position1).Size();
					float Length = Length1 + Length2 + Length3;
					float LengthPreDegree = Length / DegreesOfSubdivision;

					int Num2 = ((Length2 / LengthPreDegree) > 1) ? (int)(Length2 / LengthPreDegree) : 1;
					int Num3 = ((15 / LengthPreDegree) > 1) ? (int)(15 / LengthPreDegree) : 1;
					int Num1 = DegreesOfSubdivision - Num2 - Num3;

					UE_LOG(LogTemp,Warning,TEXT("%d %d %d"),Num1,Num2,Num3);

					FVector2D Line1PrePosition = Position1;
					FVector2D Line2PrePosition = Position2;
					FVector2D Line3PrePosition = Position3;

					FVector2D Line1Gap = (Position2 - Position1) / Num1;
					FVector2D Line2Gap = (Position3 - Position2) / Num2;
					FVector2D Line3Gap = (Position4 - Position3) / Num3;

					FLinearColor CurrentColor = Color1;
					for (int j = 0; j < Num1; j++)
					{
						FVector2D Line1CurrentPosition = Line1PrePosition + Line1Gap;
						UWidgetBlueprintLibrary::DrawLine(Context,
						                                  Line1PrePosition,
						                                  Line1CurrentPosition,
						                                  CurrentColor, true, 5.f);
						Line1PrePosition = Line1CurrentPosition;
						CurrentColor += ColorOffset;
					}
					for (int j = 0; j < Num2; j++)
					{
						FVector2D Line2CurrentPosition = Line2PrePosition + Line2Gap;
						UWidgetBlueprintLibrary::DrawLine(Context,
						                                  Line2PrePosition,
						                                  Line2CurrentPosition,
						                                  CurrentColor, true, 5.f);
						Line2PrePosition = Line2CurrentPosition;
						CurrentColor += ColorOffset;
					}
					for (int j = 0; j < Num3; j++)
					{
						FVector2D Line3CurrentPosition = Line3PrePosition + Line3Gap;
						UWidgetBlueprintLibrary::DrawLine(Context,
													Line3PrePosition,
													Line3CurrentPosition,
													CurrentColor, true, 5.f);
						Line3PrePosition = Line3CurrentPosition;
						CurrentColor += ColorOffset;
					}
				}
			}
		}
	return LayerId;
}


