// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "PuzzleGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class APuzzleGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	APuzzleGameMode(const FObjectInitializer& ObjectInitializer);
};



