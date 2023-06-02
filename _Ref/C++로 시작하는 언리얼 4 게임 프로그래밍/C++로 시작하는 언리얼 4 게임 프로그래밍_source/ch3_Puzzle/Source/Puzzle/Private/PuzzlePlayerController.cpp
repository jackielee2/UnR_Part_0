// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Puzzle.h"
#include "PuzzlePlayerController.h"

APuzzlePlayerController::APuzzlePlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
