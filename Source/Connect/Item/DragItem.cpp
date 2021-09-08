// Fill out your copyright notice in the Description page of Project Settings.


#include "Connect/Item/DragItem.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/UniformGridSlot.h"

void UDragItem::NativeTick(const FGeometry& MovieSceneBlends, float InDeltaTime)
{
	Super::NativeTick(MovieSceneBlends, InDeltaTime);
	FVector2D Size = FVector2D::ZeroVector;
	if (Size != SizeBox_0->GetDesiredSize())
	{
		Size = SizeBox_0->GetDesiredSize();
	}

	const UUniformGridSlot* UniformGridSlot = Cast<UUniformGridSlot>(Slot);
	if (!UniformGridSlot)
	{
		return;
	}
	int Row = UniformGridSlot->Row;
	int Column = UniformGridSlot->Column;
	
	BP_DragButton_1->Position = FVector2D(Column * Size.X, Row * Size.Y) + Cast<UCanvasPanelSlot>(BP_DragButton_1->Slot)
		->GetPosition();

	BP_DragButton_2->Position = FVector2D(Column * Size.X, Row * Size.Y) + Cast<UCanvasPanelSlot>(BP_DragButton_2->Slot)
		->GetPosition();
}


