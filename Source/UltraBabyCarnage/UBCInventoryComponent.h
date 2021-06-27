// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UBCConsumableBase.h"
#include "UBCInventoryComponent.generated.h"

USTRUCT(Blueprintable)
struct FUBCConsumableArray
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	int maxSize = 5;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUBCConsumableBase> parentClass = UUBCConsumableBase::StaticClass();

	UPROPERTY(EditAnywhere)
	TArray<UUBCConsumableBase*> consumables;

};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ULTRABABYCARNAGE_API UUBCInventoryComponent : 
	public UActorComponent
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemAdded, int, slotIndex, UUBCConsumableBase*, item);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemRemoved, int, slotIndex, UUBCConsumableBase*, item);

public:

	UPROPERTY(EditAnywhere)
	int maxSlotCount = 4;

	UPROPERTY(EditAnywhere)
	TArray<FUBCConsumableArray> inventory;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FItemAdded itemAdded;

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FItemRemoved itemRemoved;

private:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetImplementationDepth(UClass* parent, UClass* child) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetSlotIndexAtBestDepth(UClass* itemClass, int& outDepth) const;

public:

	UFUNCTION(BlueprintCallable)
	bool AddSlot(TSubclassOf<UUBCConsumableBase> parentClass);

	UFUNCTION(BlueprintCallable)
	bool AddItemInSlot(int slotIndex, UUBCConsumableBase* consumable);

	UFUNCTION(BlueprintCallable)
	bool AddItem(UUBCConsumableBase* consumable, int& outSlotIndex);
		
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetItemFromSlot(int slotIndex, UUBCConsumableBase*& outConsumable) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetItemOfType(TSubclassOf<UUBCConsumableBase> itemClass, int& outSlotIndex, UUBCConsumableBase*& outConsumable) const;

	UFUNCTION(BlueprintCallable)
	bool RemoveItemFromSlot(int slotIndex, UUBCConsumableBase*& outConsumable);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool RemoveItemOfType(TSubclassOf<UUBCConsumableBase> itemClass, int& outSlotIndex, UUBCConsumableBase*& outConsumable);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnItemAdded(int slotIndex, UUBCConsumableBase* item);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnItemRemoved(int slotIndex, UUBCConsumableBase* item);

};
