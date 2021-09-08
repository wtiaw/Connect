// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Connect/Button/ButtonToDrag.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

USTRUCT(BlueprintType)
struct FItemsArray
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<TSubclassOf<UUserWidget>> Items;
};

USTRUCT(BlueprintType)
struct FLine
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UButtonToDrag* UpButton;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UButtonToDrag* DownButton;
};

/**
 * 
 */
UCLASS()
class CONNECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FItemsArray> ItemsArrays;

	UPROPERTY(BlueprintReadWrite)
	TArray<FLine> Lines;

	TArray<int32> RemovedIndex;

	UPROPERTY(BlueprintReadWrite)
	UButtonToDrag* ControlledButton;

	UPROPERTY(BlueprintReadWrite)
	bool CanDrag = true;
	
public:
	virtual void Tick(float DeltaSeconds) override;
};
