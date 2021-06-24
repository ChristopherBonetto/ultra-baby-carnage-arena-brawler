
#include "InputGlyphsAsset.h"
#include "GameFramework/InputSettings.h"
#include "Components/RichTextBlockImageDecorator.h"
#include "Styling/SlateBrush.h"

UPaperSprite* UInputGlyphsAsset::GetGlyph(const FKey& key) const
{
	UPaperSprite* sprite = *glyphMap.Find(key);
	if(sprite->IsValidLowLevelFast())
	{
		return sprite;
	}

	return nullptr;
}

UDataTable* UInputGlyphsAsset::CreateDataTable()
{
	UDataTable* table = NewObject<UDataTable>();
	table->RowStruct = FRichImageRow::StaticStruct();

	for (auto pair : glyphMap)
	{
		FName name = pair.Key.GetFName();
		
		FRichImageRow row;
		
		FSlateBrush brush;
		brush.SetResourceObject(pair.Value);
		brush.SetImageSize(FVector2D(32, 32));
		//FSlateDynamicImageBrush brush(name, FVector2D(32, 32), );
		
		row.Brush = brush;
		
		table->AddRow(name, row);
	}

	return table;
}