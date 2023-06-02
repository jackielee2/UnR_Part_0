#include "GoldenEgg.h"
#include "MyHUD.h"
#include "Avatar.h"

AMyHUD::AMyHUD(const class FObjectInitializer& PCIP) : Super(PCIP)
{
}

void AMyHUD::DrawMessages()
{
	// iterate from back to front thru the list, so if we remove
	// an item while iterating, there won't be any problems
	for( int c = messages.Num() - 1; c >= 0; c-- )
	{
		// draw the background box the right size for the message
		float ow, oh, pad=10.f;
		GetTextSize( messages[c].message, ow, oh, hudFont, 1.f );

		float messageH = oh + 2*pad;
		float x = 0, y = c*messageH;
		
		if( messages[c].tex )
		{
			DrawTexture( messages[c].tex, x, y, messageH, messageH, 0, 0, 1, 1 );
		}
		else
		{
			DrawRect( FLinearColor::Red, x, y, messageH, messageH );
		}
		x += messageH;

		DrawRect( messages[c].backColor, x, y, Canvas->SizeX, messageH );
		DrawText( messages[c].message, messages[c].frontColor, x + pad, y + pad, hudFont );

		// reduce lifetime by the time that passed since last frame.
		messages[c].time -= GetWorld()->GetDeltaSeconds();
		// if the message's time is up, remove it
		if( messages[c].time < 0 )
		{
			messages.RemoveAt( c );
		}
	}
}

void AMyHUD::DrawHealthbar()
{
	// Draw the healthbar.
	AAvatar *avatar = Cast<AAvatar>( UGameplayStatics::GetPlayerPawn(GetWorld(), 0) );

	float barWidth=200, barHeight=50, barPad=12, barMargin=50;
	float percHp = avatar->Hp / avatar->MaxHp;
	DrawRect( FLinearColor( 0, 0, 0, 1 ), Canvas->SizeX - barWidth - barPad - barMargin,
		Canvas->SizeY - barHeight - barPad - barMargin, barWidth + 2*barPad, barHeight + 2*barPad );
	DrawRect( FLinearColor( 1-percHp, percHp, 0, 1 ), Canvas->SizeX - barWidth - barMargin,
		Canvas->SizeY - barHeight - barMargin, barWidth*percHp, barHeight );

}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	// dims only exist here in stock variable Canvas
	// Update them so use in addWidget()
	dims.X = Canvas->SizeX;
	dims.Y = Canvas->SizeY;

	DrawMessages();
	DrawHealthbar();
}

void AMyHUD::debug( int slot, FColor color, FString mess )
{
	if( GEngine )
	{
		GEngine->AddOnScreenDebugMessage( slot, 5.f, color, mess );
	}
}

void AMyHUD::addMessage( Message msg )
{
	messages.Add( msg );
}

