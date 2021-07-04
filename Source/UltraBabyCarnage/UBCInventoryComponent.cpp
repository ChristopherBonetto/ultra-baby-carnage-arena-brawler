
#include "UBCInventoryComponent.h"

int UUBCInventoryComponent::GetImplementationDepth(UClass* parent, UClass* child) const
{
	int depth = 0;
	while (child && child != UObject::StaticClass())
	{
		if (child == parent)
		{
			return depth;
		}

		child = child->GetSuperClass();
		depth++;
	}

	return -1;
}

int UUBCInventoryComponent::GetSlotIndexAtBestDepth(UClass* itemClass, int& outDepth) const
{
	if (inventory.Num() > 0)
	{
		int bestDepth = GetImplementationDepth(inventory[0].parentClass, itemClass);
		int bestDepthIndex = 0;

		for (int i = 1; i < inventory.Num(); i++)
		{
			int depth = GetImplementationDepth(inventory[i].parentClass, itemClass);
			if (depth < bestDepth)
			{
				bestDepth = depth;
				bestDepthIndex = i;
			}
		}

		outDepth = bestDepth;
		return bestDepthIndex;
	}

	return -1;
}

bool UUBCInventoryComponent::AddSlot(TSubclassOf<UUBCConsumableBase> parentClass)
{
	if (inventory.Num() < maxSlotCount)
	{
		inventory.Add(FUBCConsumableArray{ 5, parentClass, TArray<UUBCConsumableBase*>() });
	}

	return false;
}

bool UUBCInventoryComponent::AddItemInSlot(int slotIndex, UUBCConsumableBase* consumable)
{
	if (slotIndex < inventory.Num())
	{
		auto& arr = inventory[slotIndex];
		if (arr.consumables.Num() < arr.maxSize)
		{
			arr.consumables.Add(consumable);
			OnItemAdded(slotIndex, consumable);
			return true;
		}
	}

	return false;
}

bool UUBCInventoryComponent::AddItem(UUBCConsumableBase* consumable, int& outSlotIndex)
{
	int depth;
	if ((outSlotIndex = GetSlotIndexAtBestDepth(consumable->GetClass(), depth)) >= 0)
	{
		AddItemInSlot(outSlotIndex, consumable);
		return true;
	}

	return false;
}

int UUBCInventoryComponent::GetSlotCount(int slotIndex) const
{
	if (inventory.IsValidIndex(slotIndex))
	{
		return inventory[slotIndex].consumables.Num();
	}

	return 0;
}

int UUBCInventoryComponent::GetSlotCountOfType(TSubclassOf<UUBCConsumableBase> itemClass, int& outSlotIndex) const
{
	int depth;
	if ((outSlotIndex = GetSlotIndexAtBestDepth(itemClass, depth)) >= 0)
	{
		return GetSlotCount(outSlotIndex);
	}

	return 0;
}

bool UUBCInventoryComponent::GetItemFromSlot(int slotIndex, UUBCConsumableBase*& outConsumable) const
{
	if (slotIndex < inventory.Num())
	{
		auto arr = inventory[slotIndex].consumables;
		if (arr.Num() > 0)
		{
			outConsumable = arr[0];
			return true;
		}
	}

	return false;
}

bool UUBCInventoryComponent::GetItemOfType(TSubclassOf<UUBCConsumableBase> itemClass, int& outSlotIndex, UUBCConsumableBase*& outConsumable) const
{
	int depth;
	if ((outSlotIndex = GetSlotIndexAtBestDepth(itemClass, depth)) >= 0)
	{
		return GetItemFromSlot(outSlotIndex, outConsumable);
	}

	return false;
}

bool UUBCInventoryComponent::RemoveItemFromSlot(int slotIndex, UUBCConsumableBase*& outConsumable)
{
	if (GetItemFromSlot(slotIndex, outConsumable))
	{
		inventory[slotIndex].consumables.RemoveAt(0);
		OnItemRemoved(slotIndex, outConsumable);
		return true;
	}

	return false;
}

bool UUBCInventoryComponent::RemoveItemOfType(TSubclassOf<UUBCConsumableBase> itemClass, int& outSlotIndex, UUBCConsumableBase*& outConsumable)
{
	int depth;
	if ((outSlotIndex = GetSlotIndexAtBestDepth(itemClass, depth)) >= 0)
	{
		return RemoveItemFromSlot(outSlotIndex, outConsumable);
	}

	return false;
}

void UUBCInventoryComponent::OnItemAdded_Implementation(int slotIndex, UUBCConsumableBase* item)
{
	itemAdded.Broadcast(slotIndex, item);
}

void UUBCInventoryComponent::OnItemRemoved_Implementation(int slotIndex, UUBCConsumableBase* item)
{
	itemRemoved.Broadcast(slotIndex, item);
}