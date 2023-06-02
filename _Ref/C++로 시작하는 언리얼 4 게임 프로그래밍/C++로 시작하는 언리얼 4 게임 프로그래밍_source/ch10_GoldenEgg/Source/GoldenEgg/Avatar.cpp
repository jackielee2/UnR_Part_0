#include "GoldenEgg.h"
#include "Avatar.h"
#include "MyHUD.h"
#include "PickupItem.h"

AAvatar::AAvatar(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	inventoryShowing = false;
	Hp = MaxHp = 100;
}

void AAvatar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);

	InputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
	InputComponent->BindAxis("Strafe", this, &AAvatar::MoveRight);

	InputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
	InputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);

	InputComponent->BindAction( "Inventory", IE_Pressed, this, &AAvatar::ToggleInventory );
	InputComponent->BindAction( "MouseClickedLMB", IE_Pressed, this, &AAvatar::MouseClicked );
}

void AAvatar::MouseClicked()
{
	if( inventoryShowing )
	{
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>( PController->GetHUD() );
		hud->MouseClicked();
	}
}

void AAvatar::MoveForward( float amount )
{
	//if( inventoryShowing ) return;

	// Don't enter the body of this function if Controller is
	// not set up yet, or if the amount to move is equal to 0 
	if( Controller && amount )
	{
		FVector fwd = GetActorForwardVector();
		// we call AddMovementInput to actually move the player
		// by `amount` in the `fwd` direction
		AddMovementInput(fwd, amount);
	}
}

void AAvatar::MoveRight( float amount )
{
	//if( inventoryShowing ) return;
	
	if( Controller && amount )
	{
		FVector right = GetActorRightVector();
		AddMovementInput(right, amount);
	}
}

void AAvatar::Yaw( float amount )
{
	//x
	if( inventoryShowing )
	{
		// if the button is down click drag
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>( PController->GetHUD() );
		hud->MouseMoved();
	}
	//else
	{
		AddControllerYawInput(200.f*amount * GetWorld()->GetDeltaSeconds());
	}
}

void AAvatar::Pitch( float amount )
{
	//y
	if( inventoryShowing )
	{
		// if the button is down click drag
		APlayerController* PController = GetWorld()->GetFirstPlayerController();
		AMyHUD* hud = Cast<AMyHUD>( PController->GetHUD() );
		hud->MouseMoved();
	}
	//else
	{
		AddControllerPitchInput(200.f*amount * GetWorld()->GetDeltaSeconds());
	}
}

void AAvatar::Pickup( APickupItem *item )
{
	if( Backpack.Contains( item->Name ) )
	{
		// the item was already in the pack.. so increase qty of it
		Backpack[ item->Name ] += item->Quantity;
	}
	else
	{
		// the item wasn't in the pack before, just add it in now
		Backpack.Add(item->Name, item->Quantity);

		// record the a ref to the tex the first time it is picked up
		Icons.Add(item->Name, item->Icon);

		// for instantiation later
		Classes.Add(item->Name, item->GetClass());
	}
}

void AAvatar::ToggleInventory()
{
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	AMyHUD* hud = Cast<AMyHUD>( PController->GetHUD() );
	
	// If inventory is displayed, undisplay it.
	if( inventoryShowing )
	{
		hud->clearWidgets();
		inventoryShowing = false;
		PController->bShowMouseCursor = false;
		return;
	}

	// Otherwise, display the player's inventory
	inventoryShowing = true;
	PController->bShowMouseCursor = true;
	for( TMap<FString,int>::TIterator it = Backpack.CreateIterator(); it; ++it )
	{
		// Combine string name of the item, with qty eg Cow x 5
		FString fs = it->Key + FString::Printf( TEXT(" x %d"), it->Value );
		UTexture2D* tex = NULL;
		if( Icons.Find( it->Key ) )
		{
			tex = Icons[it->Key];
			Widget w( Icon( fs, tex ), Classes[it->Key] );
			hud->addWidget( w );
		}
	}
}

void AAvatar::Drop( UClass *className )
{
	GetWorld()->SpawnActor<AActor>(
		className, GetActorLocation() + GetActorForwardVector()*200 + FVector( 0, 0, 200 ),
		GetMesh()->GetTransformMatrix().Rotator() );
}