// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "PuzzlePlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS()
class APuzzlePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APuzzlePlayerController(const FObjectInitializer& ObjectInitializer);
};


