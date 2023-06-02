// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Puzzle.h"
#include "PuzzleGameMode.h"
#include "PuzzlePlayerController.h"

APuzzleGameMode::APuzzleGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// no pawn by default
	DefaultPawnClass = NULL;
	// use our own player controller class
	PlayerControllerClass = APuzzlePlayerController::StaticClass();
}
