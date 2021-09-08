// Fill out your copyright notice in the Description page of Project Settings.


#include "Connect/Base/MyPlayerController.h"

void AMyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(ControlledButton!=nullptr)
	{
		ControlledButton->Position = FVector2D(100,100);
	}
}
