// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "PaperSprite.h"
#include "InputGlyphsAsset.generated.h"

/**
 * 
 */

UCLASS()
class ULTRABABYCARNAGE_API UInputGlyphsAsset : 
	public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TMap<FKey, UPaperSprite*> glyphMap;

public:

	UFUNCTION(BlueprintCallable)
	UPaperSprite* GetGlyph(const FKey& key) const;

	UFUNCTION(BlueprintCallable)
	UDataTable* CreateDataTable();

};
