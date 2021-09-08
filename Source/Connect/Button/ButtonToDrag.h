// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonToDrag.generated.h"

class AMyPlayerController;
class UDragItem;
UENUM(BlueprintType)
enum class EButtonType : uint8
{
	Ebt_Up,
	Ebt_Down,
};
/**
 * 
 */
UCLASS()
class CONNECT_API UButtonToDrag : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	EButtonType ButtonType;

	UPROPERTY(BlueprintReadWrite)
	UDragItem* DragItem;

	UPROPERTY(BlueprintReadWrite)
	FVector2D Position;

	UPROPERTY(BlueprintReadWrite)
	int32 LinesIndex = -1;

	UPROPERTY(BlueprintReadWrite)
	UButtonToDrag* PostButton;
	
	UPROPERTY()
	AMyPlayerController* PlayerController;

public:
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};

