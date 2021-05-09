
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UBCCharacter.generated.h"

UCLASS()
class ULTRABABYCARNAGE_API AUBCCharacter : 
	public ACharacter
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDeath, AUBCCharacter*, character, AActor*, causer);

public:

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FDeath death;

public:

	AUBCCharacter();

protected:

	UFUNCTION(BlueprintNativeEvent)
	void OnDeath(AUBCCharacter* character, AActor* causer);

};
