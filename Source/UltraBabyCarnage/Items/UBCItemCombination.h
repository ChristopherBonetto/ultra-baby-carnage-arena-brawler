
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UBCItemBase.h"
#include "UBCItemCombination.generated.h"

USTRUCT(Blueprintable)
struct ULTRABABYCARNAGE_API FUBCItemCombination :
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AUBCItemBase> first;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AUBCItemBase> second;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AUBCItemBase> result;

};

