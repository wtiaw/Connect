// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/UniformGridPanel.h"
#include "Connect/Base/MyPlayerController.h"
#include "DragContainer.generated.h"

/**
 * 
 */
UCLASS()
class CONNECT_API UDragContainer : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	AMyPlayerController* PlayerController;

	UPROPERTY(Meta =(BindWidget))
	UUniformGridPanel* UniformGridPanel_51;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FLinearColor Color1;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FLinearColor Color2;

	UPROPERTY(BlueprintReadWrite)
	FLinearColor ColorOffset;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 DegreesOfSubdivision;
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	virtual void NativeConstruct() override;

	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;
};
