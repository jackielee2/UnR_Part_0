#pragma once

#include "GameFramework/Character.h"
#include "Avatar.generated.h"

class APickupItem; // forward declare the APickupItem class,
// since it will be "mentioned" in a member function decl below
class AMyHUD;

UCLASS()
class GOLDENEGG_API AAvatar : public ACharacter
{
	GENERATED_UCLASS_BODY()
	
	// A map for the backpack
	TMap<FString, int> Backpack;

	// Individual maps for string name => Icon, Spell it casts, etc.
	TMap<FString, UTexture2D*> Icons;
	TMap<FString, UClass*> Classes;
	bool inventoryShowing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
	float Hp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
	float MaxHp;

	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	void MouseClicked();
	void MoveForward( float amount );
	void MoveRight( float amount );

	void Yaw( float amount );
	void Pitch( float amount );
	void Pickup( APickupItem *item );
	void ToggleInventory();
	void Drop( UClass *className );

};
