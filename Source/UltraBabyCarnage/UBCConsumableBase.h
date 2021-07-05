
#pragma once

#include "CoreMinimal.h"
#include "WorldObject.h"
#include "UBCCharacter.h"
#include "UBCConsumableBase.generated.h"

UCLASS()
class ULTRABABYCARNAGE_API UUBCConsumableBase : 
	public UWorldObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	int priority = 0;

protected:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnUse(AUBCCharacter* user);

public:

	UFUNCTION(BlueprintCallable)
	bool CanUse(AUBCCharacter* user);

	UFUNCTION(BlueprintCallable)
	bool Use(AUBCCharacter* user);

};
