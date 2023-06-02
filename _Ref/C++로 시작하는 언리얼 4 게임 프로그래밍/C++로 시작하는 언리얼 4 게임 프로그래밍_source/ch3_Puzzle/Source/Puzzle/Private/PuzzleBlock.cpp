// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Puzzle.h"
#include "PuzzleBlock.h"
#include "PuzzleBlockGrid.h"

APuzzleBlock::APuzzleBlock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Meshes/TemplateCube_Rounded.TemplateCube_Rounded"))
			, BlueMaterial(TEXT("/Engine/TemplateResources/MI_Template_BaseBlue.MI_Template_BaseBlue"))
			, OrangeMaterial(TEXT("/Engine/TemplateResources/MI_Template_BaseOrange.MI_Template_BaseOrange"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f,1.f,0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BlueMaterial.Get());
	BlockMesh->AttachTo(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &APuzzleBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &APuzzleBlock::OnFingerPressedBlock);

	// Save a pointer to the orange material
	OrangeMaterial = ConstructorStatics.OrangeMaterial.Get();
	
	//!!!! NEW !!!!
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
}

void APuzzleBlock::BlockClicked(UPrimitiveComponent* ClickedComp)
{
	//!!!! modified !!!!
	bIsActive = !bIsActive;

	if ( bIsActive )
		BlockMesh->SetMaterial(0, OrangeMaterial);
	else
		BlockMesh->SetMaterial(0, BlueMaterial);
	// Tell the Grid
	if(OwningGrid != NULL)
	{
		OwningGrid->AddScore();
	}

}


void APuzzleBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	BlockClicked(TouchedComponent);
}
