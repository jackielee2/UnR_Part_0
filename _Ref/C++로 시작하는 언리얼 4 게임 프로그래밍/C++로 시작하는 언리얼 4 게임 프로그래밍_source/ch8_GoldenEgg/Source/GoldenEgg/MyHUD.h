#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

struct Message
{
	FString message;
	float time;
	FColor frontColor;
	FColor backColor;
	UTexture2D* tex;

	Message()
	{
		// Set the default time.
		time = 5.f;
		frontColor = FColor::White;
		backColor = FColor::Black;
	}

	Message( FString iMessage, float iTime, FColor iFrontColor, FColor iBackColor )
	{
		message = iMessage;
		time = iTime;
		frontColor = iFrontColor;
		backColor = iBackColor;
		tex = 0;
	}

	Message( UTexture2D* iTex, FString iMessage, float iTime, FColor iFrontColor, FColor iBackColor )
	{
		tex = iTex;
		message = iMessage;
		time = iTime;
		frontColor = iFrontColor;
		backColor = iBackColor;
	}
};

UCLASS()
class GOLDENEGG_API AMyHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	// The font used to render the text in the HUD.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	UFont* hudFont;

	// The messages available
	TArray<Message> messages;

	// These are the dims of the screen.
	FVector2D dims;
	
	void DrawMessages();
	void DrawHealthbar();
	virtual void DrawHUD() override;
	void debug( int slot, FColor color, FString mess );
	void addMessage( Message msg );

};
