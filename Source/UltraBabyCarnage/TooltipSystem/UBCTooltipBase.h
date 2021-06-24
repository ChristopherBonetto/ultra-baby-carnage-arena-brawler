
#pragma once

#include "CoreMinimal.h"
#include "../WorldObject.h"
#include "UBCTooltipBase.generated.h"

/**
 * 
 */

UCLASS()
class ULTRABABYCARNAGE_API UUBCTooltipBase : 
	public UWorldObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	FText ParseText(const FText& message, bool useGamepadInputs) const;

};
