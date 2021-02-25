
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE(Blueprintable, MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface of objects that can be interacted with.
 */

class ULTRABABYCARNAGE_API IInteractable
{
	GENERATED_BODY()

public:

	/**
	* Interacts with this object and returns whether the interaction was succesful.
	*/

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Interact(AActor* interactor);

};
