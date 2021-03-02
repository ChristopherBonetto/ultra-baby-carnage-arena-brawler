
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../Items/UBCItemBase.h"
#include "UBCWeaponCost.generated.h"

USTRUCT(Blueprintable)
struct ULTRABABYCARNAGE_API FUBCWeaponCost :
	public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	TSubclassOf<AUBCItemBase> weaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	int cost;

};

