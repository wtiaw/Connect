// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceItem.h"
#include "Components/SizeBox.h"
#include "Connect/Button/ButtonToDrag.h"
#include "DragItem.generated.h"

class UButtonToDrag;
/**
 * 
 */
UCLASS()
class CONNECT_API UDragItem : public USpaceItem
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (BindWidget),BlueprintReadWrite)
	USizeBox* SizeBox_0;

	UPROPERTY(Meta = (BindWidget),BlueprintReadWrite)
	UButtonToDrag* BP_DragButton_1;
	
	UPROPERTY(Meta = (BindWidget),BlueprintReadWrite)
	UButtonToDrag* BP_DragButton_2;
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
