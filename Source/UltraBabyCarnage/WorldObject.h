
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorldObject.generated.h"

/**
 * 
 */

UCLASS(Blueprintable)
class ULTRABABYCARNAGE_API UWorldObject : 
	public UObject
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintNativeEvent)
	void OnInit();

public:

	virtual class UWorld* GetWorld() const override;

};
