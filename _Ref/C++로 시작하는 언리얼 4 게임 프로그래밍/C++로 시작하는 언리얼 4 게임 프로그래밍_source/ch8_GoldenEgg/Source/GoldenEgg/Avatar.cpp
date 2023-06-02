#include "GoldenEgg.h"
#include "Avatar.h"
#include "MyHUD.h"

AAvatar::AAvatar(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	Hp = MaxHp = 100;
}

void AAvatar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);

	InputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
	InputComponent->BindAxis("Strafe", this, &AAvatar::MoveRight);

	InputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
	InputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);
}

void AAvatar::MoveForward( float amount )
{
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
	if( Controller && amount )
	{
		FVector right = GetActorRightVector();
		AddMovementInput(right, amount);
	}
}

void AAvatar::Yaw( float amount )
{
	AddControllerYawInput(200.f*amount * GetWorld()->GetDeltaSeconds());
}

void AAvatar::Pitch( float amount )
{
	AddControllerPitchInput(200.f*amount * GetWorld()->GetDeltaSeconds());
}
