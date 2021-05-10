
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UBCGameInstance.generated.h"

/**
 * Game instance of the Ultra Baby Carnage game. Manages the singleton system.
 */

UCLASS(Blueprintable)
class ULTRABABYCARNAGE_API UUBCGameInstance : 
	public UGameInstance
{
	GENERATED_BODY()
	
public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FViewportSizeChanged, int, width, int, height);

public:

	/**
	* Construct the GameInstance and finds or create the instances of the singletons.
	*/

	UUBCGameInstance();

protected:

	/**
	* Map that contains the references to all the singleton instances and their class.
	*/

	UPROPERTY(EditAnywhere, Category = Singleton, BlueprintReadWrite)
	TMap<TSubclassOf<AActor>, AActor*> singletons;

public:

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FViewportSizeChanged viewportSizeChanged;

protected:

	/**
	* Finds or create an instance for the specified actor class and returns it.
	*/

	UFUNCTION(BlueprintCallable, Category = Singleton, meta = (DeterminesOutputType = "actorClass"))
	AActor* CreateInstance(TSubclassOf<AActor> actorClass);

	void OnViewportSizeChange(FViewport* viewport, uint32 value);

public:

	virtual void Init() override;

	virtual void OnStart() override;

	/**
	* Makes the specified actor class singleton so that the instance can always be retrieved.
	*/

	UFUNCTION(BlueprintCallable, Category = Singleton)
	void MakeSingleton(TSubclassOf<AActor> actorClass);

	/**
	* Returns whether the specified actor class is singleton.
	*/

	UFUNCTION(BlueprintCallable, Category = Singleton)
	bool IsSingleton(TSubclassOf<AActor> actorClass) const;

	/**
	* Returns the instance of the specified actor class. If none are found, a nullptr is returned.
	*/

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Singleton, meta = (DeterminesOutputType = "actorClass"))
	AActor* GetInstanceOf(TSubclassOf<AActor> actorClass, bool& outInstanceFound);

	/**
	* Removes the instance of the specified actor class and returns whether the instance could be removed.
	*/

	UFUNCTION(BlueprintCallable, Category = Singleton)
	bool RemoveInstance(TSubclassOf<AActor> actorClass, bool destroyActor = false);

};
