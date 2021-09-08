// Fill out your copyright notice in the Description page of Project Settings.


#include "Connect/Button/ButtonToDrag.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Connect/Base/MyPlayerController.h"
#include "SceneOutliner/Public/SceneOutlinerDragDrop.h"

void UButtonToDrag::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply UButtonToDrag::NativeOnMouseButtonDown(const FGeometry& MovieSceneBlends, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(MovieSceneBlends, InMouseEvent);

	PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent,this, EKeys::LeftMouseButton).NativeReply;
}

void UButtonToDrag::NativeOnDragDetected(const FGeometry& MovieSceneBlends, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(MovieSceneBlends, InMouseEvent, OutOperation);

	if (!PlayerController)
	{
		return;
	}

	TSubclassOf<UButtonToDrag> ClassName = LoadClass<UButtonToDrag>(NULL, TEXT("WidgetBlueprint'/Game/Button/BP_DragButton.BP_DragButton_C'"));;
	UButtonToDrag* ButtonToDrag = Cast<UButtonToDrag>(CreateWidget(PlayerController,ClassName));
	PlayerController->ControlledButton = ButtonToDrag;
	
	FLine Line;
	if (ButtonType == EButtonType::Ebt_Up)
	{
		Line.UpButton = this;
		Line.DownButton = PlayerController->ControlledButton;
	}
	else
	{
		Line.DownButton = this;
		Line.UpButton = PlayerController->ControlledButton;
	}
	if (LinesIndex == -1)
	{
		if (PlayerController->RemovedIndex.Num() > 0)
		{
			LinesIndex = PlayerController->RemovedIndex.Pop();
			PlayerController->Lines[LinesIndex] = Line;
		}
		else
		{
			LinesIndex = PlayerController->Lines.Add(Line);
		}
	}else
	{
		if (ButtonType == EButtonType::Ebt_Up)
		{
			PlayerController->Lines[LinesIndex].DownButton->LinesIndex = -1;
		}
		else
		{
			PlayerController->Lines[LinesIndex].UpButton->LinesIndex = -1;
		}

		PlayerController->Lines[LinesIndex] = Line;
	}
}

bool UButtonToDrag::NativeOnDrop(const FGeometry& MovieSceneBlends, const FDragDropEvent& InDragDropEvent,
                                 UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(MovieSceneBlends, InDragDropEvent, InOperation);

	if(!PlayerController)
	{
		PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	}
	
	if(PostButton)
	{
		const EButtonType PostButtonType = PostButton->ButtonType;
		if (PostButtonType != this->ButtonType)
		{
			if (PostButtonType == EButtonType::Ebt_Up)
			{
				if (PostButton->Position.Y > this->Position.Y)
				{
					if (this->LinesIndex != -1)
					{
						PlayerController->Lines[this->LinesIndex].UpButton->LinesIndex = -1;
						PlayerController->Lines[this->LinesIndex].UpButton = nullptr;
						PlayerController->Lines[this->LinesIndex].DownButton = nullptr;
						PlayerController->RemovedIndex.AddUnique(this->LinesIndex);
					}
					this->LinesIndex = PostButton->LinesIndex;
					PlayerController->Lines[this->LinesIndex].DownButton = this;
				}
			}
			else if (PostButtonType == EButtonType::Ebt_Down)
			{
				if (PostButton->Position.Y < this->Position.Y)
				{
					if (this->LinesIndex != -1)
					{
						PlayerController->Lines[this->LinesIndex].DownButton->LinesIndex = -1;
						PlayerController->Lines[this->LinesIndex].DownButton = nullptr;
						PlayerController->Lines[this->LinesIndex].UpButton = nullptr;
						PlayerController->RemovedIndex.AddUnique(this->LinesIndex);
					}
					this->LinesIndex = PostButton->LinesIndex;
					PlayerController->Lines[this->LinesIndex].UpButton = this;
				}
			}
		}
	}
	return true;
}
