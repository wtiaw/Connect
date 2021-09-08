// Fill out your copyright notice in the Description page of Project Settings.


#include "Connect/Item/SpaceItem.h"

#include "Connect/Base/MyDragDropOperation.h"
#include "Connect/Base/MyPlayerController.h"

bool USpaceItem::NativeOnDrop(const FGeometry& MovieSceneBlends, const FDragDropEvent& InDragDropEvent,
                              UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(MovieSceneBlends, InDragDropEvent, InOperation);

	UMyDragDropOperation* DragDropOperation = Cast<UMyDragDropOperation>(InOperation);
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController)
	{
		if (DragDropOperation)
		{
			int Index = DragDropOperation->Button->LinesIndex;
			if (DragDropOperation->Button->ButtonType == EButtonType::Ebt_Up)
			{
				PlayerController->Lines[Index].DownButton = nullptr;
				PlayerController->Lines[Index].UpButton->LinesIndex = -1;
				PlayerController->Lines[Index].UpButton = nullptr;
				PlayerController->RemovedIndex.AddUnique(Index);
			}
			else
			{
				PlayerController->Lines[Index].UpButton = nullptr;
				PlayerController->Lines[Index].DownButton->LinesIndex = -1;
				PlayerController->Lines[Index].DownButton = nullptr;
				PlayerController->RemovedIndex.AddUnique(Index);
			}
		}
	}

	return true;
}
