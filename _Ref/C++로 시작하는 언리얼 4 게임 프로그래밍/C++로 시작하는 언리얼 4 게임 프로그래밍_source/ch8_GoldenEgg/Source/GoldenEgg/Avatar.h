#pragma once

#include "GameFramework/Character.h"
#include "Avatar.generated.h"

class AMyHUD;

UCLASS()
class GOLDENEGG_API AAvatar : public ACharacter
{
	GENERATED_UCLASS_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
	float Hp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
	float MaxHp;

	void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	void MoveForward( float amount );
	void MoveRight( float amount );

	void Yaw( float amount );
	void Pitch( float amount );

};
